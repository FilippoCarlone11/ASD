#include "inventario.h"
#include "personaggi.h"

#include <stdio.h>


int main(void){
    char invfile[] = "inventario.txt", pgfile[] = "pg.txt";
    int scelta;
    tabInv_t *tabINV = loadInv(invfile);
    tabPg_t *tabPG = loadPG(pgfile);
    do {
        printf("MENU PRINCIPALE\n");
        printf("[0] Aggiungi un personaggio\n"
               "[1] Rimuovi un personaggio\n"
               "[2] Modifica l'equipaggiamento di un personaggio\n"
               "[3] Statistiche\n"
               "[4] Elenco personaggi.\n"
               "[5] Uscita.\n");
        printf("Inserire scelta:");
        scanf("%d", &scelta);

        switch(scelta) {
            case 0:
                insertPG(tabPG);
                break;
            case 1:
                deletePG(tabPG);
                break;
            case 2:
                modifyEquip(tabPG, tabINV);
                break;
            case 3:
                PGstat(tabPG, tabINV);
                break;
            case 4:
                printALLPG(tabPG, tabINV);
                break;
        }
    }while(scelta != 5);



    freetabPg(tabPG);
    InvFREE(tabINV);
}