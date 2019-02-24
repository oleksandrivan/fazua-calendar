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
};

struct Schedule{
    int size;
    int usedSlots;
    struct Activity *activities;
};

void startTime();

void getTime(struct LocalTime *localTime,int *speedFactor);

void setTime(struct LocalTime *newTime, int *speedFactor);

void addActivity(struct Schedule *schedule, struct Activity *activity);

struct Activity createActivity(const char * name, struct LocalTime *start, struct LocalTime *end);

#endif //FAZUA_CALENDAR_UTILS_H
