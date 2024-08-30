#include "titolo.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct titolo{
    char *name;
    BST qt;
};


title TITLEinit(char *name){
    title t = malloc(sizeof *t);
    t->name = strdup(name);
    t->qt = BSTinit();
    return t;
}

void TITLEinsertQT(title t, quotazione q){
    BSTinsert(t->qt, q);
}

void TITLEstore(title t){
    printf("%s ", t->name);
    BSTvisit(t->qt);
}

void TITLEfree(title t){
    BSTfree(t->qt);
    free(t);
}

char *getTITLEcode(title t){
    return t->name;
}

quotazione TITLESearchQTDate(title t, time t1){
    return BSTsearch(t->qt, t1);
}

void TITLEminQTdates(title t){
    int d, m, y;
    time t1, t2;
    printf("Inserisci la prima data nel formato yy/mm/gg:");
    scanf("%d/%d/%d", &y, &m, &d);
    t1 = setTime(y, m, d, 0, 0);
    printf("\nInserisci la seconda data nel formato yy/mm/gg:");
    scanf("%d/%d/%d", &y, &m, &d);
    t2 = setTime(y, m, d, 0, 0);

    BSTminBetweenDate(t->qt, t1, t2);
}

void TITLEminQT(title t){
    BSTmin(t->qt);
}