#include <stdio.h>
#include <unistd.h>

int main() {
    int fd[2];
    pipe(fd);
    
    if (fork() == 0) {
        printf("hello\n");
        close(fd[0]);  
        write(fd[1], "x", 1);  
    } else {
        char buf;
        close(fd[1]);  
        read(fd[0], &buf, 1); 
        printf("goodbye\n");
    }
    return 0;
}

