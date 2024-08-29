#ifndef ASD_TIME_H
#define ASD_TIME_H

typedef struct{
    int year;
    int month;
    int day;
    int hour;
    int min;
} time;

time setTime(int year, int month, int day, int hour, int min);
int DateCompare(time t1, time t2); //return 1 if t1 happen before t2
void dateStore(time d);

#endif //ASD_TIME_H
