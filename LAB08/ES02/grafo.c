#include "grafo.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct graph{
    int V;
    int E;
    int **madj;
    ST tab;
};




static int** MATRIXinit(int v);
static ST STinit(int V);
static Graph GRAPHinit(int V);
static void STinsert(ST s, char* n1, char* nw1, int *nodes);
static int STsearch(ST s, char *elab, int n);
void GRAPHinsertE(Graph G, int id1, int id2, int wt);
void insertE(Graph G, Edge e);
void GRAPHstore(Graph G, char *filename);
static void GRAPHedges(Graph G, Edge *a);
static char *STsearchByIndex(ST s, int i);
int isInList(link head, int index);

static Graph GRAPHinit(int V){
    Graph G = malloc(sizeof *G);
    G->V = V;
    G->E = 0;
    G->madj = MATRIXinit(V);
    G->tab = STinit(V);
    return G;
}

static int** MATRIXinit(int v){
    int **table = (int **)malloc(v*sizeof(int *));
    for(int i = 0; i < v; i++){
        table[i] = (int *)malloc(v*sizeof(int));
    }
    for(int i = 0; i < v; i++)
        for(int j = 0; j < v; j++)
            table[i][j] = 0;
    return table;
}

static ST STinit(int V){
    ST st;
    st = (node *)malloc(V*sizeof(node));
    return st;
}

Graph Graphload(char *filename){
    int edges = 0, wt, id1, id2, nodes = 0;
    Graph G;
    char elab1[MAXC], elab2[MAXC], net1[MAXC], net2[MAXC];

    FILE *fp = fopen(filename, "r");
    if(fp == NULL) {
        printf("File non trovato");
        return NULL;
    }
    while(fscanf(fp, "%s %s %s %s %d", elab1, net1, elab2, net2, &wt) == 5) {
        edges++;
    }
    G = GRAPHinit(edges);
    fclose(fp);
    fp = fopen(filename, "r");
    if(fp == NULL) {
        printf("File non trovato");
        return NULL;
    }
    while(fscanf(fp, "%s %s %s %s %d", elab1, net1, elab2, net2, &wt) == 5) {
        STinsert(G->tab, elab1, net1, &nodes);
        STinsert(G->tab, elab2, net2, &nodes);
        id1 = STsearch(G->tab, elab1, nodes);
        id2 = STsearch(G->tab, elab2, nodes);
        if(id1 >= 0 && id2 >= 0)
            GRAPHinsertE(G, id1, id2, wt);
    }
    G->V = nodes;
}

static void STinsert(ST s, char* n1, char* nw1, int *nodes){
    int i, found = 0;
    for(int i = 0; i < *nodes && !found; i++)
        if(strcmp(s[i].elab, n1) == 0)
            found = 1;
    if(!found){
        s[(*nodes)].elab = strdup(n1); s[(*nodes)].network = strdup(nw1);
        (*nodes)++;
    }
}

static int STsearch(ST s, char *elab, int n){
    for(int i = 0; i < n; i++)
        if(strcmp(s[i].elab, elab) == 0)
            return i;
    return -1;
}

void GRAPHinsertE(Graph G, int id1, int id2, int wt){
    Edge e; e.v = id1; e.w = id2; e.wt = wt;
    insertE(G, e);
}

void insertE(Graph G, Edge e){
    if(G->madj[e.v][e.w] == 0)
        G->E++;
    G->madj[e.v][e.w] = e.wt;
    G->madj[e.w][e.v] = e.wt;
}

void GRAPHstore(Graph G, char *filename){
    FILE *fp;
    if(strcmp(filename, "stdout") == 0)
        fp = stdout;
    else
        fp = fopen(filename, "r");

    Edge *a = malloc(G->E * sizeof(Edge));
    GRAPHedges(G, a);

    fprintf(fp, "%d\n", G->V);
    for(int i = 0; i < G->V; i++)
        fprintf(fp, "%s\n", STsearchByIndex(G->tab, i));
    for(int i = 0; i < G->E; i++) {
        fprintf(fp, "%s %s %d\n", STsearchByIndex(G->tab, a[i].v), STsearchByIndex(G->tab, a[i].w), a[i].wt);

    }
    free(a);

}

static void GRAPHedges(Graph G, Edge *a){
    int k = 0;
    for(int i = 0; i < G->V; i++){
        for(int j = i; j < G->V; j++){
            if(G->madj[i][j] != 0){
                a[k].v = i; a[k].w = j; a[k].wt = G->madj[i][j]; k++;
            }
        }
    }
}

static char *STsearchByIndex(ST s, int i){
    return s[i].elab;
}

int subGRAPHmat(Graph G, char *v1, char *v2, char *v3){
    int a, b, c;
    a = STsearch(G->tab, v1, G->V);
    b = STsearch(G->tab, v2, G->V);
    c = STsearch(G->tab, v3, G->V);
    if(a < 0 || b < 0 || c < 0)
        return 0;
    if(G->madj[a][b] != 0 && (G->madj[a][c] != 0 || G->madj[b][c] != 0))
        return 1;
    if(G->madj[a][c] != 0 && (G->madj[a][b] != 0 || G->madj[c][b] != 0))
        return 1;
    if(G->madj[b][c] != 0 && (G->madj[b][a] != 0 || G->madj[c][a] != 0))
        return 1;
    return 0;
}

int subGRAPHlist(Graph G, char *v1, char *v2, char *v3, link *list){
    int a, b, c;
    a = STsearch(G->tab, v1, G->V);
    b = STsearch(G->tab, v2, G->V);
    c = STsearch(G->tab, v3, G->V);
    if(a < 0 || b < 0 || c < 0)
        return 0;
    if (isInList(list[a], b) && (isInList(list[a], c)|| isInList(list[b], c)))
        return 1;
    if(isInList(list[a], c) && (isInList(list[a], b) || isInList(list[c], b)) )
        return 1;
    if(isInList(list[b], c) && (isInList(list[b], a) || isInList(list[c], a)))
        return 1;
    return 0;
}

int isInList(link head, int index){
    link x;
    for(x = head; x != NULL; x = x->next)
        if(x->index == index)
            return 1;
    return 0;
}

link newNode(int index, link next){
    link x = malloc(sizeof *x);
    x->index = index;
    x->next = next;
    return x;
}

link * createLIST(Graph G){
    link *list = (link *)malloc(G->V*sizeof(link));
    for(int i = 0; i < G->V; i++)
        list[i] = NULL;
    for(int i = 0; i < G->V; i++){
        for(int j = 0; j < G->V; j++){
            if(G->madj[i][j] != 0){
                if(list[i] == NULL)
                    list[i] = newNode(j, NULL);
                else{
                    list[i] = newNode(j, list[i]);
                }
            }
        }
    }
    link x;
    for(int i = 0; i < G->V; i++){
        printf("%s: ", STsearchByIndex(G->tab, i));
        for(x = list[i]; x != NULL; x = x->next)
            printf("%s ", STsearchByIndex(G->tab, x->index));
        printf("\n");
    }
    return list;
}