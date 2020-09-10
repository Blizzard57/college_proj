/* 

Header file for history command. This is 
done to add ls command functionality 
in the main shell code

*/

#ifndef HISTORY_H_
#define HISTORY_H_

int add_history(char *command,char *username);

int retrieve_history(int argc,char **argv,char *username);

#endif // HISTORY_H_