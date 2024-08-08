#include <stdio.h>
int majority(int *a, int N);
int majority_d(int *a, int l, int r, int N);
int occurrences(int*a, int l, int r, int candidate);

int main(){
    int a[] = {3,9,9,4,9,9,9};
    majority(a, 7);
}

int majority(int *a, int N){
    printf("%d", majority_d(a, 0, N, N));
}

int majority_d(int *a, int l, int r, int N){
    int m = (l+r)/2, u, v;
    if(l > r)
        return -1;
    if (l == r)
        return a[l];

    u = majority_d(a, l, m, N);
    v = majority_d(a, m+1, r, N);
    if(u == v)
        return u;
    if(occurrences(a, l, r, u)> (r-l+1)/2)
        return u;
    if(occurrences(a, l, r, v)> (r-l+1)/2)
        return v;

    return -1;
}


int occurrences(int *a, int l, int r, int candidate){ //count
    int count = 0;
    for(int i = l; i <r+1; i++)
        if(a[i] == candidate)
            count++;
    return count;
}