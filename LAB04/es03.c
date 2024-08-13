#include <stdio.h>
#include <stdlib.h>
#define filename "hard_test_set.txt"
#define NTYPEMATERIALS 4

int isCorrect(int* sol, int succ, int pos);
void loadMaterials(FILE *fp, int **materials);

int disp_rip(int pos, int k, int *sol, int *materials, int cnt, int *stop);
int Speranza(int *materials, int candidato);

int main(){
    //VAR DECLARATION
    int nTest, stop,sol[75];
    int *sommaMateriali;

    //FILE VAR DECLARATION
    FILE *fp = fopen(filename, "r");
    fscanf(fp, "%d", &nTest);

    //DATA STRUCTURES FOR QUANTITY
    int **materiali = (int**) malloc(nTest*sizeof(int*));
    sommaMateriali = calloc(nTest,sizeof(int));
    int *results = (int*)malloc(nTest*sizeof(int));

    for(int k = 0; k <nTest; k++){
        materiali[k] =(int*) malloc(NTYPEMATERIALS*sizeof(int));
        loadMaterials(fp, materiali +k);
        for(int i = 0; i < NTYPEMATERIALS; i++)
            sommaMateriali[k] += materiali[k][i];
    }

    for(int k = 0; k < nTest; k++){
        printf("%d\n", k);
            stop = 0;
            for(int i = sommaMateriali[k]; i > 1 && !stop; i--)
                if(disp_rip(0, i, sol, materiali[k], 0, &stop)){
                    results[k] = i;
                    break;
                }
    }

    for(int i = 0; i < nTest;i++){
        printf( "TEST N.%d\n", i+1);
        printf("Numero totale materiali utilizzati: %d\n", results[i]);
    }

    //FREE
    free(results);
    free(sommaMateriali);
    for(int i =0; i<nTest;i++)
        free(materiali[i]);
    free(materiali);
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
        if(materials[i] > 0 && Speranza(materials, i) && isCorrect(sol, i, pos)){
                sol[pos] = i;
                --materials[i];
                cnt = disp_rip(pos + 1, k, sol, materials, cnt, stop);
                ++materials[i];
        }
    }
    return cnt;
}

int Speranza(int *materials, int candidato){  // This function is used for pruning. It returns 1 if the current choice has the potential to continue the chain.
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

//TEMPI
//very very easy : istantaneo
//very easy : istantaneo
//easy : 15s
//hard : >6min