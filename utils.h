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

/**
 * Structure to simulate time in our calendar
 */
struct LocalTime{
    int8_t hour;
    int8_t minute;
};

/**
 * Structure to store activity
 */
struct Activity{
    struct LocalTime start;
    struct LocalTime end;
    bool done;
    char *name;
    bool startCheck,endCheck,forceCheck;
    int8_t timesPrinted;
};

 /**
  * Structure to store all daily activities
  */
struct Schedule{
    int size;
    int usedSlots;
    struct Activity *activities;
};
/**
 * Get simulated time
 * @param localTime
 * @param speedFactor
 * @param timestamp
 */
void getTime(struct LocalTime *localTime,int *speedFactor, time_t *timestamp);

/**
 * Sets time in out simulated enviroment
 * @param newTime
 * @param speedFactor
 * @param timestamp
 */
void setTime(struct LocalTime *newTime, int *speedFactor, time_t *timestamp);

/**
 * Add activity to our schedule
 * @param schedule
 * @param name
 * @param start
 * @param end
 */
void addActivity(struct Schedule *schedule, char *name, struct LocalTime *start, struct LocalTime *end);

/**
 * Get activity at specific time
 * @param schedule
 * @param currentTime
 * @return
 */
int getCurrentActivity(struct Schedule *schedule,struct LocalTime *currentTime);

/**
 * Restarts day to reseting all activities to undone
 * @param localTime
 * @param schedule
 */
void restartDay(struct LocalTime *localTime, struct Schedule *schedule);

#endif //FAZUA_CALENDAR_UTILS_H
