#include "grafo.h"
#include <stdio.h>
int main(){
    Graph G = Graphload("grafo.txt");
    link *list;
    int scelta;
    char c1[MAXC], c2[MAXC], c3[MAXC];
    do{
        printf("Menu principale\n"
               "[1] Elenco Vertici con relativi archi\n"
               "[2] Verifica sottografo\n"
               "[3] Creazione lista di adiacenze e stampa della stessa\n"
               "[4] Uscita\n"
               "Selezione:");
        scanf("%d", &scelta);
        switch(scelta){
            case 1:
                break;
            case 2:
                printf("Inserire i nomi uno dopo l'altro:");
                scanf("%s %s %s", c1, c2, c3);
                if(subGRAPHmat(G, c1, c2, c3))
                    printf("Sono un sottografo.");
                else
                    printf("Non sono un sottografo");
                break;
            case 3:
                list = createLIST(G);
        }
    }while(scelta != 4);


}