#include <fcntl.h>
#include <math.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>

#define stater struct termios

void raw() {
    stater termas;
    tcgetattr(0, &termas);
    termas.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(0, TCSANOW, &termas);
}

void NotRaw() {
    stater termas;
    tcgetattr(0, &termas);
    termas.c_lflag |= ICANON | ECHO;
    tcsetattr(0, TCSANOW, &termas);
}

int keyboardWasPressed() {
    int bytes;
    raw();
    ioctl(0, FIONREAD, &bytes);
    int ans = bytes > 0;
    NotRaw();
    return ans;
}