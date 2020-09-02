/*

Code for pwd, a built in POSIX command. The code 
replicates the function of that command, but has a 
smaller list of requirements.

The command gives a list of files and directories in 
a given directory.

Example :
> ls /
  bin
  usr
  ...
>

Requirements :
- Flags to implement :
    - -a, --all
        do not ignore entries starting with . 
    - -l
        use a long listing format

- Following special characters are recognised :
    - ~  -> /home/username 
    - .  -> current directory 
    - .. -> parent directory

The code is written by : Kalp Shah

*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main(int argc, char **argv){
    // Arguments need to be split up in flags and directories
    short bool_l = 0, bool_a = 0; 
    char *dir[argc]; 
    int dirlen = 0;

    for(int i=1;i<argc;i++){
        
        if(strcmp(argv[i],"-a") == 0|| strcmp(argv[i],"--all") == 0)
            bool_a = 1;
        
        else if(strcmp(argv[i],"-l") == 0)
            bool_l = 1;

        else if(strcmp(argv[i],"-la") == 0 || strcmp(argv[i],"-al") == 0){
            bool_a = 1;
            bool_l = 1;
        }
        
        else if(argv[i][0] == '-')
            printf("ls : unrecognized option '%s'",argv[i]);
        
        else{
            dir[dirlen] = (char *)malloc((strlen(argv[i]))*sizeof(char));
            strcpy(dir[dirlen++],argv[i]);
        }
    }
    
    // If no input file provided, current directory to be listed
    if(dirlen==0){
        char *current_dir = ".";
        dir[0] = (char *)malloc((strlen(current_dir))*sizeof(char));
        strcpy(dir[0],current_dir);
        dirlen++;
    }

    for(int i=0;i<dirlen;i++)
        printf("%s\n",dir[i]);

    return 0;
}