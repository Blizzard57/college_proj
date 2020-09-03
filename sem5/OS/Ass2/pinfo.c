/*

Code for pinfo, a user defined command. the function 
of the command is to find information of any given 
process.

The information provided :
pid : pid of the process
Process Status {R/S/S+/Z} : if the process os running or sleeping or other states
Memory : virtual memory allocated to it
Executable Path : path of the executable

The code is written by : Kalp Shah

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/wait.h>

int check_number(char *str){
    int size = strlen(str);
    for(int i=0;i < size;i++){
        if(!isdigit(str[i]))
            return 1;
    }
    return 0;
}

int main(int argc, char **argv){
    pid_t process;
    if(argc > 2){
        fprintf(stderr,"pinfo : too many arguments\n");
        return 1;
    }
    else if(argc == 1){
        /* find pid of the shell */
    }
    else{
        if(check_number(argv[1])){
            printf("pinfo : argument %s is not a number\n",argv[1]);
            return 1;
        }
        process = atoi(argv[1]);
    }

    int status;

    pid_t return_pid = waitpid(process,&status,WNOHANG);
    printf("%d\n",status);

    return 0;
}