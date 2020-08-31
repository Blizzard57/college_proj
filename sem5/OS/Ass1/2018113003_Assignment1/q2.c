#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define ll long long
#define BUFF_SIZE 8000

ll find_great(ll seek_head){
    // Check and find if the seek_head has more than BUFF_SIZE characters
    if(seek_head > BUFF_SIZE){
            return BUFF_SIZE;
        }
    return seek_head;
}

short check_equivalence(char *str1,char *str2, ll size){
    // Checks if the strings are reverse of one another
    for(int i=0;i<(int)size;i++){
        if(str1[i] != str2[size-1-i])
            return 0;
    }
    return 1;
}

void find_permissions(char *filename,char *filetype){
    struct stat file_stat;
    if (stat(filename, &file_stat) < 0)
        perror("Could not stat file"), exit(1);
    
    char display[100];

    // Checking User Permissions
    if(file_stat.st_mode & S_IRUSR)
        sprintf(display,"User has read permissions on %s: Yes\n",filetype);
    else{
        sprintf(display,"User has read permissions on %s: No\n",filetype);
    }
    write(1,display,strlen(display));
    if(file_stat.st_mode & S_IWUSR)
        sprintf(display,"User has write permissions on %s: Yes\n",filetype);
    else{
        sprintf(display,"User has write permissions on %s: No\n",filetype);
    }
    write(1,display,strlen(display));
    if(file_stat.st_mode & S_IXUSR)
        sprintf(display,"User has execute permissions on %s: Yes\n",filetype);
    else{
        sprintf(display,"User has execute permissions on %s: No\n",filetype);
    }
    write(1,display,strlen(display));

    // Checking Group Permissions
    if(file_stat.st_mode & S_IRGRP)
        sprintf(display,"Group has read permissions on %s: Yes\n",filetype);
    else{
        sprintf(display,"Group has read permissions on %s: No\n",filetype);
    }
    write(1,display,strlen(display));
    if(file_stat.st_mode & S_IWGRP)
        sprintf(display,"Group has write permissions on %s: Yes\n",filetype);
    else{
        sprintf(display,"Group has write permissions on %s: No\n",filetype);
    }
    write(1,display,strlen(display));
    if(file_stat.st_mode & S_IXGRP)
        sprintf(display,"Group has execute permissions on %s: Yes\n",filetype);
    else{
        sprintf(display,"Group has execute permissions on %s: No\n",filetype);
    }
    write(1,display,strlen(display));

    // Checking Others Permissions
    if(file_stat.st_mode & S_IROTH)
        sprintf(display,"Others has read permissions on %s: Yes\n",filetype);
    else{
        sprintf(display,"Others has read permissions on %s: No\n",filetype);
    }
    write(1,display,strlen(display));
    if(file_stat.st_mode & S_IWOTH)
        sprintf(display,"Others has write permissions on %s: Yes\n",filetype);
    else{
        sprintf(display,"Others has write permissions on %s: No\n",filetype);
    }
    write(1,display,strlen(display));
    if(file_stat.st_mode & S_IXOTH)
        sprintf(display,"Others has execute permissions on %s: Yes\n",filetype);
    else{
        sprintf(display,"Others has execute permissions on %s: No\n",filetype);
    }
    write(1,display,strlen(display));
}

int main(int argc,char *argv[]){
    // Default Checking : Correct number of arguments
    if(argc != 4){
        perror("Incorrect Number of Arguments");
        return 0;
    }

    // Checking existence of directory
    struct stat dir_stat;
    if (stat(argv[3], &dir_stat) >= 0 && S_ISDIR(dir_stat.st_mode))
        write(1, "Directory is created: Yes\n", 26);
    else
        write(1, "Directory is created: No\n", 25);

    // Checking if the files are reverse of one another
    // Both files need to be read, hence O_RDONLY

    // Opening and checking if the files are present
    int old_file = open(argv[1],O_RDONLY);
    if(old_file < 0){
        perror("Error occured on the old file");
        return 0;
    }

    int new_file = open(argv[2],O_RDONLY);
    if(new_file < 0){
        perror("Error occured on the new file");
        return 0;
    }

    // Finding lengths of files
    ll size_old = lseek(old_file,0,SEEK_END);
    ll size_new = lseek(new_file,0,SEEK_END);
    // Resetting the new file back to start
    lseek(new_file,0,SEEK_SET);

    // Eliminating trivial condition
    short bool_flag = 1; // flag = 1 -> new file is the reverse
    if(size_new != size_old)
        bool_flag = 0;
    
    // Looping and checking
    if(bool_flag == 1){
        // Checking in chunks
        // Hence creating buffers
        char buff_old[BUFF_SIZE + 200];
        char buff_new[BUFF_SIZE + 200];

        // Creating seek head to keep the current pointer
        ll seek_head = size_old;
        ll seek_change;
        int size_old,size_new;
        
        do{
            seek_change = find_great(seek_head);
            seek_head -= seek_change;
            
            // Reading both the files and dumping content on the buffers
            lseek(old_file,seek_head,SEEK_SET);
            size_old = read(old_file,buff_old,seek_change);
            size_new = read(new_file,buff_new,size_old);
            
            // Checking if the buffers have reverse strings
            if(check_equivalence(buff_new,buff_old,size_old) == 0){
                bool_flag = 0;
            }
        }while(seek_head > 0);
    }

    // If flag remains 1 then the files are reversed
    if(bool_flag == 1)
        write(1,"Whether file contents are reversed in newfile: Yes\n",51);
    else
        write(1, "Whether file contents are reversed in newfile: No\n", 50);

    // Checking file permissions
    find_permissions(argv[1],"newfile");
    find_permissions(argv[2],"oldfile");
    find_permissions(argv[3],"directory");

    return 0;
}