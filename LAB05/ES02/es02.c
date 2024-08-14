#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define fileTiles "tiles.txt"
#define fileBoard "board.txt"

typedef struct{
    char colour;
    int value;
}line;

typedef struct{
    line horizontal;
    line vertical;
}tile;

void loadTiles(tile **lists, int *nTiles);
void loadBoard(int **TilesChosen, int **RotationChosen, int *row, int *column, int*blankTiles, int **board, int nTiles);
int costruzioneBoard(int *Realscacchiera, int *rotazioni, int*sol, int row, int column, tile *tessere, int ntessere);
char getVerticalColour(tile *tiles, int t, int r);
char getHorizontalColour(tile *tiles, int t, int r);
int getVerticalValue(tile *tiles, int t, int r);
int getHorizontalValue(tile *tiles, int t, int r);
int disp_semplici(int pos, int cnt, int *sol, int *mark, int k, int ntessere, int *max, int **maxsol, int *scacchiera, int *rotazioni, int row, int column, tile *tiles);
void printSOL(int *sol, int nTessere, int *scacchiera, int row, int column, int *rotazioni);

// I considered the rotated tiles as distinct tiles.
// This way, the "disp_semplici" function turned out to be very simple, but of course, this simplicity comes at the cost of increased complexity in other functions.

int main(){
    tile *tessere;
    int *DefaultTilesTaken, *TilesRotation, *defaultBoard; //The first pointer is used as "mark" considering the double symmetry (it has 2*numberOFTiles), The second stores the rotation of a single tile, the third is a pointer to the array of elements on the board
    int numberOFTiles, nEmptyTiles;
    int righe, colonne;


    loadTiles(&tessere, &numberOFTiles);
    DefaultTilesTaken = calloc(numberOFTiles*2, sizeof(int));  //At the start, no tiles are taken yet
    TilesRotation = (int *)malloc(numberOFTiles*sizeof(int));
    loadBoard(&DefaultTilesTaken, &TilesRotation, &righe, &colonne, &nEmptyTiles, &defaultBoard, numberOFTiles);


    int *sol = (int *) malloc(nEmptyTiles*sizeof(int));
    int *maxsol = (int *) malloc(nEmptyTiles*sizeof(int));
    int max = INT_MIN;
    disp_semplici(0, 0, sol, DefaultTilesTaken, nEmptyTiles, numberOFTiles, &max, &maxsol, defaultBoard, TilesRotation, righe, colonne, tessere);

    printSOL(maxsol, numberOFTiles, defaultBoard, righe, colonne, TilesRotation);

    printf("\nIl massimo e' %d", max);


    //FREE
    free(TilesRotation);
    free(DefaultTilesTaken);
    free(tessere);
    free(defaultBoard);
}

void loadTiles(tile **lists, int *nTiles){
    FILE *fp = fopen(fileTiles, "r");
    fscanf(fp, "%d", nTiles);
    *lists = (tile *)malloc((*nTiles)*sizeof(tile));

    for(int i = 0; i < *nTiles; i++){
        fscanf(fp, "%s %d %s %d", &((*lists)[i].horizontal.colour), &((*lists)[i].horizontal.value), &((*lists)[i].vertical.colour), &((*lists)[i].vertical.value));
    }
}
void loadBoard(int **TilesChosen, int **RotationChosen, int *row, int *column, int*blankTiles, int **board, int nTiles){
    int tile, rotation;
    *blankTiles = 0;
    FILE *fp = fopen(fileBoard, "r");
    fscanf(fp, "%d %d", row, column);
    *board = (int *)malloc((*row)*(*column)*sizeof(int));
    for(int i = 0; i <(*row)*(*column); i++) (*board)[i] = -1;
    for(int i = 0; i < *row; i++){
        for(int j = 0; j < *column; j++){
            fscanf(fp, "%d/%d", &tile, &rotation);
            if(tile == -1)
                (*blankTiles)++;
            else{
                (*board)[i*(*row) + j] = tile;
                (*TilesChosen)[tile] = 2; (*TilesChosen)[tile+nTiles] = 2;
                (*RotationChosen)[tile] = rotation;
            }
        }
    }

}

