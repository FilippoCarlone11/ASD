#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NCHAR 51

typedef struct{
    int day;
    int month;
    int year;
} date;

typedef struct {
    char code[6];
    char name[NCHAR];
    char surname[NCHAR];
    date birthdate;
    char address[NCHAR];
    char city[NCHAR];
    int CAP;
} Item;

typedef struct node *link;

struct node{
    Item val;
    link next;
};

link newNode(Item val, link next);
link SortListIns(link h, Item val);
date KEYget(Item val);
int KEYgreater(date d1, date d2);
link loadData(link head, FILE *fp);
date W2Date(char *data);
link PerifIns(link head);
Item SearchList(link head);
char *CODEget(Item val);
void printITEM(Item val);
Item ITEMsetVoid();
int isITEMnotVoid(Item x);
link FileINS(link head);
void printONfile(link head);
Item deleteFromCode(link head);
link deleteBetweenDates(link h);
Item valuesBetweenDates(link *h, date d1, date d2);


int main(){
    link h = NULL, x;
    int scelta;
    Item res = ITEMsetVoid();
    FILE *fp = fopen("anag1.txt", "r");
    h = loadData(h, fp);
    /*for(x = h; x != NULL; x = x->next)
        printf("%s ", x->val.code);*/

    do{
        printf("Le operazioni possibili sono le seguenti:\n"
               "[0] Acquisizione ed inserimento in lista da tastiera\n"
               "[1] Acquisizione ed inserimento in lista da file\n"
               "[2] Ricerca per codice\n"
               "[3] Cancellazione nodo tramite codice\n"
               "[4] Cancellazione tra date\n"
               "[5] Stampa su file\n"
               "[6] Uscita\n"
               "Digitare la scelta: ");
        scanf("%d", &scelta);
        switch(scelta){
            case 0:
                h = PerifIns(h);
                break;
            case 1:
                h = FileINS(h);
                break;
            case 2:
                res = SearchList(h);
                break;
            case 3:
                res = deleteFromCode(h);
                break;
            case 4:
                deleteBetweenDates(h);
                break;
            case 5:
                printONfile(h);
                break;
            case 6: exit(0);
            default:
                printf("valori non consentiti");
        }

        if(isITEMnotVoid(res))
            printITEM(res);
    }while(scelta != 6);



    fclose(fp);
}

link newNode(Item val, link next){
    link x = malloc(sizeof *x);
    if(x == NULL)
        return NULL;
    x->val = val;
    x->next = next;
    return x;
}

link SortListIns(link h, Item val){
    link x, p;
    if(h == NULL || KEYgreater(KEYget(h->val), KEYget(val))){
        return newNode(val, h);
    }

    for(x = h->next, p = h; x!= NULL && KEYgreater(KEYget(val), KEYget(x->val)); p = x, x = x->next);
    p->next = newNode(val, x);
    return h;
}

date KEYget(Item val){

    return val.birthdate;
}

int KEYgreater(date d1, date d2){
    if(d1.year < d2.year)
        return 1;
    else if (d1.year > d2.year)
        return 0; //-1
    else{
        if(d1.month < d2.month)
            return 1;
        else if (d1.month > d2.month)
            return 0; //-1
        else{
            if (d1.day < d2.day)
                return 1;
            else if (d1.day > d2.day)
                return 0; //-1
            return 0;
        }
    }
}

link loadData(link head, FILE *fp){

    char codice[6], nome[NCHAR], cognome[NCHAR], data[NCHAR], via[NCHAR], citta[NCHAR];
    int cap;
    while(fscanf(fp, "%s %s %s %s %s %s %d", codice, nome, cognome, data, via, citta, &cap) == 7){
        Item *x = (Item *)malloc(sizeof(Item));
        strcpy(x->code, codice);
        strcpy(x->name, nome);
        strcpy(x->surname, cognome);
        x->birthdate = W2Date(data);
        strcpy(x->address, via);
        strcpy(x->city, citta);
        x->CAP = cap;
        head = SortListIns(head, *x);
    }
        return head;
}

