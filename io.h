//
// Created by Oleksandr Ivanitskyy on 2019-02-24.
//

#ifndef FAZUA_CALENDAR_IO_H
#define FAZUA_CALENDAR_IO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
void readSchedule(struct Schedule *schedule);
struct LocalTime parseTime(char * string);
bool inputAvailable();
void checkActivity(struct Activity * activity, time_t *timestamp);
bool readYesNo(struct Activity *activity);
void readInput();
#endif //FAZUA_CALENDAR_IO_H
