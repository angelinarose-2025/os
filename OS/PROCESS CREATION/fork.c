#include <stdio.h>
#include <unistd.h>

int main() {
    int x = 100;
    pid_t pid = fork();
    
    if (pid == 0) {
        x += 50;
        printf("Child: x = %d\n", x);
    } else {
        x -= 50;
        printf("Parent: x = %d\n", x);
    }
    return 0;
}

