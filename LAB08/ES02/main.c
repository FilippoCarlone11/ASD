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
               "[2] Verifica sottografo con matrice\n"
               "[3] Creazione lista di adiacenze e stampa della stessa\n"
               "[4] Verifica sottografo con lista\n"
               "[5] Uscita\n"
               "Selezione:");
        scanf("%d", &scelta);
        switch(scelta){
            case 1:
                GRAPHstore(G, "stdout");
                break;
            case 2:
                printf("Inserire i nomi uno dopo l'altro:");
                scanf("%s %s %s", c1, c2, c3);
                if(subGRAPHmat(G, c1, c2, c3))
                    printf("Sono un sottografo.\n");
                else
                    printf("Non sono un sottografo.\n");
                break;
            case 3:
                list = createLIST(G);
                break;
            case 4:
                printf("Inserire i nomi uno dopo l'altro:");
                scanf("%s %s %s", c1, c2, c3);
                if(subGRAPHlist(G, c1, c2, c3, list))
                    printf("Sono un sottografo.\n");
                else
                    printf("Non sono un sottografo.\n");
                break;
        }
    }while(scelta != 5);


}