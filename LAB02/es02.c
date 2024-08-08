#include <stdio.h>
#include <stdlib.h>
void malloc2dP(int ***mat, FILE* fp, int row, int column);
void separa(int **mat, int row, int column, int **black, int **white);
void stampaCaselle(int *caselle, int nCaselle);
void freeMAT(int **mat, int row);
int main(){
    int **mat;
    FILE *fp = fopen("mat.txt", "r");
    int row, column;
    fscanf(fp, "%d %d", &row, &column);

    malloc2dP(&mat, fp, row, column);

    int *black, *white;
    separa(mat, row, column, &black, &white);

    // print chess squares
    printf("Posizioni bianche: ");
    stampaCaselle(white, row*column/2 +1);
    printf("Posizioni nere: ");
    stampaCaselle(black, (row*column)/2);


    //FREE
    freeMAT(mat, row);
    free(black);
    free(white);
}

void malloc2dP(int ***mat, FILE* fp, int row, int column){
    *mat = (int**) malloc(row * sizeof(int *));
    for(int i = 0; i < row; i++){
        (*mat)[i] = (int*)malloc(column*sizeof(int));
    }

    for(int i = 0; i < row; i++)
        for(int j = 0; j < column; j++)
            fscanf(fp, "%d", &((*mat)[i][j]));  //I use this syntax because I need the pointer to mat[i][j], which is &(mat[i][j]). Howewer I only have a pointer to mat -> (*mat) instead
}

void separa(int **mat, int row, int column, int **black, int **white){
    *black = (int*) malloc(((row*column)/2)*sizeof(int));
    *white = (int*) malloc(((row*column)/2)*sizeof(int));
    int nWhite = 0, nBlack = 0;

    for(int i = 0; i < row; i++){
        for(int j = 0; j < column; j++){
            if((i*column + j) % 2 == 0) //in this way, I can alternate between white and black
                (*white)[nWhite++] = mat[i][j];
            else
                (*black)[nBlack++] = mat[i][j];
        }
    }
}
void stampaCaselle(int *caselle, int nCaselle){
    for(int i = 0; i <nCaselle; i++)
        printf("%d ", caselle[i]);
}

void freeMAT(int **mat, int row){
    for(int i = 0; i < row; i++)
        free(mat[i]);
    free(mat);
}