/*

This is the code of a history commad which 
can handle basic functionality.

The command stores all the commands entered 
and retreives when required.

*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/stat.h>

#define __PROGRAM_NAME__ "history"
#define __SHELL_NAME__ "hash"

int check_Num(char *str){
    int size = strlen(str);
    for(int i=0;i < size;i++){
        if(!isdigit(str[i]))
            return 1;
    }
    return 0;
}

int add_history(char *command, char *username){
    char *filepath = (char *)malloc((strlen("/home/") + strlen(username) + strlen("/.") + strlen(__SHELL_NAME__) + strlen("_history") + 1)*sizeof(char));
    strcpy(filepath,"/home/");
    strcat(filepath,username);
    strcat(filepath,"/.");
    strcat(filepath,__SHELL_NAME__);
    strcat(filepath,"_history");

    FILE *histfile;
    histfile = fopen(filepath, "a");
    if(histfile == NULL){
        if(mkdir(filepath,0777)){
            fprintf(stderr,"%s : unable to create directory %s",__PROGRAM_NAME__,filepath);
            return 1;
        }
        histfile = fopen(filepath, "a");
    }
    fputs(command,histfile);
    fputs("\n",histfile);
    fclose(histfile);

    return 0;
}

int retrieve_history(int argc,char **argv,char *username){
    int no_of_commands;
    
    if(argc == 1){
        no_of_commands = 20;
    }
    else if(argc == 2){
        if(check_Num(argv[1])){
            fprintf(stderr,"%s : argument %s is not a number\n",__PROGRAM_NAME__,argv[1]);
            return 1;
        }
        no_of_commands = atoi(argv[1]);
    }
    else
        fprintf(stderr,"%s : too many arguments\n",__PROGRAM_NAME__);
    
    /* opening the history file */
    char *filepath = (char *)malloc((strlen("/home/") + strlen(username) + strlen("/.") + strlen(__SHELL_NAME__) + strlen("_history") + 1)*sizeof(char));
    strcpy(filepath,"/home/");
    strcat(filepath,username);
    strcat(filepath,"/.");
    strcat(filepath,__SHELL_NAME__);
    strcat(filepath,"_history");

    FILE *histfile;
    histfile = fopen(filepath,"r");
    
    char chr;
    int no_of_lines = 0;
    chr = getc(histfile);
    while (chr != EOF){
        if(chr == '\n')
            no_of_lines++;
        chr = getc(histfile);
    }
    fclose(histfile);

    if(no_of_lines <= no_of_commands)
        no_of_commands = 0;
    else
        no_of_commands = no_of_lines - no_of_commands;

    histfile = fopen(filepath,"r");
    
    chr = getc(histfile);
    while (chr != EOF){
        if(chr == '\n'){
            no_of_commands--;
        }
        chr = getc(histfile);
        if(no_of_commands <= 0 && chr != EOF)
            printf("%c",chr);
    }
    fclose(histfile);
}