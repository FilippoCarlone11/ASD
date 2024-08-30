#ifndef ASD_TITOLO_H
#define ASD_TITOLO_H
#include "quotazioni.h"

typedef struct titolo *title;

title TITLEinit(char *name);
void TITLEinsertQT(title t, quotazione q);
void TITLEstore(title t);
void TITLEfree(title t);
char *getTITLEcode(title t);
quotazione TITLESearchQTDate(title t, time t1);
void TITLEminQTdates(title t);
void TITLEminQT(title t);

#endif //ASD_TITOLO_H
