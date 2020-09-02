/*

Code for ls, a built in POSIX command. The code 
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

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include<dirent.h>


/*

TODO : Color coding of ls output (Optional)

#define RESET   "\033[0m"
#define BLACK   "\033[30m"      // Black 
#define RED     "\033[31m"      // Red 
#define GREEN   "\033[32m"      // Green 
#define YELLOW  "\033[33m"      // Yellow 
#define BLUE    "\033[34m"      // Blue 
#define MAGENTA "\033[35m"      // Magenta 
#define CYAN    "\033[36m"      // Cyan 
#define WHITE   "\033[37m"      // White 
#define BOLDBLACK   "\033[1m\033[30m"      // Bold Black 
#define BOLDRED     "\033[1m\033[31m"      // Bold Red 
#define BOLDGREEN   "\033[1m\033[32m"      // Bold Green 
#define BOLDYELLOW  "\033[1m\033[33m"      // Bold Yellow 
#define BOLDBLUE    "\033[1m\033[34m"      // Bold Blue 
#define BOLDMAGENTA "\033[1m\033[35m"      // Bold Magenta 
#define BOLDCYAN    "\033[1m\033[36m"      // Bold Cyan
#define BOLDWHITE   "\033[1m\033[37m"      // Bold White 

*/

#define FILE_LENGTH 2000

int find_perm(char *ans, char *filename){

    struct stat file_stat;
    if (stat(filename, &file_stat) < 0){
        perror("Could not stat file");
        return 1;
    }
    /* Checking if the given file is a directory */
    if(S_ISDIR(file_stat.st_mode))
        ans[0] = 'd';

    if(file_stat.st_mode & S_IRUSR)
        ans[1] = 'r';
    if(file_stat.st_mode & S_IWUSR)
        ans[2] = 'w';
    if(file_stat.st_mode & S_IXUSR)
        ans[3] = 'x';
    
    if(file_stat.st_mode & S_IRGRP)
        ans[4] = 'r';
    if(file_stat.st_mode & S_IWGRP)
        ans[5] = 'w';
    if(file_stat.st_mode & S_IXGRP)
        ans[6] = 'x';

    if(file_stat.st_mode & S_IROTH)
        ans[7] = 'r';
    if(file_stat.st_mode & S_IWOTH)
        ans[8] = 'w';
    if(file_stat.st_mode & S_IXOTH)
        ans[9] = 'x';

    return 0;
}

int list(char *dir, short bool_a,short bool_l){
    struct dirent **namelist;
    int no_of_files;

    no_of_files = scandir(dir,&namelist,0,alphasort);
    if(no_of_files < 0){
        perror("scandir");
        return 0;
    }
    if(bool_l){
        for(int i=0;i<no_of_files;i++){
            if(bool_a == 0 && namelist[i] -> d_name[0] == '.')
                continue;
            
            /* filename containing absolute path,
               and dynamically allocating size for it */
            char *filename = (char *)malloc((strlen(dir) + strlen(namelist[i] -> d_name) + 2)*sizeof(char));
            strcpy(filename,dir);
            strcat(filename,"/");
            strcat(filename,namelist[i] -> d_name);

            char perm[11] = {'-','-','-','-','-','-','-','-','-','-','\0'}; 
            find_perm(perm, filename);
            printf("%s %s\n",perm,namelist[i] -> d_name);
            free(namelist[i]);
        }
        free(namelist);
        return 0;
    }
    for(int i=0;i<no_of_files;i++){
        if(bool_a == 0 && namelist[i] -> d_name[0] == '.')
            continue;
        printf("%s  ",namelist[i] -> d_name);
        free(namelist[i]);
    }
    free(namelist);
    printf("\n");
    return 0;
}

int main(int argc, char **argv){
    /* arguments need to be split up in flags and directories */
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
    
    /* if no input file provided, 
       current directory to be listed */

    if(dirlen==0){
        char *current_dir = ".";
        dir[0] = (char *)malloc((strlen(current_dir))*sizeof(char));
        strcpy(dir[0],current_dir);
        dirlen++;
    }

    /* 
    if multiple directories are provided,
    list the name of the directory.
    Eg :
    > ls ~ /bin
      /home/username:
      lists
      
      /bin:
      lists
    */

    if(dirlen == 1)
        list(dir[0],bool_a,bool_l);
    
    else{
        for(int i=0;i<dirlen;i++){
            printf("%s:\n",dir[i]);
            list(dir[i],bool_a,bool_l);
            if(i != dirlen - 1)
                printf("\n");
        }
    }

    return 0;
}