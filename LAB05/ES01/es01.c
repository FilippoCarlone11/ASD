#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#define filename "att.txt"

typedef struct{
    int start;
    int end;
    int duration;
} activity;

void loadActivities(activity **lists, int *nActivities, FILE *fp);
int AreCompatible(activity a1, activity a2);
void attSel(int N, activity *v);
int powerset(int cnt, int pos, activity *lists, int *sol, int n,int *max, int **maxsol);
int isCorrect(int *sol, activity *lists, int n);
void printSOL(int *sol, activity *lists, int n);
int SumActivities(int *sol, int n, activity *lists);

int main(){
    FILE *fp;
    int nActivities;
    activity *listaAttivita;

    loadActivities(&listaAttivita, &nActivities, fp);
    attSel(nActivities, listaAttivita);

}

void loadActivities(activity **lists, int *nActivities, FILE *fp){
    fp = fopen(filename, "r");
    fscanf(fp, "%d", nActivities);
    *lists = (activity*)malloc((*nActivities)*sizeof(activity));

    for(int i = 0; i < *nActivities; i++){
        fscanf(fp, "%d %d", &((*lists)[i].start), &((*lists)[i].end));
        (*lists)[i].duration = (*lists)[i].end - (*lists)[i].start;
    }
}

int AreCompatible(activity a1, activity a2){
    if(a1.start < a2.end && a2.start < a1.end)
        return 0;
    return 1;
}

int powerset(int cnt, int pos, activity *lists, int *sol, int n, int *max, int **maxsol){
    int tempmax;
    if(pos >= n){
        if(isCorrect(sol, lists, pos)){
            tempmax = SumActivities(sol, n, lists);
            if(tempmax > *max){
                *max = tempmax;
                for(int i = 0; i < n; i++)
                    (*maxsol)[i] = sol[i];
            }
        }

        return cnt+1;
    }
    sol[pos] = 0;
    cnt = powerset(cnt, pos+1, lists, sol, n, max, maxsol);
    sol[pos] = 1;
    cnt = powerset(cnt, pos+1, lists, sol, n, max, maxsol);
    return cnt;
}

int isCorrect(int *sol, activity *lists, int n){
    int prec = -1;
    for(int i = 0; i < n; i++){
        if(sol[i]){
            if(prec == -1){

            }else if(!AreCompatible(lists[prec], lists[i])){
                return 0;
            }
            prec = i;
        }
    }
    return 1;
}
void printSOL(int *sol, activity *lists, int n){
    for(int i = 0; i < n; i++){
        if(sol[i])
            printf("(%d %d) ", lists[i].start, lists[i].end);
    }
}

int SumActivities(int *sol, int n, activity *lists){
    int count = 0;
    for(int i  = 0; i < n; i++){
        if(sol[i])
            count += lists[i].duration;
    }
    return count;
}

void attSel(int N, activity *v){
    int max = INT_MIN;
    int *sol = (int *)malloc(N*sizeof(int));
    int *maxsol = (int *)malloc(N*sizeof(int));

    powerset(0, 0, v, sol, N, &max, &maxsol);
    free(sol);
    printSOL(maxsol, v, N);
    free(maxsol);
}