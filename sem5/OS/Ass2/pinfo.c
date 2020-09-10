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
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <regex.h> 

extern int alphasort();
#define MAX_LENGTH 4096;
#define __PROGRAM_NAME__ "pinfo"

int check_Nan(char *str){
    int size = strlen(str);
    for(int i=0;i < size;i++){
        if(!isdigit(str[i]))
            return 1;
    }
    return 0;
}

int proc_reg(char *dirname,char *reg_str, char *prop){
    /* string matching to find information of process */
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

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
    printf("%s -- ",prop);
    if(!strcmp(prop,"memory")){
        for(int i=0;i<strlen(line);i++){
            if(isdigit(line[i]))
                printf("%c",line[i]);
        }
    }
    else
        printf("%c",line[7]);
    printf("\n");

    /* closing the files and refrences */
    fclose(fp);
    if (line)
        free(line);
    return 0;
}

int proc_exec(char *dirname){
    /* opens the directory to find the pid/exe file
       this file consists soft link to the original executable */
    struct stat file_stat;
    char *buf, *exec_file;
    ssize_t nbytes, bufsiz;
    
    exec_file = (char *) malloc((strlen("/proc/") + strlen(dirname) + strlen("/exe") + 2)*sizeof(char));
    strcpy(exec_file,"/proc/");
    strcat(exec_file,dirname);
    strcat(exec_file,"/exe");

    /* stat gives detail on size of file */
    if (lstat(exec_file, &file_stat) == -1) {
               fprintf(stderr,"%s : cannot stat file %s",__PROGRAM_NAME__,exec_file);
               exit(EXIT_FAILURE);
    }

    if(!file_stat.st_size){
        bufsiz = MAX_LENGTH;
    }
    else{
        bufsiz = file_stat.st_size + 2;
    }

    buf = (char *)malloc(bufsiz * sizeof(char));
    nbytes = readlink(exec_file, buf, bufsiz);
    if(nbytes < 0){
        fprintf(stderr,"%s : readlink error",__PROGRAM_NAME__);
        exit(EXIT_FAILURE);
    }
    printf("Executable Path -- %s\n",buf);
    return 0;
}

int proc_info(pid_t process){
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
        if(!check_Nan(namelist[i] -> d_name)){
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
        return 1;
    }

    /* printing the pid */
    printf("pid -- %d\n",process);
    /* printing the status */
    char reg_stat[] = "State";
    char prop_stat[] = "Process Status";
    proc_reg(dirname,reg_stat,prop_stat);

    /* printing memory taken by process */
    char reg_mem[] = "VmSize";
    char prop_mem[] = "memory";
    proc_reg(dirname,reg_mem,prop_mem);
    /* printing path of the executable */
    proc_exec(dirname);    
    return 0;
}

int pinfo(int argc, char **argv){
    pid_t process;
    
    if(argc > 2){
        fprintf(stderr,"%s : too many arguments\n",__PROGRAM_NAME__);
        return 1;
    }
    else if(argc == 1){
        process = getppid();
    }
    else{
        if(check_Nan(argv[1])){
            fprintf(stderr,"pinfo : argument %s is not a number\n",argv[1]);
            return 1;
        }
        process = atoi(argv[1]);
    }
    
    if(proc_info(process))
        fprintf(stderr,"%s : given process does not exist\n",__PROGRAM_NAME__);
    return 0;
}

int main(int argc,char **argv){
    int ret_val = pinfo(argc,argv);
    return ret_val;
}