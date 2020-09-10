/*

This is the code of a shell program (like bash) which 
can handle basic functionality.

Requirements :

- displays <username@systemname:curr_dir>
- directory from where the shell is invoked (cwd) is the home directory
- implement cd
    - .. , . and ~ flags implemented
- process can execute in background (&) and foreground
- appropriate message displayed after background process exits (on stderr)

*/

#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <signal.h>
#include <sys/utsname.h>
#include <regex.h>
#include <sys/wait.h>

#define __PROGRAM_NAME__ "hash"
#define BUF_MAX 4096
#define HOST_MAX 64

char *osname;
char *username;
char *home_dir;

void  parse(char *line, char **argv){
    /* External Functions : Taken From http://www.csl.mtu.edu/cs4411.ck/www/NOTES/process/fork/exec.html */
    while (*line != '\0') {       /* if not the end of line ....... */ 
        while (*line == ' ' || *line == '\t' || *line == '\n')
            *line++ = '\0';     /* replace white spaces with 0    */
        
        *argv++ = line;          /* save the argument position     */
        while (*line != '\0' && *line != ' ' &&  *line != '\t' && *line != '\n') 
            line++;             /* skip the argument until ...    */
     }
     *argv = '\0';                 /* mark the end of argument list  */
}

void  execute(char **argv){
     pid_t  pid;
     int    status;

    /* fork a child process */
     if ((pid = fork()) < 0) {
          fprintf(stderr,"%s: forking child process failed\n",__PROGRAM_NAME__);
          exit(1);
     }

     /* Child does the process */
     else if (pid == 0) {
          if (execvp(*argv, argv) < 0) {     /* execute the command  */
               fprintf(stderr,"%s: unknown command %s\n",__PROGRAM_NAME__,argv[0]);
               exit(1);
          }
     }
     /* Parent waits */
     else {
         /* wait for completion */
          while (wait(&status) != pid)
               ;
        int exit_status = WEXITSTATUS(status);         
        //printf("Exit status of the child was %d\n",exit_status); 
     }
}

char* pwd_cur(){
    /* gets the current directory and does tilde contration */
    long size;
    char *buf;
    char *cur_dir, *result;

    size = pathconf(".", _PC_PATH_MAX);

    if ((buf = (char *)malloc((size_t)size)) != NULL)
        cur_dir = getcwd(buf, (size_t)size);

    /* pattern matching to find if cur_dir is a subdirectory of home_dir */
    regex_t reg;
    int ret_val = regcomp(&reg,home_dir,0);
    if(ret_val)
        fprintf(stderr,"%s : regex compilation\n",__PROGRAM_NAME__);

    /* comparing and replacing home_dir -> ~ */
    if(!regexec(&reg,cur_dir,0,NULL,0)){
        int len_home = strlen(home_dir);
        int len_cur = strlen(cur_dir);

        result = (char *)malloc((len_cur - len_home + 3)*sizeof(char));
        strcpy(result,"~");
        for(int i=1;i < len_cur - len_home + 1;i++){
            result[i] = cur_dir[len_home + i - 1];
        }
        return result;
    }
    return cur_dir;
}

void pwd_home(){
    long size;
    char *buf;

    size = pathconf(".", _PC_PATH_MAX);

    if ((buf = (char *)malloc((size_t)size)) != NULL)
        home_dir = getcwd(buf, (size_t)size);
}

int change_dir(char *dir){
    /* implements the functionality of the cd command */
    if(dir == NULL || !strcmp(dir,"~"))
        chdir(home_dir);
    chdir(dir);
    return 0;
}

void replace_home(char **argv){
    /* Replace ~ -> Home Dir */
    int len = strlen(*argv);
    for(int i=0;i<len;i++){
        //if(strcmp(argv[i],"~") == 0){
        //    *argv + i = home_dir;
        //}
        printf("Argv Values : %s\n",argv[i]);
    }
}

int main(){
    /* finding username */
    struct passwd *pw;
    uid_t uid;
    int c;

    uid = getuid();
    pw = getpwuid(uid);
    if (!pw){
        fprintf (stderr,"%s: cannot find username for UID %u\n",__PROGRAM_NAME__,(unsigned) uid);
        exit (EXIT_FAILURE);
    }
    username = (char *)malloc((strlen(pw->pw_name) + 2) * sizeof(char));
    strcpy(username,pw -> pw_name);
    
    /* find hostname */
    osname = (char *)malloc(HOST_MAX*sizeof(char));
    gethostname(osname,HOST_MAX);

    /* find home directory ~ */
    pwd_home();

    while(1){

        size_t bufsize = BUF_MAX;
        char *buffer = (char *)malloc(BUF_MAX*sizeof(char));
        char *token;
        char *cur_dir = NULL;

        cur_dir = pwd_cur();
        printf("<%s@%s:%s>",username,osname,cur_dir);
        scanf("%[^\n]%*c", buffer);

        char *argv[64];
        token = strtok(buffer,";");
        while(token != NULL){
            parse(token,argv);
            //replace_home(argv);
            
            /* if the command is exit */
            if(strcmp(argv[0],"exit")==0)
                exit(0);

            /* if the command is cd */
            else if(strcmp(argv[0],"cd") == 0)
                change_dir(argv[1]);
            
            /* for every other command */
            else
                execute(argv);
            token = strtok(NULL,";");
        }
    }
    return 0;
}