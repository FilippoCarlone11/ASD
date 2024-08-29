#include "time.h"
#include <stdio.h>

time setTime(int year, int month, int day, int hour, int min){
    time t;
    t.year = year; t.month = month; t.day = day; t.hour = hour; t.min = min;
    return t;
}

int DateCompare(time t1, time t2){
    if(t1.year < t2.year)
        return 1;
    else if(t1.year > t2.year)
        return -1;
    else{
        if(t1.month < t2.month)
            return 1;
        else if(t1.month >t2.month)
            return -1;
        else{
            if(t1.day < t2.day)
                return 1;
            else if(t1.day > t2.day)
                return -1;
            else
                return 0;
        }
    }
}

void dateStore(time d){
    printf("%04d/%02d/%02d %02d:%02d ", d.year, d.month, d.day, d.hour, d.min);
}