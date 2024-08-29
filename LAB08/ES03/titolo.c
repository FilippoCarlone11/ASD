#include "titolo.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct titolo{
    char *name;
    BST qt;
};


title titleINIT(char *name){
    title t = malloc(sizeof *t);
    t->name = strdup(name);
    t->qt = BSTinit();
    return t;
}

void insertQuotation(title t, quotazione q){
    BSTinsert(t->qt, q);
}

void titoloStore(title t){
    printf("%s ", t->name);
    BSTvisit(t->qt);
}

void TitoloFree(title t){
    BSTfree(t->qt);
    free(t);
}

char *getTitleCode(title t){
    return t->name;
}

quotazione searchQTbyDateForTitle(title t, time t1){
    return BSTsearch(t->qt, t1);
}