#ifndef ASD_QUOTAZIONE_H
#define ASD_QUOTAZIONE_H

#include "time.h"

typedef struct {
    time datetime;
    int value;
    int n;
} quotazione;

quotazione QTSetNull();
quotazione updateQT(quotazione old, quotazione new);
quotazione newQT(time datetime, int value, int n);
time getTimeQT(quotazione q);
void storeQT(quotazione q);
int getValueQT(quotazione q);


#endif //ASD_QUOTAZIONE_H
