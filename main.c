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
//    int factor = 1;
    time(&timestamp);
//    getTime(&localTime,&factor);
//
//    printf("Current time is %d hours and %d minutes\n", localTime.hour,localTime.minute);
//    sleep(5);
//    getTime(&localTime,&factor);x
//    printf("Current time is %d hours and %d minutes\n", localTime.hour,localTime.minute);
//
//    struct LocalTime newTime;
//    newTime.hour = 11;
//    newTime.minute = 27;
//    setTime(&newTime,&factor);
//
//    getTime(&localTime,&factor);
//    printf("Current time is %d hours and %d minutes\n", localTime.hour,localTime.minute);
//
//    sleep(12);
//
//    getTime(&localTime,&factor);
//    printf("Current time is %d hours and %d minutes\n", localTime.hour,localTime.minute);

//    printf("Schedule size %d \n", schedule.size);

//    struct LocalTime start1;
//    struct LocalTime start2;
//    struct LocalTime start3;
//    struct LocalTime end1;
//
//    start1.hour = 8;
//    start1.minute = 00;
//    start2.hour = 9;
//    start2.minute = 00;
//    start3.hour = 11;
//    start3.minute = 30;
//
//    end1.hour = 12;
//    end1.minute = 45;
//
//    struct Activity activity1 = createActivity("activity1", &start1, &start2);
//    struct Activity activity2 = createActivity("activity2", &start2, &start3);
//    struct Activity activity3 = createActivity("activity3", &start3, &end1);
//
//    addActivity(&schedule,&activity1);
//    addActivity(&schedule,&activity2);
//    addActivity(&schedule,&activity3);
//
//    for(int i = 0; i < schedule.usedSlots ; i++){
//        printf("Activity %s starts %d:%d ends %d:%d and state %d\n", schedule.activities[i].name,
//               schedule.activities[i].start.hour,schedule.activities[i].start.minute,
//               schedule.activities[i].end.hour,schedule.activities[i].end.minute,schedule.activities[i].done);
//    }
//    printf("Schedule size is %d\n",schedule.size);

    readSchedule(&schedule);
//    for(int i = 0; i < schedule.usedSlots ; i++){
//        printf("Activity %s starts %d:%d ends %d:%d and state %d\n", schedule.activities[i].name,
//               schedule.activities[i].start.hour,schedule.activities[i].start.minute,
//               schedule.activities[i].end.hour,schedule.activities[i].end.minute,schedule.activities[i].done);
//    }
//    printf("Schedule size is %d\n",schedule.size);

    speedFactor = 3;
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
                        printf("Actual time is %d:%d \n",localTime.hour,localTime.minute); //TODO force check
                    }else {
                        printf("Wrong input\n");
                    }
                }
            }
        } else{
//            checkActivity(&schedule.activities[actualActivityIndex],&timestamp);
//            getTime(&localTime,&speedFactor,&timestamp);
//            actualActivityIndex = getCurrentActivity(&schedule,&localTime);
//            printf("Actual time is %d:%d\n",localTime.hour,localTime.minute);
//            printf("Actual activity is %s and it's done %d\n", schedule.activities[actualActivityIndex].name,
//                    schedule.activities[actualActivityIndex].done);
            sleep(3);
        }
    }

//    actualActivityIndex = 2;
//    checkActivity(&schedule.activities[actualActivityIndex]);
    return 0;
}