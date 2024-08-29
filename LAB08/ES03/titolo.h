#ifndef ASD_TITOLO_H
#define ASD_TITOLO_H
#include "quotazioni.h"

typedef struct titolo *title;

title titleINIT(char *name);
void insertQuotation(title t, quotazione q);
void titoloStore(title t);
void TitoloFree(title t);
char *getTitleCode(title t);
quotazione searchQTbyDateForTitle(title t, time t1);

#endif //ASD_TITOLO_H
