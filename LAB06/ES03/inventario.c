
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "inventario.h"

static tabInv_t * InvINIT(int maxN);
static object_t ObjSetNull();

static tabInv_t * InvINIT(int maxN){
    tabInv_t *t = malloc(sizeof *t);
    t->lista = malloc(maxN*sizeof(object_t));
    t->maxInv = maxN;
    t->nInv = 0;
    return t;
}

void InvFREE(tabInv_t * t){
    free(t->lista);
    free(t);
}

tabInv_t *loadInv(char *filename){
    int nObj;
    char name[MAXC], type[MAXC];
    FILE *fp = fopen(filename, "r");
    if(fp == NULL)
        exit(1);
    fscanf(fp, "%d", &nObj);
    tabInv_t *elenco = InvINIT(nObj*3/2);
    elenco->nInv = nObj;
    for(int i = 0; i < nObj; i++){
        fscanf(fp, "%s %s %d %d %d %d %d %d", name, type,
               &(elenco->lista[i].objStat.hp), &(elenco->lista[i].objStat.mp), &(elenco->lista[i].objStat.atk),&(elenco->lista[i].objStat.def),
               &(elenco->lista[i].objStat.mag),&(elenco->lista[i].objStat.spr));
        elenco->lista[i].name = strdup(name);
        elenco->lista[i].type = strdup(type);
    }
    fclose(fp);
    return elenco;
}


object_t *searchByName(tabInv_t *t, char *name){
    for(int i = 0; i < t->nInv; i++){
        if(strcmp(name, t->lista[i].name) == 0)
            return &(t->lista[i]);
    }
    return NULL;
}

void printObj(char *filename, object_t *t){
    FILE *fp;
    if(strcmp(filename, "stdout") == 0)
        fp = stdout;
    else
        fp = fopen(filename, "w");
    if(t != NULL){
        fprintf(fp, "%s %s %d %d %d %d %d %d\n", t->name, t->type, t->objStat.hp, t->objStat.mp, t->objStat.atk, t->objStat.def, t->objStat.mag, t->objStat.spr);
    }
}

int getInvIndex(tabInv_t *t, char *name){
    for(int i = 0; i < t->nInv; i++){
        if(strcmp(name, t->lista[i].name) == 0)
            return i;
    }
    return -1;
}