#include <stdio.h>
#include <stdlib.h>

void LoadData(FILE *fp, int nFriends, int **nChoicesForFriends, char ****songs);
int princ_molt(int cnt, int *sol, int* nChoicesForFriends, int pos, int numberOfFriends, char ***matSongs);


int main(void){
    int numberOfFriends, checkCNT;

    //FILE ACTIVITIES
    FILE *fp = fopen("brani.txt", "r");
    fscanf(fp, "%d", &numberOfFriends);

    //LOAD DATA
    int *choicesPerFriend;
    char ***matSongs;
    LoadData(fp, numberOfFriends, &choicesPerFriend, &matSongs);


    int *sol = (int *)malloc(5*sizeof(int));
    checkCNT = princ_molt(0, sol, choicesPerFriend, 0, numberOfFriends, matSongs); //The value should be 900 (5*3*4*5*3)
    printf("%d ", checkCNT);


    //FREE
    free(sol);
    for(int i = 0; i<numberOfFriends; i++){
        for(int j = 0; j < choicesPerFriend[i]; j++)
            free(matSongs[i][j]);
        free(matSongs[i]);
    }
    free(choicesPerFriend);
    free(matSongs);
}

void LoadData(FILE *fp, int nFriends, int **nChoicesForFriends, char ****songs){
// I want to simultaneously save the number of songs chosen by each friend in nChoicesForFriends and the list of songs chosen in songs. I passed pointers to the variables because I need to return 2 data structures.
    *nChoicesForFriends = (int*)malloc(nFriends * sizeof(int));
    *songs = (char***)malloc(nFriends*sizeof(char**));

    for(int i = 0; i < nFriends; i++){
        fscanf(fp, "%d", &(*nChoicesForFriends)[i]);   // Note that "*nChoisesForFriends" is the variable I am using
        (*songs)[i] = (char**)malloc((*nChoicesForFriends)[i] * sizeof(char*));

        for(int j = 0; j < (*nChoicesForFriends)[i]; j++){
            (*songs)[i][j] = (char*) malloc(255*sizeof(char));
            fscanf(fp, "%s", (*songs)[i][j]);
        }
    }
}

int princ_molt(int cnt, int *sol, int* nChoicesForFriends, int pos, int numberOfFriends, char ***matSongs){
    int j;
    if(pos >= numberOfFriends){
        for(int i = 0; i < pos; i++){
            printf("%s ", matSongs[i][sol[i]]);
        }
        printf("\n");
        return cnt + 1;
    }
    for(j = 0; j < nChoicesForFriends[pos]; j++){  //note that I'm iterating over each friend and there is no data structure other than the variable 'j'
        sol[pos] = j;
        cnt = princ_molt(cnt, sol, nChoicesForFriends, pos+1, numberOfFriends, matSongs);
    }
    return cnt;
}