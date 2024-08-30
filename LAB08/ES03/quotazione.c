#include "quotazione.h"
#include <stdio.h>

static int isQTsetNull(quotazione q);

time getTimeQT(quotazione q){
    return q.datetime;
}

quotazione QTSetNull(){
    quotazione q;
    q.n = -1;
    q.value = -1;
    return q;
}

int isQTsetNull(quotazione q){
    if (q.n ==  -1 && q.value == -1)
        return 1;
    return 0;
}

quotazione newQT(time datetime, int value, int n){
    quotazione  q;
    q.datetime = datetime;
    q.value = value;
    q.n = n;
    return q;
}

quotazione updateQT(quotazione old, quotazione new){
    old.value += new.value;
    old.n += new.n;
    return old;
}

void storeQT(quotazione q){
    if(!isQTsetNull(q)) {
        printf("Quotazione per il giorno: ");
        dateStore(q.datetime);
        printf("%d %d\n", q.value / q.n, q.n);
    }else{
        printf("Non ci sono quotazioni per questa data\n");
    }
}

int getValueQT(quotazione q) {
    return q.value/q.n;
}