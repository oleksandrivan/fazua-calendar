//
// Created by Oleksandr Ivanitskyy on 2019-02-24.
//
#include "main.h"

struct LocalTime localTime;
struct Schedule schedule;
int actualActivityIndex;
int speedFactor;
time_t timestamp;
int main(){
    time(&timestamp);

    readSchedule(&schedule);
//    for(int i = 0; i < schedule.usedSlots ; i++){
//        printf("Activity %s starts %d:%d ends %d:%d and state %d\n", schedule.activities[i].name,
//               schedule.activities[i].start.hour,schedule.activities[i].start.minute,
//               schedule.activities[i].end.hour,schedule.activities[i].end.minute,schedule.activities[i].done);
//    }
//    printf("Schedule size is %d\n",schedule.size);
//
    speedFactor = 1;
    char line[256];
    char answer[5];
    int hour,min;

    while(true){
        if(inputAvailable()){
            timestamp -=3;
            if (fgets(line, sizeof(line), stdin)) {
                if (2 == sscanf(line, "%d:%d", &hour,&min)){
                    printf("Time introduced is %d:%d \n",hour,min);
                    struct LocalTime newTime;
                    newTime.hour = hour;
                    newTime.minute = min;
                    setTime(&newTime, &speedFactor,&timestamp);
                } else if (1 == sscanf(line, "%s", answer)) {
                    if(strcmp(answer,"now") == 0){
                        getTime(&localTime,&speedFactor,&timestamp);
                        printf("Actual time is %d:%d \n",localTime.hour,localTime.minute);
                        actualActivityIndex = getCurrentActivity(&schedule,&localTime);
                        schedule.activities[actualActivityIndex].forceCheck = true;
                    }else {
                        printf("Wrong input\n");
                    }
                }
            }
            sleep(3);
        } else{
            checkActivity(&schedule.activities[actualActivityIndex],&timestamp);
            getTime(&localTime,&speedFactor,&timestamp);
            actualActivityIndex = getCurrentActivity(&schedule,&localTime);

            sleep(1);
        }
    }

    return 0;
}