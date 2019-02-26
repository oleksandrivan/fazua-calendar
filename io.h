//
// Created by Oleksandr Ivanitskyy on 2019-02-24.
//

#ifndef FAZUA_CALENDAR_IO_H
#define FAZUA_CALENDAR_IO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

/**
 * Reads activities from schedule.txt and adds them to schedule struct
 * @param schedule
 */
void readSchedule(struct Schedule *schedule);

/**
 * Parses string to LocalTime struct
 * @param string
 * @return
 */
struct LocalTime parseTime(char * string);

/**
 * Checks if input is available
 * @return
 */
bool inputAvailable();

/**
 * Prints info about activity and asks if is done
 * @param activity
 * @param timestamp
 */
void checkActivity(struct Activity * activity, time_t *timestamp);

/**
 * Interprets if input is yes/no
 * @param activity
 * @return
 */
bool readYesNo(struct Activity *activity);


#endif //FAZUA_CALENDAR_IO_H
