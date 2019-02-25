//
// Created by Oleksandr Ivanitskyy on 2019-02-24.
//

#ifndef FAZUA_CALENDAR_UTILS_H
#define FAZUA_CALENDAR_UTILS_H

#include <time.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <memory.h>

struct LocalTime{
    int hour;
    int minute;
};
/**
 * Structure to simulate time in our calendar
 */

struct Activity{
    struct LocalTime start;
    struct LocalTime end;
    bool done;
    char *name;
    bool startCheck,endCheck,forceCheck;
};

struct Schedule{
    int size;
    int usedSlots;
    struct Activity *activities;
};

void getTime(struct LocalTime *localTime,int *speedFactor, time_t *timestamp);

void setTime(struct LocalTime *newTime, int *speedFactor, time_t *timestamp);

void addActivity(struct Schedule *schedule, struct Activity *activity);

struct Activity createActivity(const char * name, struct LocalTime *start, struct LocalTime *end);

int getCurrentActivity(struct Schedule *schedule,struct LocalTime *currentTime);

#endif //FAZUA_CALENDAR_UTILS_H
