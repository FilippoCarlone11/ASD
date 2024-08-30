#include "quotazioni.h"
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

typedef struct BSTnode *link;
struct BSTnode {
    quotazione q;
    link l;
    link r;
    link p;
    int N;
};

struct binarysearchtree{
    link root;
    link z;
};

static link BSTinsertR(link root, link z, quotazione q);
static void BSTvisit_r(link h, link z);
static void treeFree(link h, link z);
static quotazione BSTsearch_r(link h, link z, time t);
static void BSTminbtD_r(link h, link z, time t1, time t2, int *min, int *max);
static void BSTmin_r(link h, link z, int *min, int *max);
static link newNode(quotazione q, link l, link r, link p, int N);
static link rotR(link h);
static link rotL(link h);
static int BSTcountR(link h, link z);


static link newNode(quotazione q, link l, link r, link p, int N){
    link x = malloc(sizeof *x);
    x->q = q;
    x->l = l;
    x->r = r;
    x->p = p;
    x->N = N;
    return x;
}

BST BSTinit(){
    BST b = malloc(sizeof *b);
    b->root = b->z = newNode(QTSetNull(), NULL,NULL, NULL, 0);
    return b;
}

void BSTinsert(BST b, quotazione q){
    b->root = BSTinsertR(b->root, b->z, q);
}

static link BSTinsertR(link root, link z, quotazione q){
    if(root == z)
        return newNode(q, z, z, z,1);
    if(DateCompare(getTimeQT(root->q), getTimeQT(q)) > 0) {
        root->r = BSTinsertR(root->r, z, q);
        root->r->p = root;
    }
    else if(DateCompare(getTimeQT(root->q), getTimeQT(q)) == 0) {
        root->q = updateQT(root->q, q);
        return root;
    }
    else {
        root->l = BSTinsertR(root->l, z, q);
        root->l->p = root;
    }
    (root->N)++;
    return root;

}

void BSTvisit(BST b){
    BSTvisit_r(b->root, b->z);
}

static void BSTvisit_r(link h, link z){
    if(h == z)
        return;
    dateStore(h->q.datetime);
    printf("%d %d\n", h->q.value, h->q.n);
    BSTvisit_r(h->l, z);
    BSTvisit_r(h->r, z);
}

void BSTfree(BST b){
    if(b == NULL)
        return;
    treeFree(b->root, b->z);
    free(b->z);
    free(b);
}

static void treeFree(link h, link z){
    if(h == z)
        return;
    treeFree(h->l, z);
    treeFree(h->r, z);
    free(h);
}

quotazione BSTsearch(BST b, time t){
    return BSTsearch_r(b->root, b->z, t);
}

static quotazione BSTsearch_r(link h, link z, time t){
    if(h == z)
        return QTSetNull();
    int cmp = DateCompare(getTimeQT(h->q), t);
    if(cmp == 0)
        return h->q;
    if(cmp == 1)
        return BSTsearch_r(h->r, z, t);
    return BSTsearch_r(h->l, z, t);

}

static void BSTminbtD_r(link h, link z, time t1, time t2, int *min, int *max){
    int tempmin;
    if(h == z)
        return;
    BSTminbtD_r(h->l, z, t1, t2, min, max);
    if(DateCompare(t1, getTimeQT(h->q)) >= 0 && DateCompare(getTimeQT(h->q), t2) >= 0) {
        tempmin = getValueQT(h->q);
        if(tempmin < *min)
            *min = tempmin;
        if(tempmin > *max)
            *max = tempmin;
    }
    BSTminbtD_r(h->r, z, t1, t2, min, max);
}

void BSTminBetweenDate(BST b, time t1, time t2){
    int min = INT_MAX, max = INT_MIN;
    BSTminbtD_r(b->root, b->z, t1, t2, &min, &max);
    if(min == INT_MAX && max == INT_MIN)
        printf("Nessuna quotazione trovata\n");
    else
        printf("Valore minimo: %d, Valore massimo: %d\n", min, max);
}

static void BSTmin_r(link h, link z, int *min, int *max){
    int tempmin;
    if(h == z)
        return;
    BSTmin_r(h->l, z,  min, max);
    tempmin = getValueQT(h->q);
    if(tempmin < *min)
        *min = tempmin;
    if(tempmin > *max)
        *max = tempmin;
    BSTmin_r(h->r, z,  min, max);
}

void BSTmin(BST b){
    int min = INT_MAX, max = INT_MIN;
    BSTmin_r(b->root, b->z, &min, &max);
    if(min == INT_MAX && max == INT_MIN)
        printf("Nessuna quotazione trovata\n");
    else
        printf("Valore minimo: %d, Valore massimo: %d\n", min, max);
}

static link rotR(link h){
    link x = h->l;
    h->l = x->r;
    x->r->p = h;
    x->r = h;
    x->p = h->p;
    h->p = x;
    x->N = h->N;
    h->N = 1;
    h->N += (h->l) ? h->l->N : 0;
    h->N += (h->r) ? h->r->N : 0;
    return x;
}

static link rotL(link h) {
    link x = h->r;
    h->r = x->l;
    x->l->p = h;
    x->l = h;
    x->p = h->p;
    h->p = x;
    x->N = h->N;
    h->N = 1;
    h->N += (h->l) ? h->l->N : 0;
    h->N += (h->r) ? h->r->N : 0;
    return x;
}

link partR(link h, int r){
    int t = h->l->N;
    if(t > r){
        h->l = partR(h->l, r);
        h = rotR(h);
    }
    if(t < r){
        h->r = partR(h->r, r -t -1);
        h = rotL(h);
    }
    return h;
}

int BSTcount(BST b){
    return BSTcountR(b->root, b->z);
}

static int BSTcountR(link h, link z){
    if (h == z)
        return 0;
    return BSTcountR(h->l, z) + BSTcountR(h->r, z) + 1;
}

static int treeMinmaxHeight(link h, int *max, int depth) { //del prof
    int min_l, min_r;
    if (h == NULL)
        return 0;
    if (h->l == NULL && h->r == NULL) {
        if (depth > *max)
            *max = depth;
        return 1;
    }
    min_l = treeMinmaxHeight(h->l, max, depth+1);
    min_r = treeMinmaxHeight(h->r, max, depth+1);
    if (h->l == NULL)
        return min_r+1;
    if (h->r == NULL)
        return min_l+1;
    return (min_l < min_r) ? min_l+1 : min_r+1;
}

void BSTbil(BST bst){
    int min = -1, max = -1, S = -1;
    min = treeMinmaxHeight(bst->root, &max, 1);
    if (bst->root && (bst->root->l == NULL || bst->root->r == NULL))
        min = 0;
    if (min == 0 || (max / (float) min) > S) {
        printf("Pre-bilanciamento min_path = %d max_path = %d\n", min, max);
        partR(bst->root, BSTcount(bst));
        min = max = -1;
        min = treeMinmaxHeight(bst->root, &max, 1);
        printf("Post-bilanciamento min_path = %d max_path = %d\n", min, max);
    }

}