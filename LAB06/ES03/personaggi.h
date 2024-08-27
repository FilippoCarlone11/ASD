#ifndef ASD_PERSONAGGI_H
#define ASD_PERSONAGGI_H

#include "inventario.h"

typedef struct pg *linkpg, pg;
typedef struct{
    int inUso;
    int vettEq[8];
} tabEquip_t;

struct pg{
    char *code;
    char *name;
    char *classe;
    tabEquip_t *equip;
    stat_t pgStat;
    linkpg next;
};

typedef struct{
    linkpg head;
    linkpg tail;
    int nPg;
} tabPg_t;

void freetabPg(tabPg_t *t);
tabPg_t *loadPG(char* filename);
tabPg_t *insertPG(tabPg_t *elencoPG);
tabPg_t *deletePG(tabPg_t *elencoPG);
void printPG(pg *p, char *filename, tabInv_t *tabInv);
void modifyEquip(tabPg_t *elencoPG, tabInv_t *tabInv);
void printALLPG(tabPg_t *elencoPG, tabInv_t *tabInv);
stat_t PGstat(tabPg_t *elencoPG, tabInv_t *tabInv);

#endif //ASD_PERSONAGGI_H
