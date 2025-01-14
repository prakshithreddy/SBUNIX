#ifndef _UNISTD_H
#define _UNISTD_H

#include <sys/defs.h>

int open(const char *pathname, int flags);
int close(int fd);
ssize_t read(int fd, void *buf, size_t count);
ssize_t write(int fd, const void *buf, size_t count);
//int unlink(const char *pathname);

int chdir(const char *path);
char *getcwd(char *buf, size_t size);

pid_t fork();

//int dup(int oldfd);


int execvpe(const char *file, char *const argv[], char *const envp[]);

int execve(const char *file, char *const argv[], char *const envp[]);

unsigned int sleep(unsigned int seconds);
int waitpid(int pid, int *status,int options);

pid_t getpid(void);
pid_t getppid(void);


// OPTIONAL: implement for ``on-disk r/w file system (+10 pts)''
off_t lseek(int fd, off_t offset, int whence);
int mkdir(const char *pathname, mode_t mode);

// OPTIONAL: implement for ``signals and pipes (+10 pts)''
int pipe(int pipefd[2]);

#endif
