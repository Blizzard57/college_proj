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

    -P, --physical : Default Option
        Resolves symlinks

The code is written by : Kalp Shah

*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

long size;
char *buf;
char *ptr;

void physical_pwd(){
    // Physical PWD (Resolves Symlinks)
    size = pathconf(".", _PC_PATH_MAX);

    if ((buf = (char *)malloc((size_t)size)) != NULL)
        ptr = getcwd(buf, (size_t)size);

    printf("%s",ptr);
    printf("\n");
}

void logical_pwd(){
    // Logical PWD (Respects Symlinks)
    ptr = getenv("PWD");
    printf("%s",ptr);
    printf("\n");
}

int main(int argc,char **argv){
    // Arguments Required : command -flag -> 2
    if(argc > 2){
        fprintf(stderr,"pwd : too many arguments");
        return 0;
    }

    if((argc == 2 && (strcmp(argv[1],"-L") == 0 || strcmp(argv[1],"--logical") == 0)))
        logical_pwd();

    else if((argc == 1) || (strcmp(argv[1],"-P") == 0 || strcmp(argv[1],"--physical") == 0))
        physical_pwd();

    else
        printf("pwd : unrecognised option '%s'\n",argv[1]);
    return 0;
}