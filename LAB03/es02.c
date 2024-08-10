#include <stdio.h>
#include <stdlib.h>

void LoadData(FILE *fp, int nFriends, int **FriendsChosen, char ****songs);
int princ_molt(int cnt, int *sol, int* FriendsChosen, int pos, int numberOfFriends, char ***matSongs);
int main(void){
    FILE *fp = fopen("brani.txt", "r");
    int numberOfFriends, cntmolt;
    int *nScelte;
    char ***matSongs;
    fscanf(fp, "%d", &numberOfFriends);
    LoadData(fp, numberOfFriends, &nScelte, &matSongs);

   /* for(int i = 0; i< numberOfFriends; i++) {
        for (int j = 0; j < nScelte[i]; j++)
            printf("%s ", matSongs[i][j]);
        printf("\n");
    }*/
   int *sol = (int *)malloc(5*sizeof(int));

   cntmolt = princ_molt(0, sol, nScelte, 0, numberOfFriends, matSongs);
   printf("%d ", cntmolt);
}

void LoadData(FILE *fp, int nFriends, int **FriendsChosen, char ****songs){
    *FriendsChosen = (int*)malloc(nFriends * sizeof(int));
    *songs = (char***)malloc(nFriends*sizeof(char**));

    for(int i = 0; i < nFriends; i++){
        fscanf(fp, "%d", &(*FriendsChosen)[i]);
        (*songs)[i] = (char**)malloc((*FriendsChosen)[i] * sizeof(char*));

        for(int j = 0; j < (*FriendsChosen)[i]; j++){
            (*songs)[i][j] = (char*) malloc(255*sizeof(char));
            fscanf(fp, "%s", (*songs)[i][j]);
        }
    }
}

int princ_molt(int cnt, int *sol, int* FriendsChosen, int pos, int numberOfFriends, char ***matSongs){
    int j;
    if(pos >= numberOfFriends){
        for(int i = 0; i < pos; i++){
            printf("%s ", matSongs[i][sol[i]]);
        }
        printf("\n");
        return cnt + 1;
    }
    for(j = 0; j < FriendsChosen[pos]; j++){
        sol[pos] = j;
        cnt = princ_molt(cnt, sol, FriendsChosen, pos+1, numberOfFriends, matSongs);
    }
    return cnt;
}