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
#include <sys/utsname.h>
#include <regex.h>

#define __PROGRAM_NAME__ "hash"
#define BUF_MAX 4096

char *osname;
char *username;
char *cur_dir;
char *home_dir;

void pwd_home(){
    long size;
    char *buf;

    size = pathconf(".", _PC_PATH_MAX);

    if ((buf = (char *)malloc((size_t)size)) != NULL){
        home_dir = getcwd(buf, (size_t)size);
        cur_dir = getcwd(buf, (size_t)size);
    }
}

int change_curdir(char *dir){
    return 0;
}

int change_dir(char *dir){
    if(strcmp(dir,"."))
        return 0;

    chdir(dir);
    change_curdir(dir);
    return 0;
}

int replace_string(char *str, char *substr, char *repstr){
    regex_t reg;
    int ret_val = regcomp(&reg,substr,0);
    if(ret_val)
        fprintf(stderr,"%s : regex compilation\n",__PROGRAM_NAME__);

    if(regexec(&reg,str,0,NULL,0))
        return 1;

    return 0;
}

char* distro_name(char *reg_str){
    /* string matching to find information of process */
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    char *filename = (char *)malloc((strlen("/etc/os-release") + 2)*sizeof(char)) ;
    strcpy(filename,"/etc/os-release");

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

    osname = (char *)malloc((strlen(line) - 3 + 2)*sizeof(char));
    strncpy(osname,line + 3,strlen(line) - 4);

    /* closing the files and refrences */
    fclose(fp);
    if (line)
        free(line);
    return osname;
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
    
    /* find os distribution name */
    distro_name("ID");

    /* find home directory ~ */
    pwd_home();

    size_t bufsize = BUF_MAX;
    char *buffer = (char *)malloc(BUF_MAX*sizeof(char));
    while(strcmp(buffer,"exit")){
        printf("<%s@%s:%s>",username,osname,cur_dir);
        scanf("%[^\n]%*c", buffer); 
        printf("The command entered is : %s\n",buffer);
    }
    return 0;
}