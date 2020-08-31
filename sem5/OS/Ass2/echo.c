/* 

Code for echo, a built in POSIX command. The code 
replicates the function of that command, but has a 
smaller list of requirements.

Echo commands prints everything written as an argument 
to it on the stdout.

Example :

> echo Hello World
  Hello World
>

The requirements are :

- Basic Functionality
- Multiline strings and ENV varibles not required

The code is written by : Kalp Shah

*/

#include<stdio.h>

int main(int argc,char **argv){
    // Echo requires atleast 2 arguments to function
    if(argc < 2){
        perror("Error : Arguments Missing");
        return 1;
    }

    // Printing the arguments
    for(int i=0;i<argc - 1;i++){
        printf("%s ",argv[i+1]);
    }

    /* ZSH adds a \n and a highlighted % sign for a 
    partial line, hence a \n to make it a complete line*/ 
    printf("\n");
    
    return 0;
}