/* 

Header file for setenv and unsetenv command. 
This is done to add ls command functionality 
in the main shell code

*/

#ifndef SET_ENV_H_
#define SET_ENV_H_

int set_env(int argc,char **argv);

#endif // SET_ENV_H_

#ifndef UNSET_ENV_H_
#define UNSET_ENV_H_

int unset_env(int argc,char **argv);

#endif // UNSET_ENV_H_

#ifndef GET_ENV_H_
#define GET_ENV_H_

int get_env(int argc,char **argv);

#endif // GET_ENV_H_