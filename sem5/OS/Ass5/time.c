/*
time function call which tests waitx for any command to be executed
*/

#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc,char **argv){
    if(argc < 2){
        printf(1,"time : no arguments provided\n");
        exit();
    }

    int proc = fork();
    if(proc==0)
        exec(argv[1],argv + 1);
    else{
        int *wtime = (int *)malloc(sizeof(int));
        int *rtime = (int *)malloc(sizeof(int));

        waitx(wtime,rtime);
        printf(1,"Wait time (wtime) : %d ticks \nExecution time (rtime) : %d ticks\n",*wtime,*rtime);
    }

    #ifdef ORIGINAL
    printf(1,"Scheduler : DEFAULT\n");
    #endif
    
    #ifdef PBS
    printf(1,"Scheduler : PBS\n");
    #endif

    #ifdef FCFS
    printf(1,"Scheduler : FCFS\n");
    #endif

    exit();
}