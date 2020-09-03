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
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

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

#define ll long long

#define FILE_LENGTH 2000
#define NAME_LENGTH 200

int find_perm(char *ans, char *filename){
    /* finds the rwx permissions for user, group and others */
    struct stat file_stat;
    if (stat(filename, &file_stat) < 0){
        fprintf(stderr,"ls : connot access %s\n",filename);
        return 1;
    }
    /* checking if the given file is a directory */
    if(S_ISDIR(file_stat.st_mode))
        ans[0] = 'd';

    /* finding permissions for user */
    if(file_stat.st_mode & S_IRUSR)
        ans[1] = 'r';
    if(file_stat.st_mode & S_IWUSR)
        ans[2] = 'w';
    if(file_stat.st_mode & S_IXUSR)
        ans[3] = 'x';
    
    /* finding permissions for group */
    if(file_stat.st_mode & S_IRGRP)
        ans[4] = 'r';
    if(file_stat.st_mode & S_IWGRP)
        ans[5] = 'w';
    if(file_stat.st_mode & S_IXGRP)
        ans[6] = 'x';

    /* finding permissions for other */
    if(file_stat.st_mode & S_IROTH)
        ans[7] = 'r';
    if(file_stat.st_mode & S_IWOTH)
        ans[8] = 'w';
    if(file_stat.st_mode & S_IXOTH)
        ans[9] = 'x';

    return 0;
}

ll int find_filesize(char *filename){
    /* find size of file in bytes */
    int file = open(filename,O_RDONLY);
    if(file < 0){
        fprintf(stderr,"ls : cannot access %s\n", filename);
        return -1;
    }
    ll int size = lseek(file,0,SEEK_END);
    return size;
}

int find_owner(char *owner,char *group, char *filename){
    /* find owner and group of a file */
    struct stat file_stat;
    if (stat(filename, &file_stat) < 0){
        fprintf(stderr,"ls : cannot access %s\n", filename);
        return 1;
    }
    struct passwd *pwd = getpwuid(file_stat.st_uid);
    struct group  *grp = getgrgid(file_stat.st_gid);

    if(pwd == 0 || grp == 0){
        fprintf(stderr,"ls : cannot access %s\n", filename);
        return 1;
    }

    strcpy(owner,pwd->pw_name);
    strcpy(group,grp->gr_name);
    return 0;
}

int find_hardlinks(char *filename){
    struct stat file_stat;
    if (stat(filename, &file_stat) < 0){
        fprintf(stderr,"ls : cannot access %s\n", filename);
        return -1;
    }
    return file_stat.st_nlink;
}

int find_mod_date(char *month,char *date,char *time, char *filename){
    /* find modification date, month and time */
    struct stat file_stat;
    if (stat(filename, &file_stat) < 0){
        fprintf(stderr,"ls : cannot access %s\n", filename);
        return 1;
    }
    strftime(month, sizeof(month), "%b", localtime(&(file_stat.st_mtime)));
    strftime(time, sizeof(time), "%H:%M",localtime(&(file_stat.st_mtime)));
    strftime(date, sizeof(date), "%d",localtime(&(file_stat.st_mtime)));
    return 0;
}

int find_maxlength(int max,int val){
    /* returns max(val1,val2) */
    if(max > val)
        return max;
    return val;
}

int list(char *dir, short bool_a,short bool_l){
    struct dirent **namelist;
    int no_of_files;

    no_of_files = scandir(dir,&namelist,0,alphasort);
    if(no_of_files < 0){
        perror("ls");
        return 1;
    }
    if(bool_l){
        int max_owner = 0,max_group = 0;
        for(int i=0;i<no_of_files;i++){
            char *filename = (char *)malloc((strlen(dir) + strlen(namelist[i] -> d_name) + 2)*sizeof(char));
            strcpy(filename,dir);
            strcat(filename,"/");
            strcat(filename,namelist[i] -> d_name);

            char owner[NAME_LENGTH];
            char group[NAME_LENGTH];
            if(find_owner(owner,group,filename))
                continue;

            max_owner = find_maxlength(max_owner,strlen(owner));
            max_group = find_maxlength(max_group,strlen(group));
        }

        for(int i=0;i<no_of_files;i++){
            if(bool_a == 0 && namelist[i] -> d_name[0] == '.')
                continue;
            
            /* filename containing absolute path,
               and dynamically allocating size for it */
            char *filename = (char *)malloc((strlen(dir) + strlen(namelist[i] -> d_name) + 2)*sizeof(char));
            strcpy(filename,dir);
            strcat(filename,"/");
            strcat(filename,namelist[i] -> d_name);

            /* individual elements are modified in the find_perm function, 
               hence perm is given as a char array and not a string */
            char perm[11] = {'-','-','-','-','-','-','-','-','-','-','\0'}; 
            if(find_perm(perm, filename))
                continue;

            /* finding number of hardlinks */
            int hard_links = find_hardlinks(filename);
            if(hard_links == -1)
                continue;

            /* finding owner and group */
            char owner[NAME_LENGTH];
            char group[NAME_LENGTH];
            if(find_owner(owner,group,filename))
                continue;

            /* finding filesize */
            float size = 4.0; // Default size for directories
            char suffix = 'B'; // Suffix for KB,MB and GB
            short no_of_mults = 0;
            
            /* dividing the filesize by 1024 
               to find the size in MB,GB,etc */
            if(perm[0] != 'd'){
                size = find_filesize(filename);
                if(size == -1)
                    continue;
                while(size > 1024){
                    size/=1024;
                    no_of_mults++;
                }
            }
            else
                no_of_mults = 1;

            /* finding the suffix of filesize */
            if(no_of_mults == 1)
                suffix = 'K'; /* kilobytes */
            else if(no_of_mults == 2)
                suffix = 'M'; /* megabytes */
            else if(no_of_mults == 3)
                suffix = 'G'; /* gigabytes */
            else if(no_of_mults == 4)
                suffix = 'T'; /* terabytes */
            
            /* finding the modification date */
            char month[4], date[4], time[6];
            if(find_mod_date(month,date,time,filename))
                continue;

            printf("%s %3d %-*s %-*s %7.2lf%c %3s %2s %s %s\n",perm,hard_links,max_owner,owner,max_group,group,size,suffix,month,date,time,namelist[i] -> d_name);
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