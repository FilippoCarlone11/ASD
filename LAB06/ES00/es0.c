#include <stdio.h>
#include <stdlib.h>

int max(int a, int b); //return 1 if a > b
void solveDP (int *val, int n);
void displaySol(int *opt, int n, int *val);
int main(){
    int val[8] = {0, 14,22,13,25,30,11,90};
    int n = 7;
    solveDP(val, n);
}

void solveDP (int *val, int n){
    int *opt;
    opt = calloc(n+1, sizeof(int));
    opt[1] = val[1];
    for(int i = 2; i <= n; i++){
        if(max(opt[i-2]+val[i], opt[i-1]))
            opt[i] = opt[i-2]+val[i];
        else
            opt[i] = opt[i-1];
    }

    displaySol(opt, n, val);
    free(opt);
}

void displaySol(int *opt, int n, int *val){
    int i = n;
    int *sol;
    sol = calloc(n+1, sizeof(int));
    sol[1] = 1;
    while (i > 0){
        if(opt[i] == opt[i-1])
            sol[i] = 0;
        else if(opt[i] == (opt[i-2] + val[i])) {
            sol[i] = 1;
            sol[i - 1] = 0;
            i--;
        }
        i--;
    }
    printf("Il numero massimo di persone coperte e' %d\n", opt[n]);
    printf("Sono state prese le seguenti stazioni: \n");
    for(int i = 1; i <= n; i++)
        if(sol[i])
            printf("%d ", i);
    free(sol);
}

int max(int a, int b){
    return (a > b);
}