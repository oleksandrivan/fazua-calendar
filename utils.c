//
// Created by Oleksandr Ivanitskyy on 2019-02-24.
//
#include "utils.h"

time_t timestamp;

void reallocSchedule(struct Schedule *schedule);

void startTime(){
    time(&timestamp);
}

void getTime(struct LocalTime *localTime,int *speedFactor){
    time_t actual;
    time(&actual);

    time_t difference = (int) actual - timestamp;
    difference *= *speedFactor;
    printf("The difference is %d\n",difference);
    localTime->minute = (difference % 30) * 2;
    localTime->hour = difference / 30;
    localTime->hour = localTime->hour % 24; //Hours from 0 to 23

}

void setTime(struct LocalTime *newTime, int *speedFactor){
    time_t actual;
    time(&actual);
    int difference = newTime->hour * 30 + newTime->minute/2;
    difference /= *speedFactor;
    timestamp = actual - difference;
}

void initializeSchedule(struct Schedule *schedule){
    schedule->size = 1;
    schedule->activities = malloc(sizeof(struct Activity));
    schedule->usedSlots = 0;
}

void addActivity(struct Schedule *schedule, struct Activity *activity){
    //Our schedule is dynamically allocated, so it grows with more activities we add
    if(schedule->size == 0){
        initializeSchedule(schedule);
    } else if (schedule->size == schedule->usedSlots){
        reallocSchedule(schedule);
    }

    schedule->activities[schedule->usedSlots++] = *activity;
}

void reallocSchedule(struct Schedule *schedule) {
    schedule->size *=2;
    schedule->activities = realloc(schedule->activities, sizeof(struct Activity) * schedule->size);
}

struct Activity createActivity(const char * name, struct LocalTime *start, struct LocalTime *end){
    struct Activity newActivity;

    //Allocate and copy name string
    char *activityName = malloc(sizeof(*name));
    strcpy(activityName,name);

    newActivity.name = activityName;
    newActivity.start = *start;
    newActivity.end = *end;
    newActivity.done = false;

    return newActivity;
}