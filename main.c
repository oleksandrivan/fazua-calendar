//
// Created by Oleksandr Ivanitskyy on 2019-02-24.
//
#include "main.h"

struct LocalTime localTime;
struct Schedule schedule;
int actualActivityIndex;
int speedFactor;
time_t timestamp;
int main(int argc, char *argv[] ){
    speedFactor = 1;
    char line[256];
    char answer[5];
    int hour,min;
    char *endptr;

    if(argc == 2){
        speedFactor = (int) strtol(argv[1],&endptr,10);
        printf("The speed factor is %d\n",speedFactor);
    }

    signal(SIGINT,signalHandler);
    readSchedule(&schedule);


    time(&timestamp);
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
                        restartDay(&localTime,&schedule);
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

void signalHandler(int sig){
    printf("Calendar app finished\n");
        for(int i = 0; i < schedule.usedSlots ; i++){
        free(schedule.activities[i].name);
    }
    free(schedule.activities);
    exit(EXIT_SUCCESS);
}