#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "personaggi.h"

static void storeStat(pg *p, stat_t st);
static tabPg_t *pgINIT();
void printEQUIPpg(pg *p, tabInv_t * tabInv);
pg *searchPG(tabPg_t *elencoPG);


tabPg_t *pgINIT(){
    tabPg_t *t = malloc(sizeof *t);
    t->head = NULL;
    t->tail = NULL;
    t->nPg = 0;
    return t;
}

void freetabPg(tabPg_t *t){
    linkpg p, q;
    for(p = t->head; p != NULL; p = q){
        q = p->next;
        free(p->name); free(p->code); free(p->classe);
        free(p->equip); free(p);
    }
    free(t);
}

tabPg_t *loadPG(char* filename){
    char code[MAXC], name[MAXC], classe[MAXC];
    stat_t temp;
    pg *tempP;

    FILE *fp = fopen(filename, "r");
    if(fp == NULL)
        exit(1);
    tabPg_t *elencoPG = pgINIT();

    while(fscanf(fp, "%s %s %s %d %d %d %d %d %d", code, name, classe, &(temp.hp), &(temp.mp), &(temp.atk), &(temp.def), &(temp.mag), &(temp.spr)) == 9){
        tempP = malloc(sizeof *tempP);
        tempP->equip = malloc(sizeof(tabEquip_t));
        tempP->equip->inUso = 0;
        for(int i = 0; i < 8; i++) tempP->equip->vettEq[i] = -1;
        tempP->code = strdup(code);
        tempP->name = strdup(name);
        tempP->classe = strdup(classe);
        storeStat(tempP, temp);
        if(elencoPG->head == NULL){
            elencoPG->head = elencoPG->tail = tempP;
        }else{
            elencoPG->tail->next = tempP;
            elencoPG->tail = tempP;
        }
        elencoPG->nPg++;
    }
    fclose(fp);
    return elencoPG;
}

static void storeStat(pg *p, stat_t st){
    p->pgStat.hp = st.hp;
    p->pgStat.mp = st.mp;
    p->pgStat.atk = st.atk;
    p->pgStat.def = st.def;
    p->pgStat.mag = st.mag;
    p->pgStat.spr = st.spr;
}

tabPg_t *insertPG(tabPg_t *elencoPG){
    char name[MAXC], code[MAXC], type[MAXC];
    pg *p; p = malloc(sizeof *p);


    printf("Inserire i dati riferiti al personaggio da inserire: <code> <name> <type> <hp> <mp> <atk> <def> <mag> <spr>");
    scanf("%s %s %s %d %d %d %d %d %d", code, name, type, &(p->pgStat.hp), &(p->pgStat.mp), &(p->pgStat.atk), &(p->pgStat.def), &(p->pgStat.mag), &(p->pgStat.spr));
    p->code = strdup(code);
    p->name = strdup(name);
    p->classe = strdup(type);
    p->equip = malloc(sizeof(tabEquip_t));
    for(int i = 0; i < 8; i++) p->equip->vettEq[i] = -1;
    p->equip->inUso = 0;
    if(elencoPG->head == NULL){
        elencoPG->head = elencoPG->tail = p;
    }else{
        elencoPG->tail->next = p;
        elencoPG->tail = p;
    }
    elencoPG->nPg++;
    return elencoPG;
}

tabPg_t *deletePG(tabPg_t *elencoPG){
    linkpg t, l;
    char code[MAXC];
    printf("Inserire il codice del personaggio da cancellare: ");
    scanf("%s", code);

    for(t = elencoPG->head, l = NULL; t != NULL; l = t, t = t->next){
        if(strcmp(code, t->code) == 0){
            if(t == elencoPG->head)
                elencoPG->head = elencoPG->head->next;
            else
                l->next = t->next;

            free(t->name); free(t->code); free(t->classe);
            free(t->equip); free(t);
        }
    }
    return elencoPG;
}

