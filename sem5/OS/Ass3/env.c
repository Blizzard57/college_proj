/*

This is the code of env functions which take care of setting and unsetting 
the environments.

Requirements :

- setenv var val
    Sets var = val,if val not provided, sets it as ""

- unsetenv var
    Destroys environment variable var, if it exists
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int set_env(int argc,char **argv){
    if(argc < 2){
        fprintf(stderr,"setenv : no environment variable entered\n");
        return 1;
    }
    else if(argc > 3){
        fprintf(stderr,"setenv : too many arguments\n");
        return 1;
    }
    else if(argc == 2){
        if(setenv(argv[1],"",1) < 0){
            fprintf(stderr,"setenv : error on setenv variable\n");
        }
    }
    else{
        setenv(argv[1],argv[2],1);
    }
    return 0;
}

int unset_env(int argc,char **argv){
    if(argc < 2){
        fprintf(stderr,"unsetenv : no environment variable entered\n");
        return 1;
    }
    else if(argc > 2){
        fprintf(stderr,"unsetenv : too many arguments\n");
        return 1;
    }
    unsetenv(argv[1]);
    return 0;
}

int get_env(int argc,char **argv){
    if(argc < 2){
        fprintf(stderr,"unsetenv : no environment variable entered\n");
        return 1;
    }
    else if(argc > 2){
        fprintf(stderr,"unsetenv : too many arguments\n");
        return 1;
    }
    printf("The environment variable %s has the value %s\n",argv[1],getenv(argv[1]));
    return 0;
}