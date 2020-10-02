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
#include <fcntl.h>
#include <sys/stat.h>

#include "ls.h"
#include "pinfo.h"
#include "pwd.h"
#include "echo.h"
#include "history.h"
#include "nightswatch.h"
#include "env.h"
#include "jobs.h"
#include "proc.h"

#define __PROGRAM_NAME__ "hash"
#define BUF_MAX 4096
#define HOST_MAX 64

char *osname;
char *username;
char *home_dir;
char *prev_dir;

int fore_proc = 0;

struct job{
    char *command;
    pid_t pgid;
    struct job *next;
};

struct job *top = NULL;

int  parse(char *line, char **argv){
    /* External Functions : Taken From http://www.csl.mtu.edu/cs4411.ck/www/NOTES/process/fork/exec.html */
    int no_of_params = 0;
    while (*line != '\0') {       /* if not the end of line */ 
        while (*line == ' ' || *line == '\t' || *line == '\n')
            *line++ = '\0';     /* replace white spaces with 0 */
        
        /* save the argument position */
        no_of_params++;
        *argv++ = line;

        while (*line != '\0' && *line != ' ' &&  *line != '\t' && *line != '\n') 
            line++;             /* skip the argument until ...    */
    }
    *argv = '\0';                 /* mark the end of argument list  */
    return no_of_params;
}

void add_jobs(char *command,pid_t pid){
    struct job *new_job = (struct job*)malloc(sizeof(struct job));
    new_job->command = command;
    new_job->next = NULL;
    new_job->pgid = pid;

    struct job *parent_job = NULL;
    //struct job *child_job = NULL;

    if(top == NULL){
        top = new_job;
    }
    else{
        parent_job = top;
        //child_job = parent_job->next;
        while(parent_job -> next != NULL){
            parent_job = parent_job->next;
        }
        parent_job->next = new_job;
    }
}

void print_jobs(){
    int i = 1;
    struct job *temp_job = top;
    while (temp_job != NULL){
        char stat = job_proc(temp_job->pgid);
        if(stat == 'R')
            printf("[%d] Running %s [%d]\n",i++,temp_job->command,temp_job->pgid);
        else if(stat == 'T')
            printf("[%d] Stopped %s [%d]\n",i++,temp_job->command,temp_job->pgid);
        else if(stat == 'S')
            printf("[%d] Sleeping %s [%d]\n",i++,temp_job->command,temp_job->pgid);
        else if(stat == 'Z')
            printf("[%d] Zombie %s [%d]\n",i++,temp_job->command,temp_job->pgid);
        temp_job = temp_job->next;
    }
}

int kjobs(int argc,char **argv){
    if(argc > 3){
        fprintf(stderr,"kjobs : too many arguments\n");
        return -1;
    }
    else if(argc < 3){
        fprintf(stderr,"kjobs : arguments missing\n");
        return -1;
    }

    if(check_Nan(argv[1])){
        fprintf(stderr,"kjobs : %s is invalid process ID\n",argv[1]);
        return -1;
    }
    if(check_Nan(argv[2])){
        fprintf(stderr,"kjobs : %s is invalid signmal number\n",argv[2]);
        return -1;
    }
    kill(atoi(argv[1]),atoi(argv[2]));
}

int overkill(){
    struct job *temp_job = top;
    while (temp_job != NULL){
        char stat = job_proc(temp_job->pgid);
        if(stat != 'N')
            kill(temp_job->pgid, SIGTERM);
            usleep(1000);
            int st;
            waitpid(temp_job->pgid, &st, WNOHANG);
            kill(temp_job->pgid, SIGKILL);
        temp_job = temp_job->next;
    }
}

void execute(char **argv,short bg_flag){
    pid_t  pid;
    int    status;

    /* fork a child process */
    if ((pid = fork()) < 0) {
        fprintf(stderr,"%s: forking child process failed\n",__PROGRAM_NAME__);
        exit(1);
    }

    /* Child does the process */
    else if (pid == 0) {
        setpgid(0,0);
        if (execvp(*argv, argv) < 0) {     /* execute the command  */
            fprintf(stderr,"%s: unknown command %s\n",__PROGRAM_NAME__,argv[0]);
            exit(1);
        }
        fore_proc = getpid();
    }
    /* Parent waits */
    else {
        if(!bg_flag){
            signal(SIGTTOU,SIG_IGN);
            signal(SIGTTIN,SIG_IGN);
            setpgid(pid,0);
            tcsetpgrp(0,__getpgid(pid));
            int status;
            waitpid(pid,&status,WUNTRACED);
            tcsetpgrp(0,getpgrp());
            signal(SIGTTIN,SIG_DFL);
            signal(SIGTTOU,SIG_DFL);
        }
        else{
            setpgid(pid,0);
            tcsetpgrp(0,getpgrp());
        }
        add_jobs(argv[0],pid);
    }
    fore_proc = getpid();
}

