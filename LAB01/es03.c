#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NCHAR 31
#define NCOMMANDS 7

typedef enum  {
    stampa,
    ordinamento_data,
    ordinamento_codT,
    ordinamento_stazioneP,
    ordinamento_stazioneA,
    ricerca,
    r_fine
} comando_e;
typedef struct {
    int day;
    int month;
    int year;
} date;

typedef struct {
    char codiceTratta[7];
    char partenza[NCHAR];
    char destinazione[NCHAR];
    date data;
    char oraPartenza[9];
    char oraArrivo[9];
    int ritardo;
}tratta;



void loadTratta(tratta* Routes, FILE* fp, int numberOfRoutes);
void printCommand(char listOfCommands[NCOMMANDS][NCHAR]);
comando_e LoadCommand(char listOfCommands[NCOMMANDS][NCHAR]);
void ExecuteCommand(comando_e chosenCMD, tratta* Routes, int numberOfRoutes); //il professore la chiama selezionaDati
int dateCompare(date d1, date d2);
date ConvertDate(char *dataRoutes);

void stampaDati(tratta* Routes, int numberOfRoutes);
void DataOrder(tratta* Routes, int numberOfRoutes);
void CodTOrder(tratta* Routes, int numberOfRoutes);
void stazOrder(tratta* Routes, int numberOfRoutes, int k);
void LinearSearch(tratta* Routes, int numberOfRoutes);
void stampaStazione(tratta stazione);
void DicotomicSearch(tratta* Routes, int numberOfRoutes);
void OrderForDicotomicSearch(tratta **Routes, int numberOfRoutes);
void realDicSearch(int l, int r, tratta *Routes, char *stazione, int stazlen);
void Search(tratta* Routes, int numberOfRoutes);

//I have omitted ordering by hour because it is symmetric to the date. Unlike the teacher's solution, I give the user the choice of which search to use and i don't use a struct wrapper.

int main(){
    // FILE LOAD
    FILE *fp;
    int n;
    fp = fopen("corse.txt", "r");
    fscanf(fp, "%d", &n);

    tratta *elencoTratte = (tratta*)malloc(n*sizeof(tratta));
    loadTratta(elencoTratte, fp, n);


    // COMMAND MANAGEMENT
    comando_e chosenCommand;
    char comandi[NCOMMANDS][NCHAR] = {"stampa", "ordinamento_data", "ordinamento_codTratta", "ordinamento_stazioneP", "ordinamento_stazioneA","ricerca", "fine"};
    printCommand(comandi);
    chosenCommand = LoadCommand(comandi);
    ExecuteCommand(chosenCommand, elencoTratte, n);

}

void loadTratta(tratta* Routes, FILE* fp, int numberOfRoutes){
    char data[11];
    for(int i = 0; i < numberOfRoutes; i++){
        fscanf(fp, "%s %s %s %s %s %s %d", Routes[i].codiceTratta, Routes[i].partenza, Routes[i].destinazione, data, Routes[i].oraPartenza, Routes[i].oraArrivo, &(Routes[i].ritardo));
        Routes[i].data = ConvertDate(data);
    }

}
void printCommand(char listOfCommands[NCOMMANDS][NCHAR]){
    printf("I comandi che possono essere eseguiti sono i seguenti: \n");
    for(int i = 0; i < NCOMMANDS; i++) printf("%s \n", listOfCommands[i]);
}

comando_e LoadCommand(char listOfCommands[NCOMMANDS][NCHAR]){
    char chosenCommand[NCHAR];
    printf("Seleziona il comando: ");
    scanf("%s", chosenCommand);
    //I need the id of the chosen command. for do this, I have to scan every element in the array of commands
    for(int i = 0; i < NCOMMANDS; i++)
        if(strcmp(listOfCommands[i], chosenCommand) == 0)
            return (comando_e) i;  //this is an explicit cast, otherwise I can create another function to do this
    return -1;
}

void ExecuteCommand(comando_e chosenCMD, tratta* Routes, int numberOfRoutes) {
    switch (chosenCMD) {
        case stampa:
            stampaDati(Routes, numberOfRoutes);
            break;
        case ordinamento_data:
            DataOrder(Routes, numberOfRoutes);
            break;
        case ordinamento_codT:
            CodTOrder(Routes, numberOfRoutes);
            break;
        case ordinamento_stazioneP:
            stazOrder(Routes, numberOfRoutes, 1);
            break;
        case ordinamento_stazioneA:
            stazOrder(Routes, numberOfRoutes, 0);
            break;
        case ricerca:
            Search(Routes, numberOfRoutes);
            DicotomicSearch(Routes, numberOfRoutes);
            break;

    }
}

int dateCompare(date d1, date d2){
    if (d1.year > d2.year)
        return 1;
    else if (d1.year < d2.year)
        return -1;
    else{
        if(d1.month > d2.month)
            return 1;
        else if(d1.month < d2.month)
            return -1;
        else{
            if(d1.day > d2.day)
                return 1;
            else if (d1.day < d2.day)
                return -1;
            else
                return 0;
        }
    }
}

