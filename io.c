//
// Created by Oleksandr Ivanitskyy on 2019-02-24.
//
#include "io.h"
void readSchedule(struct Schedule *schedule){
    FILE * fp;
    char * line = NULL;
    size_t len = 0;

    char *start, *end, *name;
    fp = fopen("schedule.txt", "r");
    if (fp == NULL)
        printf("Schedule.txt missing at root folder\n");

    while ((getline(&line, &len, fp)) != -1) {
        struct Activity activity;
        start = strsep(&line, ",");
        end = strsep(&line, ",");
        name = strsep(&line, "\n");

        struct LocalTime startTime =  parseTime(start);
        struct LocalTime endTime =  parseTime(end);
        activity = createActivity(name,&startTime,&endTime);

        addActivity(schedule,&activity);
    }

    fclose(fp);
    if (line)
        free(line);

}
struct LocalTime parseTime(char * string){
    struct LocalTime localTime;
    char * eptr;

    localTime.hour = strtol(strsep(&string, ":"), eptr, 10);
    localTime.minute = strtol(strsep(&string, "\n"), eptr, 10);

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

    if(activity->done && activity->forceCheck){
        activity->forceCheck = false;
        printf("Chill, the activity %s is done \n",activity->name);
    } else{
        if(!activity->startCheck){
            activity->startCheck = true;
            printf("Is activity %s done? [yes/no] \n",activity->name);
            time(&tic);
            activity->done = readYesNo(activity);
            time(&toc);
        } else if(activity->forceCheck){
            activity->forceCheck = false;
            printf("Is activity %s done? [yes/no] \n",activity->name);
            time(&tic);
            activity->done = readYesNo(activity);
            time(&toc);
        } else if(activity->endCheck) {
            printf("Is activity %s done? [yes/no] \n",activity->name);
            time(&tic);
            activity->done = readYesNo(activity);
            time(&toc);
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
}
