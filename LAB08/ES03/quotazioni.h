#ifndef ASD_QUOTAZIONI_H
#define ASD_QUOTAZIONI_H
#include "quotazione.h"
typedef struct binarysearchtree *BST;

BST BSTinit();
void BSTinsert(BST b, quotazione q);
void BSTvisit(BST b);
void BSTfree(BST b);
quotazione BSTsearch(BST b, time t);
void BSTminBetweenDate(BST b, time t1, time t2);
void BSTmin(BST b);

#endif //ASD_QUOTAZIONI_H