date ConvertDate(char *dataRoutes){
    date d1;
    sscanf(dataRoutes, "%d/%d/%d", &d1.year, &d1.month, &d1.day);
    return d1;
}

void stampaDati(tratta* Routes, int numberOfRoutes){
    for(int i = 0; i < numberOfRoutes; i++)
        printf("%s %s %s %d/%d/%d %s %s %d \n", Routes[i].codiceTratta, Routes[i].partenza, Routes[i].destinazione, Routes[i].data.year, Routes[i].data.month, Routes[i].data.day, Routes[i].oraPartenza, Routes[i].oraArrivo, Routes[i].ritardo);
}

void DataOrder(tratta* Routes, int numberOfRoutes){
    tratta swapVar;
    for(int i = 0; i < numberOfRoutes; i++){
        for(int j = 0; j < numberOfRoutes -1 -i; j++){
            if(dateCompare(Routes[j].data, Routes[j+1].data) >0){
                swapVar = Routes[j];
                Routes[j] = Routes[j+1];
                Routes[j+1] = swapVar;
            }
        }
    }
    stampaDati(Routes, numberOfRoutes);
}

void CodTOrder(tratta* Routes, int numberOfRoutes){
    tratta swapVar;
    for(int i = 0; i < numberOfRoutes; i++){
        for(int j = 0; j < numberOfRoutes -1 -i; j++){
            if(strcmp(Routes[j].codiceTratta, Routes[j+1].codiceTratta) >0){
                swapVar = Routes[j];
                Routes[j] = Routes[j+1];
                Routes[j+1] = swapVar;
            }
        }
    }
    stampaDati(Routes, numberOfRoutes);
}

void stazOrder(tratta* Routes, int numberOfRoutes, int k){
    tratta swapVar;
    if(k){
        for(int i = 0; i < numberOfRoutes; i++){
            for(int j = 0; j < numberOfRoutes -1-i; j++){
                    if(strcmp(Routes[j].partenza, Routes[j+1].partenza) >0){
                        swapVar = Routes[j];
                        Routes[j] = Routes[j+1];
                        Routes[j+1] = swapVar;
                    }
            }
        }
    }else{
        for(int i = 0; i < numberOfRoutes; i++){
            for(int j = 0; j < numberOfRoutes-1-i; j++){
                    if(strcmp(Routes[j].destinazione, Routes[j+1].destinazione) >0){
                        swapVar = Routes[j];
                        Routes[j] = Routes[j+1];
                        Routes[j+1] = swapVar;
                    }
            }
        }
    }
    stampaDati(Routes, numberOfRoutes);
}

void LinearSearch(tratta* Routes, int numberOfRoutes){
    int stazlen;
    char stazione[NCHAR];
    printf("inserire nome da ricercare: ");
    scanf("%s", stazione);
    stazlen = strlen(stazione);

    for(int i = 0; i < numberOfRoutes; i++){
        if(strncmp(Routes[i].partenza, stazione, stazlen) == 0)
            stampaStazione(Routes[i]);
    }
}
void stampaStazione(tratta stazione){
    printf("%s %s %s %d/%d/%d %s %s %d \n", stazione.codiceTratta, stazione.partenza, stazione.destinazione, stazione.data.year, stazione.data.month, stazione.data.day, stazione.oraPartenza, stazione.oraArrivo, stazione.ritardo);
}

void DicotomicSearch(tratta* Routes, int numberOfRoutes){
    int stazlen;
    char stazione[NCHAR];
    printf("inserire nome da ricercare: ");
    scanf("%s", stazione);
    stazlen = strlen(stazione);
    OrderForDicotomicSearch(&Routes, numberOfRoutes);
    realDicSearch(0, numberOfRoutes, Routes, stazione, stazlen);

}
void OrderForDicotomicSearch(tratta **Routes, int numberOfRoutes){
    tratta swapVar;
    for(int i = 0; i < numberOfRoutes; i++){
        for(int j = 0; j < numberOfRoutes -1-i; j++){
            if(strcmp((*Routes)[j].partenza, (*Routes)[j+1].partenza) >0){
                swapVar = (*Routes)[j];
                (*Routes)[j] = (*Routes)[j+1];
                (*Routes)[j+1] = swapVar;
            }
        }
    }
}
void realDicSearch(int l, int r, tratta *Routes, char *stazione, int stazlen){
    int m = (l+r)/2;
    if (l> r){
        return;
    }

    if(strncmp(Routes[m].partenza, stazione, stazlen) == 0){
        stampaStazione(Routes[m]);
    }

    if(strncmp(Routes[m].partenza, stazione, stazlen) > 0)
        realDicSearch(l, m-1, Routes, stazione, stazlen);
    realDicSearch(m+1, r, Routes, stazione, stazlen);
}

void Search(tratta* Routes, int numberOfRoutes){
    int x;
    printf("Selezionare il tipo di ricerca da fare:\n"
           "Dicotomica[0] o Lineare [1] : ");
    scanf("%d", &x);
    if(x)
        LinearSearch(Routes, numberOfRoutes);
    else
        DicotomicSearch(Routes, numberOfRoutes);
}