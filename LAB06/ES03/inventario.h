//
// Created by carlo on 27/08/2024.
//

#ifndef ASD_INVENTARIO_H
#define ASD_INVENTARIO_H
#define MAXC 50
typedef struct{
    int hp;
    int mp;
    int atk;
    int def;
    int mag;
    int spr;
} stat_t;

typedef struct{
    char *name;
    char *type;
    stat_t objStat;
} object_t;

typedef struct{
    object_t *lista;
    int nInv;
    int maxInv;
} tabInv_t;

void InvFREE(tabInv_t * t);
tabInv_t *loadInv(char *filename);
void printObj(char *filename, object_t *t);
object_t *searchByName(tabInv_t *t, char *name);
int getInvIndex(tabInv_t *t, char *name);

#endif //ASD_INVENTARIO_H