void printPG(pg *p, char *filename, tabInv_t *tabInv){
    FILE *fp;
    if(strcmp(filename, "stdout") == 0)
        fp = stdout;
    else
        fp = fopen(filename, "w");
    if(p == NULL)
        return;
    fprintf(fp, "%s %s %s %d %d %d %d %d %d\n", p->code, p->name, p->classe, p->pgStat.hp, p->pgStat.mp, p->pgStat.atk, p->pgStat.def, p->pgStat.mag, p->pgStat.spr);
    if(p->equip->inUso != 0){
        printf("Il suo equipaggiamento e' il seguente: \n");
        printEQUIPpg(p, tabInv);
    }
}
void printEQUIPpg(pg *p, tabInv_t * tabInv){
    if(p->equip->inUso != 0){
        for(int i = 0; i < 8; i++)
            if(p->equip->vettEq[i] != -1)
                printf("%s ", tabInv->lista[p->equip->vettEq[i]].name);
        printf("\n");
    }
}

void modifyEquip(tabPg_t *elencoPG, tabInv_t *tabInv){
    char oggetto[MAXC];
    int scelta, index, i, found = 0;
    pg *p = searchPG(elencoPG);
    printf("Vuoi aggiungere o rimuovere oggetti? (1/0)");
    scanf("%d", &scelta);

    printf("A quale elemento dell'inventario ti riferisci? ");
    scanf("%s", oggetto);

    index = getInvIndex(tabInv, oggetto);
    if(index == -1) {
        printf("Personaggio non trovato.\n");
        exit(0);
    }

    if(scelta){
        if(p->equip->inUso == 8)
            printf("Il personaggio ha guà il numero massimo di oggetti. Impossibile aggiungerne di altri.\n");
        else{
            for(i = 0; i< 8 && p->equip->vettEq[i] != -1; i++);
            p->equip->vettEq[i] = index;
            printf("Inserimento eseguito con successo.\n");
            p->equip->inUso++;
        }
    }else{
        if(p->equip->inUso == 0)
            printf("Il personaggio Non ha oggetti equipaggiati.\n");
        else{
            for(i = 0; i < 8; i++)
                if(p->equip->vettEq[i] == index) {
                    found = 1;
                    p->equip->vettEq[i] = -1;
                    printf("Rimozione eseguita con successo.\n");
                    p->equip->inUso--;
                    break;
                }
        if(!found)
            printf("Oggetto non trovato nell'elenco del guerriero.\n");
        }
    }
}

pg *searchPG(tabPg_t *elencoPG){
    linkpg x;
    char code[MAXC];
    printf("Inserire codice personaggio:");
    scanf("%s", code);
    for(x = elencoPG->head; x != NULL; x = x->next)
        if(strcmp(x->code, code) == 0)
            return x;
    return NULL;
}

void printALLPG(tabPg_t *elencoPG, tabInv_t *tabInv){
    linkpg x;
    for(x = elencoPG->head; x != NULL; x = x->next)
        printPG(x, "stdout", tabInv);
}

stat_t PGstat(tabPg_t *elencoPG, tabInv_t *tabInv){
    stat_t stat_tot;
    pg *p = searchPG(elencoPG);

    stat_tot.hp = p->pgStat.hp; stat_tot.mp = p->pgStat.mp; stat_tot.atk = p->pgStat.atk; stat_tot.def = p->pgStat.def; stat_tot.mag = p->pgStat.mag; stat_tot.spr = p->pgStat.spr;
    if(p->equip->inUso > 0)
        for(int i = 0; i < 8; i++){
            if(p->equip->vettEq[i] != -1){
                stat_tot.hp += tabInv->lista[p->equip->vettEq[i]].objStat.hp;
                stat_tot.mp += tabInv->lista[p->equip->vettEq[i]].objStat.mp;
                stat_tot.atk += tabInv->lista[p->equip->vettEq[i]].objStat.atk;
                stat_tot.def += tabInv->lista[p->equip->vettEq[i]].objStat.def;
                stat_tot.mag += tabInv->lista[p->equip->vettEq[i]].objStat.mag;
                stat_tot.spr += tabInv->lista[p->equip->vettEq[i]].objStat.spr;
            }
        }

    printf("%s %s %s %d %d %d %d %d %d\n", p->code, p->name, p->classe, (stat_tot.hp > 0) ? stat_tot.hp : 0, (stat_tot.mp > 0) ? stat_tot.mp : 0, (stat_tot.atk > 0) ? stat_tot.atk : 0, (stat_tot.def > 0) ? stat_tot.def : 0, (stat_tot.mag > 0) ? stat_tot.mag : 0, (stat_tot.spr > 0) ? stat_tot.spr : 0);

}