int costruzioneBoard(int *Realscacchiera, int *rotazioni, int*sol, int row, int column, tile *tessere, int ntessere){
    int count = 0, tempcount;
    int pos = 0;
    int *scacchiera = (int *)malloc(row*column*sizeof(int));
    for(int i = 0; i < row*column; i++) scacchiera[i] = Realscacchiera[i];

    for(int i = 0; i < row*column; i++){ //completo la scacchiera
        if(scacchiera[i] == -1){
            if(sol[pos] < ntessere) {
                scacchiera[i] = sol[pos++];
                rotazioni[scacchiera[i]] = 0;
            }else{
                scacchiera[i] = sol[pos] % ntessere;
                rotazioni[scacchiera[i]] = 1;
                pos++;
            }
        }
    }

    //ROW COUNT
    for(int j = 0; j <column; j++){
        tempcount = 0;
        char c;
        c = getVerticalColour(tessere, scacchiera[j], rotazioni[scacchiera[j]]);
        tempcount += getVerticalValue(tessere,scacchiera[j], rotazioni[scacchiera[j]]);
        for(int i = 1; i < row; i++) {
            if(c != getVerticalColour(tessere, scacchiera[i*row + j], rotazioni[scacchiera[i*row + j]])){
                tempcount = 0;
                break;
            }
            tempcount += getVerticalValue(tessere,scacchiera[i*row + j], rotazioni[scacchiera[i*row + j]]);
        }
        count += tempcount;
    }


    //COLUMN COUNT
    for(int j = 0; j <row; j++){
        tempcount = 0;
        char c;
        c = getHorizontalColour(tessere, scacchiera[j*row], rotazioni[scacchiera[j*row]]);
        tempcount += getHorizontalValue(tessere,scacchiera[j*row], rotazioni[scacchiera[j*row]]);
        for(int i = 1; i < column; i++) {
            if(c != getHorizontalColour(tessere, scacchiera[j*row + i], rotazioni[scacchiera[j*row + i]])){
                tempcount = 0;
                break;
            }
            tempcount += getHorizontalValue(tessere,scacchiera[j*row + i], rotazioni[scacchiera[j*row + i]]);
        }
        count += tempcount;
    }
    //printf("\nTotale conteggio: %d", count);
    free(scacchiera);
    return count;
}

char getVerticalColour(tile *tiles, int t, int r){
    if(r == 0){
        return tiles[t].vertical.colour;
    }else
        return tiles[t].horizontal.colour;
}

char getHorizontalColour(tile *tiles, int t, int r){
    if(r == 0){
        return tiles[t].horizontal.colour;
    }else
        return tiles[t].vertical.colour;
}

int getVerticalValue(tile *tiles, int t, int r){
    if(r == 0){
        return tiles[t].vertical.value;
    }else
        return tiles[t].horizontal.value;
}

int getHorizontalValue(tile *tiles, int t, int r){
    if(r == 0){
        return tiles[t].horizontal.value;
    }else
        return tiles[t].vertical.value;
}

int disp_semplici(int pos, int cnt, int *sol, int *mark, int k, int ntessere, int *max, int **maxsol, int *scacchiera, int *rotazioni, int row, int column, tile *tiles){
    int tempmax;
    if(pos >= k){
        tempmax = costruzioneBoard(scacchiera, rotazioni, sol, row, column, tiles, ntessere);
        if (tempmax > *max) {
            *max = tempmax;
            for (int i = 0; i < k; i++)
                (*maxsol)[i] = sol[i];
            }
        return cnt + 1;
    }
    for(int i = 0; i < ntessere*2; i++){
        if(mark[i] == 0){
            sol[pos] = i;
            mark[i]++;
            if(i<ntessere)
                mark[i+ntessere]++;
            else
                mark[i-ntessere]++;
            cnt = disp_semplici(pos+1, cnt, sol, mark, k, ntessere, max, maxsol, scacchiera, rotazioni, row, column, tiles);
            mark[i]--;
            if(i<ntessere)
                mark[i+ntessere]--;
            else
                mark[i-ntessere]--;
        }
    }
    return cnt;
}

void printSOL(int *sol, int nTessere, int *scacchiera, int row, int column, int *rotazioni){
    printf("Scacchiera finale\n");
    int pos = 0;
    for(int i = 0; i < row; i++){
        for(int j = 0; j < column; j++) {
            if (scacchiera[i * row + j] == -1)
                if (sol[pos] < nTessere) {
                    scacchiera[i * row + j] = sol[pos++];
                    rotazioni[scacchiera[i * row + j] ]=0;
                }else {
                    scacchiera[i * row + j] = sol[pos++] % nTessere;
                    rotazioni[scacchiera[i * row + j] ]=1;
                }
            printf("%d/%d ", scacchiera[i * row + j], rotazioni[scacchiera[i * row + j]]);
        }
        printf("\n");
    }
}