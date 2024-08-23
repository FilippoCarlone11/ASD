#include <stdio.h>
#include <stdlib.h>

#define infile "att.txt"

typedef struct{
    int start;
    int end;
    int duration;
} activity;

int compatible(activity a1, activity a2);
activity *loadActivities(FILE *fp, int n);
void LongestActivitySequence(activity *a, int n);
void displaySol(int *sol, int n, activity *a);
void sort(activity **a, int n);
void bubbleSort(activity **a, int n); //Andata usato un O(nlogn)

int main(){
    int nActivities;
    FILE *fp; fp = fopen(infile, "r");
    fscanf(fp, "%d", &nActivities);
    activity *a = loadActivities(fp, nActivities);

    sort(&a, nActivities);

    LongestActivitySequence(a, nActivities);
    free(a);
}

activity *loadActivities(FILE *fp, int n){
    activity *a;
    a = (activity *)malloc(n*sizeof(activity));
    for(int i = 0; i < n; i++) {
        fscanf(fp, "%d %d", &(a[i].start), &(a[i].end));
        a[i].duration = a[i].end - a[i].start;
    }
    return a;
}

void LongestActivitySequence(activity *a, int n){
    int k = 0;
    int *sol;
    sol = calloc(n,sizeof(int));
    sol[0] = 1;
    for(int i = 0; i < n; i++){
        if(compatible(a[i], a[k])){
            sol[i] = 1;
            k = i;
        }
    }
    displaySol(sol, n, a);
    free(sol);
}

void displaySol(int *sol, int n, activity *a){
    printf("soluzione:\n");
    for(int i = 0; i < n; i++)
        if(sol[i])
            printf("(%d, %d) ", a[i].start, a[i].end);
}

void sort(activity **a, int n){
    bubbleSort(a, n);
}

void bubbleSort(activity **a, int n){
    activity temp;
    for(int i = 0; i < n; i++){
        for(int j = 0; j <n-1-i; j++){
            if((*a)[j+1].duration > (*a)[j].duration){
                temp = (*a)[j];
                (*a)[j] = (*a)[j+1];
                (*a)[j+1] = temp;
            }
        }
    }
}

int compatible(activity a, activity b){
    if(a.start < b.end && b.start < a.end)
        return 0;
    return 1;
}