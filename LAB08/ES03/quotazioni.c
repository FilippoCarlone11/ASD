#include "quotazioni.h"

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
typedef struct BSTnode *link;
struct BSTnode {
    quotazione q;
    link l;
    link r;
};

struct binarysearchtree{
    link root;
    link z;
};

static link BSTinsertR(link root, link z, quotazione q);
static void BSTvisit_r(link h, link z);
static void treeFree(link h, link z);
static quotazione BSTsearch_r(link h, link z, time t);
static void BSTminbtD_r(link h, link z, time t1, time t2, int *min);
static void BSTmin_r(link h, link z, int *min);


link newNode(quotazione q, link l, link r){
    link x = malloc(sizeof *x);
    x->q = q;
    x->l = l;
    x->r = r;
    return x;
}

BST BSTinit(){
    BST b = malloc(sizeof *b);
    b->root = b->z = newNode(qSetNull(), NULL, NULL);
    return b;
}

void BSTinsert(BST b, quotazione q){
    b->root = BSTinsertR(b->root, b->z, q);
}

static link BSTinsertR(link root, link z, quotazione q){
    if(root == z)
        return newNode(q, z, z);
    if(DateCompare(getTime(root->q), getTime(q)) > 0)
        root->r = BSTinsertR(root->r, z, q);
    else if(DateCompare(getTime(root->q), getTime(q)) == 0) {
        root->q = UpdateQT(root->q, q);
        return root;
    }
    else
        root->l = BSTinsertR(root->l, z, q);
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
        return qSetNull();
    int cmp = DateCompare(getTime(h->q), t);
    if(cmp == 0)
        return h->q;
    if(cmp == 1)
        return BSTsearch_r(h->r, z, t);
    return BSTsearch_r(h->l, z, t);

}

static void BSTminbtD_r(link h, link z, time t1, time t2, int *min){
    int tempmin;
    if(h == z)
        return;
    BSTminbtD_r(h->l, z, t1, t2, min);
    if(DateCompare(t1, getTime(h->q)) >= 0 && DateCompare(getTime(h->q), t2) <= 0) {
        tempmin = getQValue(h->q);
        if(tempmin < *min)
            *min = tempmin;
    }
    BSTminbtD_r(h->r, z, t1, t2, min);
}

int BSTminBetweenDate(BST b, time t1, time t2){
    int min = INT_MAX;
    BSTminbtD_r(b->root, b->z, t1, t2, &min);
    return min;
}

static void BSTmin_r(link h, link z, int *min, int *max){
    int tempmin;
    if(h == z)
        return;
    BSTmin_r(h->l, z,  min);
    tempmin = getQValue(h->q);
    if(tempmin < *min)
        *min = tempmin;
    BSTmin_r(h->r, z,  min);
}

int BSTmin(BST b){
    int min = INT_MAX, max = INT_MIN;
    BSTmin_r(b->root, b->z, &min, &max);
    return min;
}