date W2Date(char *data){
    date d1;
    sscanf(data, "%d/%d/%d", &(d1.day), &(d1.month), &(d1.year));
    return d1;
}

link PerifIns(link head){
    char frase[NCHAR*6], data[13];
    //Item *x = malloc(sizeof( Item));
    Item x;
    printf("Inserisci i dati nel seguente formato <codice> <nome> <cognome> <data_di_nascita> <via> <citta'> <cap>");
    scanf("%s %s %s %s %[^ ] %[^ ] %d", x.code, x.name, x.surname, data, x.address, x.city, &(x.CAP));
    //sscanf(frase, "%s %s %s %s %s %s %d", x.code,  x.name, x.surname, data, x.address, x.city, &(x.CAP));
    x.birthdate = W2Date(data);
    return SortListIns(head, x);
}

Item SearchList(link head){
    link x;
    char code[6];
    printf("Inserisci il codice da ricercare: ");
    scanf("%s", code);
    for(x = head; x != NULL; x = x->next)
        if(strcmp(x->val.code, code) == 0)
            return x->val;
    return ITEMsetVoid();
}

void printITEM(Item val){
    printf("%s %s %s %d/%d/%d %s %s %d \n", val.code,  val.name, val.surname, val.birthdate.day, val.birthdate.month, val.birthdate.year, val.address, val.city, val.CAP);
}
Item ITEMsetVoid(){
    Item x;
    x.code[0] = '\0';
    return x;
}
int isITEMnotVoid(Item x){
    if(x.code[0] != '\0')
        return 1;
    return 0;
}

link FileINS(link head){
    char filename[NCHAR];
    printf("Inserisci nome file: ");
    scanf("%s", filename);
    FILE *fp = fopen(filename, "r");
    if(fp != NULL)
        head = loadData(head, fp);
    else
        printf("File non trovato!");
    return head;
}

void printONfile(link head){
    link x;
    char filename[NCHAR];
    printf("Inserisci nome file: ");
    scanf("%s", filename);
    FILE *fp = fopen(filename, "w");

    for (x = head; x != NULL; x = x->next) {
        Item val = x->val;
        fprintf(fp, "%s %s %s %d/%d/%d %s %s %d \n", val.code, val.name, val.surname, val.birthdate.day,
                val.birthdate.month, val.birthdate.year, val.address, val.city, val.CAP);
    }
    fclose(fp);
}

Item deleteFromCode(link head){
    link t, p, x;
    Item i = ITEMsetVoid();
    char codice[6];
    printf("Inserisci il codice da cancellare: ");
    scanf("%s", codice);

    for(x = head, p = NULL; x != NULL; p = x, x = x -> next){
        if(strcmp(x->val.code, codice) == 0){
            t = x;
            p->next = x->next;
            i = t->val;
            free(t);
            break;
        }
    }
    return i;
}

link deleteBetweenDates(link h){
    date d1, d2;
    char data1[13], data2[13];
    printf("Inserire la prima data nel formato gg/mm/aa: ");
    scanf("%s", data1);
    printf("Inserire la seconda data nel formato gg/mm/aa: ");
    scanf("%s", data2);
    d1 = W2Date(data1); d2 = W2Date(data2);
    Item i;
    do{
        i = valuesBetweenDates(&h, d1, d2);
        if(isITEMnotVoid(i))
            printITEM(i);
    }while(isITEMnotVoid(i));


}

Item valuesBetweenDates(link *h, date d1, date d2){
    link x, p, t;
    Item i = ITEMsetVoid();
    for(x = *h, p = NULL; x != NULL ; p = x, x = x->next){
        if(KEYgreater(d1, KEYget(x->val)) && KEYgreater(KEYget(x->val), d2)){
            t = x;
            i = t->val;
            p->next = x->next;
            free(t);
            break;
        }
    }
    return i;
}