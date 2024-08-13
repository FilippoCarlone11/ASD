#include <stdio.h>
#include <stdlib.h>
#define filename "easy_test_set.txt"
#define NTYPEMATERIALS 4

int isCorrect(int* sol, int succ, int pos);
void loadMaterials(FILE *fp, int **materials);

int disp_rip(int pos, int k, int *sol, int *materials, int cnt, int *stop);
int countZaffiri(int *sol, int k);
int countRubini(int *sol, int k);
int countTopazi(int *sol, int k);
int countSmeraldi(int *sol, int k);
int Speranza(int *materials, int candidato);

int main(){
    int nTest, sommaMateriali = 0, stop;
    //int *materials = (int *)malloc(NTYPEMATERIALS *sizeof(int));
    FILE *fp = fopen(filename, "r");
    fscanf(fp, "%d", &nTest);
    int* sol = (int*) malloc(70*sizeof(int));
    int **materiali = (int**)malloc(nTest*sizeof(int*));
    for(int j = 0; j < 70; j++) sol[j] = -1;

    for(int k = 0; k <nTest; k++){
        materiali[k] =(int*) malloc(4*sizeof(int));
        loadMaterials(fp, materiali +k);
    }

    for(int k = 1; k <= nTest; k++){
            stop = 0;
            //printf( "TEST N.%d\n", k);
            //loadMaterials(fp, &materials);
            for(int i = 0; i <NTYPEMATERIALS; i++)
                sommaMateriali += materiali[k-1][i];

            for(int i = sommaMateriali; i > 1 && !stop; i--){
                if(disp_rip(0, i, sol, materiali[k-1], 0, &stop)){
                    //printf("Numero totale materiali utilizzati: %d\n", i);
                    //printf("Zaffiri: %d/%d Rubini: %d/%d Topazi: %d/%d Smeraldi: %d/%d", countZaffiri(sol, i), materials[0], countRubini(sol, i), materials[1], countTopazi(sol, i), materials[2],countSmeraldi(sol, i), materials[3]);
                    //for(int l = 0; l < i; l++) printf("%d ", sol[l]);
                }
            }
    }
    free(sol);
}

int isCorrect(int* sol, int succ, int pos){
    if(pos == 0)
        return 1;
    if(sol[pos-1] == 0) {
        if (succ == 0 || succ == 1)
            return 1;
        else
            return 0;
    }else if(sol[pos-1] == 1) {
        if (succ == 2 || succ == 3)
            return 1;
        else
            return 0;
    }else if(sol[pos-1] == 2) {
        if (succ == 0 || succ == 1)
            return 1;
        else
            return 0;
    }else if(sol[pos-1] == 3) {
        if (succ == 3 || succ == 2)
            return 1;
        else
            return 0;
    }
    return 0;
}

void loadMaterials(FILE *fp, int **materials){
    if(fp == NULL)
        printf("File non trovato.");
    fscanf(fp, "%d %d %d %d", &((*materials)[0]), &((*materials)[1]), &((*materials)[2]), &((*materials)[3]));
}

int disp_rip(int pos, int k, int *sol, int *materials, int cnt, int *stop){
    if(pos >= k){
        *stop = 1;
        return cnt+1;
    }
    for(int i = 0; i < NTYPEMATERIALS &&!(*stop); i++){
        if(materials[i] > 0 && Speranza(materials, i)){
            if(isCorrect(sol, i, pos)){
                sol[pos] = i;
                --materials[i];
                cnt = disp_rip(pos + 1, k, sol, materials, cnt, stop);
                ++materials[i];
            }

        }
    }
    return cnt;
}

int Speranza(int *materials, int candidato){

    if(candidato == 0) {
        if (materials[0] > 0 || materials[1] > 0)
            return 1;
        else
            return 0;
    }else if(candidato == 1){
        if(materials[2] > 0 || materials[3] > 0)
            return 1;
        else
            return 0;
    }else if(candidato == 2){
        if(materials[0] > 0 || materials[1] > 0)
            return 1;
        else
            return 0;
    }if(candidato == 3){
        if(materials[3] > 0 || materials[2] > 0)
            return 1;
        else
            return 0;
    }else
        return 0;

}