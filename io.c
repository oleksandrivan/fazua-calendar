//
// Created by Oleksandr Ivanitskyy on 2019-02-24.
//
#include "io.h"
void readSchedule(struct Schedule *schedule){
    FILE * fp;

    char line[256];
    char name[20];
    char start[20];
    char end[20];

    fp = fopen("schedule.txt", "r");
    if (fp == NULL)
        printf("Schedule.txt missing at root folder\n");

    while (fgets(line, sizeof(line), fp)) {
        if (3 == sscanf(line, "%s , %s , %s \n", start, end, name)) {
            struct LocalTime startTime = parseTime(start);
            struct LocalTime endTime = parseTime(end);
            addActivity(schedule, name, &startTime, &endTime);
        } else{
            printf("Bad format schedule.txt\n");
        }

    }


    fclose(fp);

}
struct LocalTime parseTime(char * string){
    struct LocalTime localTime;

    sscanf(string,"%d:%d",&localTime.hour,&localTime.minute);

    return localTime;
}

bool inputAvailable(){
    struct timeval tv;
    fd_set fds;
    tv.tv_sec = 0;
    tv.tv_usec = 0;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds);
    select(STDIN_FILENO+1, &fds, NULL, NULL, &tv);
    return (FD_ISSET(0, &fds));
}

void checkActivity(struct Activity * activity, time_t *timestamp){
    time_t tic,toc;
    tic = 0;
    toc = 0;

    if(activity->done && activity->forceCheck){
        activity->forceCheck = false;
        printf("Chill, the activity '%s' is done \n",activity->name);
    } else{
        if(!activity->startCheck){
            activity->startCheck = true;
            printf("Is activity '%s' done? [yes/no] \n",activity->name);
            time(&tic);
            activity->done = readYesNo(activity);
            time(&toc);
            activity->timesPrinted++;
        } else if(activity->forceCheck){
            activity->forceCheck = false;
            printf("Is activity '%s' done? [yes/no] \n",activity->name);
            time(&tic);
            activity->done = readYesNo(activity);
            time(&toc);
        } else if(activity->endCheck && !activity->done && activity->timesPrinted < 2) {
            printf("Is activity '%s' done? [yes/no] \n",activity->name);
            time(&tic);
            activity->done = readYesNo(activity);
            time(&toc);
            activity->timesPrinted++;
        }
    }
    *timestamp += toc - tic;
}

bool readYesNo(struct Activity *activity){
    char line[256];
    char answer[5];
    if (fgets(line, sizeof(line), stdin)) {
        if (1 == sscanf(line, "%s", answer)) {
           if(strcmp(answer,"yes") == 0 ){
                printf("The answer is yes\n");
               return true;
           } else if(strcmp(answer,"no") == 0){
               printf("The answer is no\n");
               return false;
           } else{
               printf("Wrong answer\n");
               return false;
           }
        }
    }
    return false;
}
