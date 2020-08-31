/*

Code for pwd, a built in POSIX command. The code 
replicates the function of that command, but has a 
smaller list of requirements.

The code gives the working directory the user is 
currently in.

Example :
> pwd
  /Absolute/path/of/the/current/directory
>

Requirements :
- Two flags to implement :
    -L, --logical
        environemnt PWD, symlinks respected

    -P, --physical
        Avoid symlinks

The code is written by : Kalp Shah

*/

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>

long size;
char *buf;
char *ptr;

void logical_pwd(){
    // Logical PWD (Respects Symlinks)
    size = pathconf(".", _PC_PATH_MAX);

    if ((buf = (char *)malloc((size_t)size)) != NULL)
        ptr = getcwd(buf, (size_t)size);

    printf("%s",ptr);
    printf("\n");
}

void physical_pwd(){
    // Physical PWD (Avoids Symlinks)
}

int main(int argc,char **argv){
    // Arguments Required : command -flag -> 2
    if(argc > 2){
        perror("Error : Excess Arguments");
        return 0;
    }

    if((argc == 2 && (strcmp(argv[1],"-L") || strcmp(argv[1],"--logical")))){
        logical_pwd();
    }

    else if((argc == 1) || (strcmp(argv[1],"-P") || strcmp(argv[1],"--physical"))){
        physical_pwd();
    }

    return 0;
}