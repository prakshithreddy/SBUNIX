#ifndef _SIGNAL_H
#define _SIGNAL_H

#include <sys/defs.h>

int kill(int64_t pid, int sig);

// OPTIONAL: implement for ``signals and pipes (+10 pts)''
typedef void (*sighandler_t)(int);
sighandler_t signal(int signum, sighandler_t handler);
int alarm(int seconds);

#endif
