//
// Created by Oleksandr Ivanitskyy on 2019-02-24.
//
#include "utils.h"

void reallocSchedule(struct Schedule *schedule);

void getTime(struct LocalTime *localTime,int *speedFactor, time_t *timestamp){
    time_t actual;
    time(&actual);

    time_t difference = (int) actual - *timestamp;
    difference *= *speedFactor;
    localTime->minute = (difference % 30) * 2;
    localTime->hour = difference / 30;
    localTime->hour = localTime->hour % 24; //TODO All undone after 1 day

}

void setTime(struct LocalTime *newTime, int *speedFactor, time_t *timestamp){
    time_t actual;
    time(&actual);
    int difference = newTime->hour * 30 + newTime->minute/2;
    difference /= *speedFactor;
    *timestamp = actual - difference;
}

void initializeSchedule(struct Schedule *schedule){
    schedule->size = 1;
    schedule->activities = malloc(sizeof(struct Activity));
    schedule->usedSlots = 0;
}

void addActivity(struct Schedule *schedule, char *name, struct LocalTime *start, struct LocalTime *end){
    //Our schedule is dynamically allocated, so it grows with more activities we add
    if(schedule->size == 0){
        initializeSchedule(schedule);
    } else if (schedule->size == schedule->usedSlots){
        reallocSchedule(schedule);
    }

    schedule->activities[schedule->usedSlots].name = malloc(sizeof(name));
    strcpy(schedule->activities[schedule->usedSlots].name,name);
    schedule->activities[schedule->usedSlots].start = *start;
    schedule->activities[schedule->usedSlots].end = *end;
    schedule->activities[schedule->usedSlots].done =false;
    schedule->activities[schedule->usedSlots].startCheck =false;
    schedule->activities[schedule->usedSlots].endCheck =false;
    schedule->activities[schedule->usedSlots].forceCheck =false;
    schedule->activities[schedule->usedSlots].timesPrinted =0;


    schedule->usedSlots++;
}

void reallocSchedule(struct Schedule *schedule) {
    schedule->size *=2;
    schedule->activities = realloc(schedule->activities, sizeof(struct Activity) * schedule->size);
}


int getCurrentActivity(struct Schedule *schedule,struct LocalTime *currentTime){
    int diff1,diff2;
    struct LocalTime start, end;
    for(int i = 0; i < schedule->usedSlots ; i++){
        start = schedule->activities[i].start;
        end = schedule->activities[i].end;
        diff1 = (currentTime->hour - start.hour)*60 + (currentTime->minute - start.minute);
        diff2 = (end.hour - currentTime->hour)*60 + (end.minute - currentTime->minute);

        if(diff1 >= 0 && diff2 > 0){
            if(diff2 <= 10 && !schedule->activities[i].done)
                schedule->activities[i].endCheck = true;
            return  i;
        }
    }
    return 0;
}

