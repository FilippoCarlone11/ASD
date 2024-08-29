#ifndef ASD_QUOTAZIONE_H
#define ASD_QUOTAZIONE_H

#include "time.h"

typedef struct {
    time datetime;
    int value;
    int n;
} quotazione;

quotazione qSetNull();
quotazione UpdateQT(quotazione old, quotazione new);
quotazione newQ(time datetime, int value, int n);
time getTime(quotazione q);
void quotazioneStore(quotazione q);
int getQValue(quotazione q);


#endif //ASD_QUOTAZIONE_H
