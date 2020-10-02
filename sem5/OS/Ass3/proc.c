#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <regex.h> 
#include <signal.h>
#include <wait.h>

#include "jobs.h"

int check_no_correct(char *str){
    int size = strlen(str);
    for(int i=0;i < size;i++){
        if(!isdigit(str[i]))
            return 1;
    }
    return 0;
}

int fg(int argc,char **argv){
    if(argc > 2){
        fprintf(stderr,"fg : too many arguments\n");
        return -1;
    }

    if(check_no_correct(argv[1])){
        fprintf(stderr,"fg : entered argument is not a valid number\n");
        return -1;
    }

    pid_t pid = atoi(argv[1]);

    char ret = job_proc(pid);
    if(ret == 'N'){
        fprintf(stderr,"fg : given process %d does not exist\n",pid);
        return -1;
    }
    
    signal(SIGTTIN, SIG_IGN);
    signal(SIGTTOU, SIG_IGN);
    tcsetpgrp(0, pid);
    kill(pid, SIGCONT);
    int st;
    waitpid(pid, &st, WUNTRACED);
    tcsetpgrp(0, getpgrp());
    signal(SIGTTIN, SIG_DFL);
    signal(SIGTTOU, SIG_DFL);

}

int bg(int argc,char **argv){
    if(argc > 2){
        fprintf(stderr,"fg : too many arguments\n");
        return -1;
    }

    if(check_no_correct(argv[1])){
        fprintf(stderr,"fg : entered argument is not a valid number\n");
        return -1;
    }

    pid_t pid = atoi(argv[1]);

    char ret = job_proc(pid);
    if(ret == 'N'){
        fprintf(stderr,"fg : given process %d does not exist\n",pid);
        return -1;
    }
    
    kill(pid, SIGTTIN);
    kill(pid, SIGCONT);

    return 0;
}