void get_prevdir(){
    long size;
    char *buf;
    char *cur_dir, *result;

    size = pathconf(".", _PC_PATH_MAX);

    if ((buf = (char *)malloc((size_t)size)) != NULL)
        prev_dir = getcwd(buf, (size_t)size);

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
    /* find the home directory */
    long size;
    char *buf;

    size = pathconf(".", _PC_PATH_MAX);

    if ((buf = (char *)malloc((size_t)size)) != NULL){
        home_dir = getcwd(buf, (size_t)size);
        prev_dir = getcwd(buf, (size_t)size);
    }
}

int change_dir(char *dir){
    /* implements the functionality of the cd command */
    if(dir == NULL || !strcmp(dir,"~")){
        chdir(home_dir);
        return 0;
    }
    else if(!strcmp(dir,"-")){
        chdir(prev_dir);
        return 0;
    }
    chdir(dir);
    return 0;
}

void display_screen(){
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
}

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

    else if(!strcmp(argv[0],"jobs"))
        print_jobs();

    else if(!strcmp(argv[0],"fg"))
        fg(no,argv);

    else if(!strcmp(argv[0],"bg"))
        bg(no,argv);

    else if(!strcmp(argv[0],"kjobs"))
        kjobs(no,argv);

    else if(!strcmp(argv[0],"overkill"))
        overkill();

    /* for every other command */
    else
        execute(argv,bg_flag);
}

int redirection(int no,char **argv,int bg_flag,char *token){
    int inred = 0,outred = 0, appred = 0;
    int in_flag = 0,out_flag = 0,app_flag = 0;
    
    for(int i=0;i<no;i++){
        if(!strcmp(argv[i],"<")){
            if(i == no - 1){
                fprintf(stderr,"%s : no file entered at redirection <\n",__PROGRAM_NAME__);
                return -1; // Return Code for Error
            }
            inred = open(argv[i+1], O_RDONLY);
            if(inred == -1){
                fprintf(stderr,"%s : The following file does not exist : %s",__PROGRAM_NAME__,argv[i+1]);
                return 0;
            }
            in_flag = 1;
        }
        else if(!strcmp(argv[i],">")){
            if(i == no - 1){
                fprintf(stderr,"%s : no file entered at redirection >\n",__PROGRAM_NAME__);
                return -1; // Return Code for Error
            }
            outred = open(argv[i+1],  O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
            out_flag = 1;
        }
        else if(!strcmp(argv[i],">>")){
            if(i == no - 1){
                fprintf(stderr,"%s : no file entered at redirection >>\n",__PROGRAM_NAME__);
                return -1; // Return Code for Error
            }
            appred = open(argv[i+1],  O_CREAT | O_RDWR | O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH );
            app_flag = 1;
        }
    }

    if(in_flag == 0 && out_flag == 0 && app_flag == 0)
        return 1;

    int old_stdin = dup(STDIN_FILENO);
    int old_stdout = dup(STDOUT_FILENO);

    if(in_flag != 0){
        dup2(inred,0);
        close(inred);
    }
    
    if(out_flag != 0){
        dup2(outred,1);
        close(outred);
    }
    else if(app_flag != 0){
        dup2(appred,1);
        close(appred);
    }

    for(int i=0;i< no;i++){
        if(!strcmp(argv[i],"<") || !strcmp(argv[i],">") || !strcmp(argv[i],">>")){
            argv[i] = NULL;
            command_exec(i-1,argv,bg_flag);
            break;
        }
    }

    dup2(old_stdin,0);
    dup2(old_stdout,1);

    return 0;
}

void sigC() {
    if (fore_proc > 0 && fore_proc != getpid()) {
        raise(SIGINT);
    }
}

void sigZ() {
    if (fore_proc > 0 && fore_proc != getpid()) {
        raise(SIGTSTP);
    }
}

int main(){
    display_screen();
    signal(SIGINT, sigC); 
    signal(SIGTSTP, sigZ);
    while(1){

        size_t bufsize = BUF_MAX;
        char *buffer = (char *)malloc(BUF_MAX*sizeof(char));
        char *token;
        char *cur_dir = NULL;

        cur_dir = pwd_cur();
        printf("<%s@%s:%s>",username,osname,cur_dir);
        scanf("%[^\n]%*c", buffer);

        add_history(buffer,username);

        token = strtok(buffer,";");
        while(token != NULL){

            char *argv[64];
            char *red_tok = (char *)malloc(BUF_MAX*sizeof(char));
            int no = parse(token,argv);
            short bg_flag = 0;

            /*checks if process is background  */
            if(!strcmp(argv[no-1],"&")){
                argv[no-1] = NULL;
                bg_flag = 1;
                no--;
            }

            if(redirection(no,argv,bg_flag,red_tok) > 0)
                command_exec(no,argv,bg_flag);
            token = strtok(NULL,";");
        }
        fflush(stdout);
    }
    return 0;
}