#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <regex.h> 

extern int alphasort();
#define MAX_LENGTH 4096;
#define __PROGRAM_NAME__ "jobs"

int find_if_no(char *str){
    int size = strlen(str);
    for(int i=0;i < size;i++){
        if(!isdigit(str[i]))
            return 1;
    }
    return 0;
}

char get_stat(char *dirname,char *reg_str, char *prop){
    /* string matching to find information of process */
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    char ans;

    char *filename = (char *)malloc((strlen("/proc/") + strlen(dirname) + strlen("/status") + 2)*sizeof(char)) ;
    strcpy(filename,"/proc/");
    strcat(filename,dirname);
    strcat(filename,"/status");

    /* regex for pattern matching */
    regex_t reg;
    int ret_val = regcomp(&reg,reg_str,0);
    if(ret_val)
        fprintf(stderr,"%s : regex compilation\n",__PROGRAM_NAME__);

    fp = fopen(filename, "r");
    if (fp == NULL){
        fprintf(stderr,"%s : cannot access %s",__PROGRAM_NAME__,filename);
        exit(EXIT_FAILURE);
    }

    /* comparing the strings line by line */
    while ((read = getline(&line, &len, fp)) != -1) {
        if(!regexec(&reg,line,0,NULL,0))
            break;
    }

    /* printing the value */
    if(!strcmp(prop,"memory")){
        for(int i=0;i<strlen(line);i++){
            if(isdigit(line[i]))
                printf("%c",line[i]);
        }
    }
    else
        ans = line[7];

    /* closing the files and refrences */
    fclose(fp);
    if (line)
        free(line);
    return ans;
}

char job_proc(pid_t process){
    /* finds a folder with same name as pid (same is done by command ps) */
    struct dirent **namelist;
    int no_of_files;

    /* finds all the files inside the given directory */
    no_of_files = scandir("/proc",&namelist,0,alphasort);
    if(no_of_files < 0){
        fprintf(stderr,"%s : pinfo",__PROGRAM_NAME__);
        return 1;
    }

    /* checks if a directory with the same name as pid exists */
    short flag = 0;
    char *dirname;
    for(int i=0;i<no_of_files;i++){
        if(!find_if_no(namelist[i] -> d_name)){
            if(atoi(namelist[i] -> d_name) == process){
                flag = 1;
                dirname = (char *)malloc((strlen(namelist[i] -> d_name) + 2) * sizeof(char));
                strcpy(dirname,namelist[i] -> d_name);
                break;
            }
        }
        free(namelist[i]);
    }
    free(namelist);

    /* exit status for file not existing */
    if(!flag){
        return 'N';
    }

    char reg_stat[] = "State";
    char prop_stat[] = "Process Status";
    char val = get_stat(dirname,reg_stat,prop_stat);

    return val;
}