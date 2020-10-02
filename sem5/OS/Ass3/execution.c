#include <stdio.h>
#include <string.h>

void command_exec(int no,char **argv,short bg_flag){
    /* if the command is quit */
    if(!strcmp(argv[0],"quit"))
        exit(0);

    /* if the command is cd */
    else if(!strcmp(argv[0],"cd")){
        if(strcmp(argv[1],"-"))
            get_prevdir();
        else
            printf("%s\n",prev_dir);
        change_dir(argv[1]);
    }
            
    /* if the command is ls */
    else if(!strcmp(argv[0],"ls"))
        ls(no, argv,home_dir);
            
    /* if the command is pinfo */
    else if(!strcmp(argv[0],"pinfo"))
        pinfo(no,argv);

    /* if the command is echo */
    else if(!strcmp(argv[0],"echo"))
        echo(no,argv);

    /* if the command is pwd */
    else if(!strcmp(argv[0],"pwd"))
        pwd(no,argv);

    /* if the command is history */
    else if(!strcmp(argv[0],"history"))
        retrieve_history(no,argv,username);

    else if(!strcmp(argv[0],"nightswatch"))
        nightswatch(no,argv);
            
    else if(!strcmp(argv[0],"setenv"))
        set_env(no,argv);

    else if(!strcmp(argv[0],"unsetenv"))
        unset_env(no,argv);

    else if(!strcmp(argv[0],"getenv"))
        get_env(no,argv);

    /* for every other command */
    else
        execute(argv,bg_flag);
}