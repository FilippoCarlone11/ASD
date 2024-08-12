#include <stdio.h>
#include <stdlib.h>
int **loadEdge(FILE *fp, int *nodes, int *edges);
int VertexCheck(int **matrix, int *sol, int edges, int nodes);
int powerset(int cnt, int*sol, int pos, int edges, int nodes, int **matrix);

int main(void){
    int nodi, archi;
    int **matrix;
    FILE *fp = fopen("grafo.txt", "r");
    matrix = loadEdge(fp, &nodi, &archi);

    int *sol = (int*)malloc(nodi*sizeof(int));
    powerset(0, sol, 0, archi, nodi, matrix);


    //FREE data structure
    free (sol);
    for(int i = 0; i < nodi; i++)
        free(matrix[i]);
    free(matrix);
}

int **loadEdge(FILE *fp, int *nodes, int *edges){
    int **matrix;
    int node1, node2;
    fscanf(fp, "%d %d", nodes, edges);

    //create data structure
    matrix = (int**)malloc((*nodes)*sizeof(int*));
    for(int i = 0; i < *nodes; i++){
        matrix[i] = calloc(2,sizeof(int));
    }

    //database population
    for(int i = 0; i < (*edges); i++){
        fscanf(fp, "%d %d", &node1, &node2);
        matrix[i][0] = node1;
        matrix[i][1] = node2;
    }
    return matrix;
}

int VertexCheck(int **matrix, int *sol, int edges, int nodes){
    int* archi = calloc(edges, sizeof(int));

    for(int i = 0; i < nodes; i++){
        if(sol[i]){
            for(int j = 0; j < edges; j++){
                if(matrix[j][0] == i || matrix[j][1] == i)
                    archi[j]++;
            }
        }
    }
    for(int i = 0; i <edges; i++)
        if(!archi[i])
            return 0;
    free(archi);
    return 1;

}

int powerset(int cnt, int*sol, int pos, int edges, int nodes, int **matrix){ //powerset con disposizioni ripetute
    int i;
    if(pos >= nodes){
        if(VertexCheck(matrix, sol, edges, nodes)) {
            for (i = 0; i < nodes; i++)
                if (sol[i])
                    printf("%d ", i);
            printf("\n");
        }
        return cnt +1;
    }
    sol[pos] = 0;
    cnt = powerset(cnt, sol, N, pos+1, edges, nodes, matrix);
    sol[pos] = 1;
    cnt = powerset(cnt, sol, N, pos+1, edges, nodes, matrix);
    return cnt;

}