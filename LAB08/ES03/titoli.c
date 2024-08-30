#include "titoli.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAXC 10

typedef struct nodeTitolo *linktitolo;

struct nodeTitolo{
    title t;
    linktitolo next;
};

struct titoli{
    linktitolo head;
    int nTitoli;
};

static linktitolo newTitoloNode(title t, linktitolo next);
static title searchTitle(Titoli t, char *code);
static Titoli TITOLIinit();

static linktitolo newTitoloNode(title t, linktitolo next){
    linktitolo x = malloc(sizeof *x);
    x->t = t;
    x->next = next;
    return x;
}

static Titoli TITOLIinit(){
    Titoli t = malloc(sizeof *t);
    t->head = NULL;
    t->nTitoli = 0;
    return t;
}

Titoli titoliLOAD(char *filename){
    int nTitoli, nTransazioni, valore, nPezzi, y, m, d, h, min;
    char code[MAXC];

    Titoli collT = TITOLIinit();

    FILE *fp = fopen(filename, "r");
    if(fp == NULL){
        printf("Problemi con l'apertura del file");
        return NULL;
    }

    fscanf(fp, "%d", &nTitoli);

    for(int i = 0; i < nTitoli; i++){
        fscanf(fp, "%s %d", code, &nTransazioni);
        title t = TITLEinit(code);
        collT->nTitoli++;
        for(int j = 0; j < nTransazioni; j++){
            fscanf(fp, "%d/%d/%d %d:%d %d %d", &y, &m, &d, &h, &min, &valore, &nPezzi);
            quotazione q = newQT(setTime(y, m, d, h, min), valore*nPezzi, nPezzi);
            TITLEinsertQT(t, q);
        }
        if(collT->head == NULL)
            collT->head = newTitoloNode(t, NULL);
        else{
            collT->head = newTitoloNode(t, collT->head);
        }
    }
    return collT;
}

void TITOLIstore(Titoli t){
    linktitolo x;
    for(x = t->head; x != NULL; x = x->next){
        TITLEstore(x->t);
    }
}

void TITOLIfree(Titoli t){
    linktitolo x, y;
    for(x = t->head; x != NULL; x = y){
        y = x->next;
        TITLEfree(x->t);
        free(x);
    }

    free(t);
}

Titoli TITOLIloadwp(){
    char filename[MAXC];
    printf("Inserire nome file:");
    scanf("%s", filename);
    return titoliLOAD(filename);
}

static title searchTitle(Titoli t, char *code){
    linktitolo x;
    for(x = t->head; x != NULL; x = x->next)
        if(strcmp(getTITLEcode(x->t), code) == 0)
            return x->t;
    return NULL;
}

void operations(Titoli t){
    int scelta;
    char code[MAXC];
    time t1;
    int y, m, d;

    printf("Inserire nome titolo da ricercare:");
    scanf("%s", code);
    title x = searchTitle(t, code);
    if(x == NULL) {
        printf("Titolo non trovato.");
        return;
    }
    printf("Titolo trovato.\n");
    do{
        printf("Scegliere quale operazione svolgere: \n"
               "[0] Ricerca quotazione di una certa data\n"
               "[1] Ricerca quotazione minima e massima tra due date.\n"
               "[2] Ricerca quotazione minima e massima\n"
               "[3] Bilanciamento albero.\n"
               "[4] Uscita.\n"
               "Inserire scelta:");
        scanf("%d", &scelta);

        switch(scelta){
            case 0:
                printf("Inserire la data nel seguente formato: yy/mm/gg:");
                scanf("%d/%d/%d", &y, &m, &d);
                t1 = setTime(y, m, d, 0, 0);
                storeQT(TITLESearchQTDate(x, t1));
                break;
            case 1:
                TITLEminQTdates(x);
                break;
            case 2:
                TITLEminQT(x);
                break;
            case 3:
                break;
        }
    }while (scelta != 4);
}