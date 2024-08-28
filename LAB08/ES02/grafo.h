#ifndef ASD_GRAFO_H
#define ASD_GRAFO_H
#define MAXC 30

typedef struct{
    char *elab;
    char *network;
} node;

typedef node* ST;

typedef struct edge{
    int v;
    int w;
    int wt;
} Edge;


typedef struct itemnode *link;
struct itemnode{
    int index;
    link next;
};

typedef struct graph *Graph;
void GRAPHstore(Graph G, char *filename);
Graph Graphload(char *filename);
int subGRAPHmat(Graph G, char *v1, char *v2, char *v3);
link * createLIST(Graph G);


#endif //ASD_GRAFO_H
