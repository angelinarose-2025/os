#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
    // fork() example
    pid_t pid = fork();
    if (pid == 0) {
        printf("Child Process\n");
    } else {
        printf("Parent Process\n");
        wait(NULL); // Ensure parent waits for child
    }
    
    // exec() example
    if (fork() == 0) {
        execlp("/bin/ls", "ls", NULL);
        exit(0);
    } else {
        wait(NULL);
    }

    // getpid() example
    printf("Process ID: %d\n", getpid());

    // exit() example
    if (fork() == 0) {
        printf("Exiting child process\n");
        exit(0);
    } else {
        wait(NULL);
    }
    
    // close() example
    int fd = open("file.txt", O_CREAT | O_WRONLY, 0644);
    if (fd >= 0) {
        write(fd, "Hello", 5);
        close(fd);
    }
    
    // stat() example
    struct stat s;
    if (stat("file.txt", &s) == 0) {
        printf("File size: %ld bytes\n", s.st_size);
    }
    
    // opendir(), readdir() example
    DIR *d = opendir(".");
    struct dirent *dir;
    if (d) {
        while ((dir = readdir(d)) != NULL) {
            printf("%s\n", dir->d_name);
        }
        closedir(d);
    }
    
    return 0;
}
