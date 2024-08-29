#include "titoli.h"
#include <stdio.h>

int main(){
    int scelta;
    Titoli t;
    t = titoliLOADwp();
    operations(t);
    //Titolistore(t);

    /*do{
        printf("Menu principale\n");
        printf("[0] Acquisizione da file\n"
               "[1] Ricerca titolo azionario\n"
               "[2] Uscita\n"
               "Inserire scelta:");
        scanf("%d", &scelta);
        switch(scelta){
            case 0:
                t = titoliLOADwp();
                break;
            case 1:
                operations(t);
        }
    }while(scelta != 2);*/

    TITOLIfree(t);
}