#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define ll long long
#define FILE_LENGTH 200
#define BUFF_SIZE 8000

int find_index(char *s){
    // Finds the index of the last /
    int len;
    len = strlen(s);
    for(int i=len-1;i>0;i--){
        if(s[i] == '/'){
            return i;
        }
    }
    return -1;
}

void str_rev(char *str, int len) {
    // Reverses a string without a dummy string
    int start = 0, end = len - 1;
    while (start < end) {
        
        str[start] ^= str[end];
        str[end] ^= str[start];
        str[start] ^= str[end];
        
        // Counters
        start++; 
        end--;
    }
}

ll find_great(ll seek_head){
    // Check and find if the seek_head has more than BUFF_SIZE characters
    if(seek_head > BUFF_SIZE){
            return BUFF_SIZE;
        }
    return seek_head;
}

int main(int argc, char **argv){
    // Checking if File has two arguments
    // The two arguments being the program name itself and the file name
    if(argc != 2){
        perror("Error : Arguments Missing");
        return 0;
    }
    
    // Reading the Original File
    int orig = open(argv[1],O_RDONLY);
    if(orig < 0){
        perror("The file entered does not exist, or cannot be read");
        return 0;
    }
    
    // Finding the last / to get the name of the file
    int ans;
    char *name;
    ans = find_index(argv[1]);
    if(ans == -1){
        name = argv[1];
    }
    else{
        name = argv[1] + ans + 1;
    }

    // Reading and creating the reversed file
    char dest[FILE_LENGTH] = "./Assignment/";
    strcat(dest,name); // The relative path of the reversed file
    int rev = open(dest, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
    if(rev < 0){
        if(mkdir("Assignment",0777) == -1){
            perror("Directory not created, please check the file structure");
        }
        rev = open(dest, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
    }

    // Seeking to the end of the original file
    ll size = lseek(orig,0,SEEK_END); // The total filesize     
    // Reversing and Percent
    float per = size/BUFF_SIZE; // Percent (%) done
    ll seek_head = size; // The modifiable seek_head which is at the current location (For lseek)
    ll cnt = 0; //Counter for percent(%)
    
    char buffer[BUFF_SIZE + 200]; //Buffer for temporary storage (Extra 200 for anormalies)
    char text[50];
    ll len; //Dummy Variable for Read
    ll seek_change;

    // Looped Reading and Writing
    do {
        // Read from the original file
        seek_change = find_great(seek_head);
        seek_head -= seek_change;
        lseek(orig, seek_head, SEEK_SET);
        
        // Writing to the reversed file
        len = read(orig, buffer, seek_change);
        str_rev(buffer,len);
        write(rev, buffer, len);
        
        // Calculating and Printing the Progress Bar
        float cent = cnt++/per;
        sprintf(text, "\rProgress: %f Percent", cent*100);
        write(1, text, 50);
    }while (seek_head > 0);
    write(1, "\rProgress: 100.00 Percent\n", 26);
    
    return 0;
}