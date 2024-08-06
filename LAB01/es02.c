#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NCHAR 31
#define NCOMMANDS 6

typedef enum  {
    r_date,
    r_partenza,
    r_capolinea,
    r_ritardo,
    r_ritardo_tot,
    r_fine
} comando_e;

typedef struct {
    char codiceTratta[7];
    char partenza[NCHAR];
    char destinazione[NCHAR];
    char data[13];
    char oraPartenza[9];
    char oraArrivo[9];
    int ritardo;
}tratta;

typedef struct {
    int day;
    int month;
    int year;
} date;

void loadTratta(tratta* Routes, FILE* fp, int numberOfRoutes);
void printCommand(char listOfCommands[NCOMMANDS][NCHAR]);
comando_e LoadCommand(char listOfCommands[NCOMMANDS][NCHAR]);
void ExecuteCommand(comando_e chosenCMD, tratta* Routes, int numberOfRoutes); //il professore la chiama selezionaDati
int dateCompare(char* dataRoutes, date d2);
date ConvertDate(char *dataRoutes);

int main(){
    // FILE LOAD
    FILE *fp;
    int n;
    fp = fopen("corse.txt", "r");
    fscanf(fp, "%d", &n);

    tratta *elencoTratte = (tratta*)malloc(n*sizeof(tratta));
    loadTratta(elencoTratte, fp, n);
    /*for(int i = 0; i < n; i++){
        printf("%s %s %s %s %s %s %d \n", elencoTratte[i].codiceTratta, elencoTratte[i].partenza, elencoTratte[i].destinazione, elencoTratte[i].data, elencoTratte[i].oraPartenza, elencoTratte[i].oraArrivo, elencoTratte[i].ritardo);
    }*/

    // COMMAND MANAGEMENT
    comando_e chosenCommand;
    char comandi[NCOMMANDS][NCHAR] = {"date", "partenza", "capolinea", "ritardo", "ritardo_tot", "fine"};
    printCommand(comandi);
    chosenCommand = LoadCommand(comandi);
    ExecuteCommand(chosenCommand, elencoTratte, n);

}

void loadTratta(tratta* Routes, FILE* fp, int numberOfRoutes){
    for(int i = 0; i < numberOfRoutes; i++){
        fscanf(fp, "%s %s %s %s %s %s %d", Routes[i].codiceTratta, Routes[i].partenza, Routes[i].destinazione, Routes[i].data, Routes[i].oraPartenza, Routes[i].oraArrivo, &(Routes[i].ritardo));
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

void ExecuteCommand(comando_e chosenCMD, tratta* Routes, int numberOfRoutes){
    date d1, d2;
    char str[NCHAR];
    switch (chosenCMD){
        case r_date:
            printf("Inserire prima data [aaaa/mm/gg]: ");
            scanf("%d/%d/%d", &d1.year,&d1.month,&d1.day);
            printf("Inserire seconda data [aaaa/mm/gg]: ");
            scanf("%d/%d/%d", &d2.year,&d2.month,&d2.day);
            break;
        case r_partenza:
            printf("Inserire luogo di partenza: ");
            scanf("%s", str);
            break;
        case r_capolinea:
            printf("Inserire luogo di arrivo: ");
            scanf("%s", str);
            break;
        case r_ritardo:
            printf("Inserire prima data [aaaa/mm/gg]: ");
            scanf("%d/%d/%d", &d1.year,&d1.month,&d1.day);
            printf("Inserire seconda data [aaaa/mm/gg]: ");
            scanf("%d/%d/%d", &d2.year,&d2.month,&d2.day);
            break;
        case r_ritardo_tot:
            printf("Inserire codice della tratta: ");
            scanf("%s", str);
            break;
    }
    printf("\n");

    // This part is completely inspired by what the professor did
    int ritardo = 0;
    for(int i = 0; i < numberOfRoutes; i++)
        switch(chosenCMD){
            case r_date:
                if (dateCompare(Routes[i].data, d1) >= 0 && dateCompare(Routes[i].data, d2) <= 0 )
                    printf("%s\n", Routes[i].codiceTratta);
                break;
            case r_partenza:
                if(strcmp(Routes[i].partenza, str) == 0)
                    printf("%s\n", Routes[i].codiceTratta);
                break;
            case r_capolinea:
                if(strcmp(Routes[i].destinazione, str) == 0)
                    printf("%s\n", Routes[i].codiceTratta);
                break;
            case r_ritardo:
                if(Routes[i].ritardo > 0)
                    if (dateCompare(Routes[i].data, d1) >= 0 && dateCompare(Routes[i].data, d2) <= 0)
                        printf("%s\n", Routes[i].codiceTratta);
                break;
            case r_ritardo_tot:
                if(strcmp(Routes[i].codiceTratta, str) == 0)
                    ritardo += Routes[i].ritardo;
                break;
        }

    if(ritardo)
        printf("Ritardo totale: %d", ritardo);

}

int dateCompare(char* dataRoutes, date d2){
    date d1 = ConvertDate(dataRoutes);
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
