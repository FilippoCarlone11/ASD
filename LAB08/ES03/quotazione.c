#include "quotazione.h"
#include <stdio.h>

time getTime(quotazione q){
    return q.datetime;
}

quotazione qSetNull(){
    quotazione q;
    q.n = -1;
    q.value = -1;
    return q;
}

int isQsetNull(quotazione q){
    if (q.n ==  -1 && q.value == -1)
        return 1;
    return 0;
}

quotazione newQ(time datetime, int value, int n){
    quotazione  q;
    q.datetime = datetime;
    q.value = value;
    q.n = n;
    return q;
}

quotazione UpdateQT(quotazione old, quotazione new){
    old.value += new.value;
    old.n += new.n;
    return old;
}

void quotazioneStore(quotazione q){
    if(!isQsetNull(q)) {
        printf("Quotazione per il giorno: ");
        dateStore(q.datetime);
        printf("%d %d\n", q.value / q.n, q.n);
    }else{
        printf("Non ci sono quotazioni per questa data\n");
    }
}

int getQValue(quotazione q) {
    return q.value/q.n;
}