#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <time.h>
#include <regex.h>
#include <sys/stat.h>
#include <dirent.h>

#include "keypress.h"

#define __PROGRAM_NAME__ "nightswatch"
#define HOST_MAX 64

extern int alphasort();

int  params(char *line, char **argv){
    int no_of_params = 0;
    while (*line != '\0') {       /* if not the end of line */ 
        while (*line == ' ' || *line == '\t' || *line == '\n')
            *line++ = '\0';     /* replace white spaces with 0 */
        
        /* save the argument position */
        no_of_params++;
        *argv++ = line;

        while (*line != '\0' && *line != ' ' &&  *line != '\t' && *line != '\n') 
            line++;             /* skip the argument until ...    */
    }
    *argv = '\0';                 /* mark the end of argument list  */
    return no_of_params;
}

int check_no(char *str){
    int size = strlen(str);
    for(int i=0;i < size;i++){
        if(!isdigit(str[i]))
            return 1;
    }
    return 0;
}

int get_cpu_info(int numCPU){
    FILE *proc = fopen("/proc/interrupts","r");
    char * line = NULL;
    ssize_t read;
    size_t len = 0;
    short flag = 0;

    if(proc == NULL){
        fprintf(stderr,"%s : could not read file /proc/interrupts",__PROGRAM_NAME__);
        return 1;
    }

    regex_t reg;
    int ret_val = regcomp(&reg,"i8042",0);
    if(ret_val)
        fprintf(stderr,"%s : regex compilation\n",__PROGRAM_NAME__);

    /* comparing the strings line by line */
    while ((read = getline(&line, &len, proc)) != -1) {
        if(!regexec(&reg,line,0,NULL,0)){
            flag = 1;
            break;
        }
    }
    if(flag){
        char *argv[15];
        int no = params(line,argv), j = 0;
        for(int i=0;i<no;i++){
            //printf("%s\n",argv[i]);
            if(!check_no(argv[i]) && j < numCPU){
                printf("%s\t",argv[i]);
                j++;
            }
        }
        printf("\n");
    }
    else{
        fprintf(stderr,"%s : the entry does not exist\n",__PROGRAM_NAME__);
        return 1;
    }
    fclose(proc);
    return 0;
}

int interrupt(int interval){
    
    char *osname = (char *)malloc(HOST_MAX*sizeof(char));
    gethostname(osname,HOST_MAX);
    if(!strcmp(osname,"sphinx"))
        interval *= 1000000;
    else
        interval *= 1000;
    
    int numCPU = sysconf(_SC_NPROCESSORS_ONLN);
    for(int i=0;i<numCPU;i++)
        printf("CPU%d\t",i);
    printf("\n");

    clock_t start = clock();

    while (1) {
        while (clock() < start + interval){
           if(keyboardWasPressed()){
               char c = getchar();
               if(c=='q'){
                   printf("\n");
                   return 0;
               }
           }
        }
        if(get_cpu_info(numCPU))
            return 1;
        start = clock();
    }
}

int find_newborn(){
    struct dirent **namelist;
    int no_of_files;

    /* finds all the files inside the given directory */
    no_of_files = scandir("/proc",&namelist,0,alphasort);
    if(no_of_files < 0){
        fprintf(stderr,"%s",__PROGRAM_NAME__);
        return 1;
    }

    for(int i=0;i<no_of_files;i++){
        if(!check_no(namelist[i] -> d_name)){
            char *dir = (char *)malloc((strlen("/proc/") + strlen(namelist[i] -> d_name) + strlen("/stat") + 10)*sizeof(char));
            strcpy(dir,"/proc/");
            strcat(dir,namelist[i] -> d_name);
            strcat(dir,"/stat");

            char * line = NULL;
            ssize_t read;
            size_t len = 0;

            FILE *proc = fopen(dir,"r");
            read = getline(&line, &len, proc);
            char *argv[30];
            params(line,argv);
            printf("The Process Time : %d\n",atoi(argv[21]));
            fclose(proc);
            free(dir);
        }
    }
    return 0;
}

int newborn(int interval){
    char *osname = (char *)malloc(HOST_MAX*sizeof(char));
    gethostname(osname,HOST_MAX);
    if(!strcmp(osname,"sphinx"))
        interval *= 1000000;
    else
        interval *= 1000;

    clock_t start = clock();

    while (1) {
        while (clock() < start + interval){
           if(keyboardWasPressed()){
               char c = getchar();
               if(c=='q'){
                   printf("\n");
                   return 0;
               }
           }
        }
        if(find_newborn())
            return 1;
        start = clock();
    }
}

int nightswatch(int argc,char **argv){
    if(argc > 4){
        fprintf(stderr,"%s : too many arguments",__PROGRAM_NAME__);
        return 1;
    }
    else if(argc == 1){
        fprintf(stderr,"%s : no argument provided",__PROGRAM_NAME__);
        return 1;
    }
    /* default is 5s */
    int interval = 5;

    for(int i=0;i<argc;i++){
        /* find the argument where -n is mentioned */
        if(!strcmp(argv[i],"-n")){
            /* check if time interval is given after that */
            if(i+1 >= argc){
                fprintf(stderr,"%s : time not specified\n",__PROGRAM_NAME__);
                return 1;
            }
            else{
                /* check if the latter argument is a number */
                if(!check_no(argv[i+1])){
                    /* store it in a varible */
                    interval = atoi(argv[i+1]);
                    break;
                }
                else{
                    fprintf(stderr,"%s : time interval %s must be a number\n",__PROGRAM_NAME__,argv[i+1]);
                    return 1;
                }
            }
        }
    }

    if(!strcmp(argv[argc-1],"interrupt"))
        interrupt(interval);
    else if(!strcmp(argv[argc-1],"newborn"))
        newborn(interval);
    else
        fprintf(stderr,"%s : %s option not recognised\n",__PROGRAM_NAME__,argv[argc-1]);

    return 0;
}

//int main(int argc,char **argv){
//    return nightswatch(argc,argv);
//}