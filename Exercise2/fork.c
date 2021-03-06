#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>

void err_sys(const char* info) { 
    fprintf(stderr, "ERROR: %s: %s\n", info, strerror(errno)); 
    exit(EXIT_FAILURE); 
}

int global = 1314;
int main(int argc, const char *argv[]) {
    int local;
    pid_t pid;
    local = 520;

    printf("\nbefore fork\n");
    
    pid = fork();

    if (pid < 0) {
        err_sys("fork error");
    } else if (0 == pid) {
        global++;
        local--;
        printf("\nchild process\n");
        printf("pid=%d, global=%d, local=%d\n\n", getpid(), global, local);
    } else {
        printf("\nparent process\n");
        printf("pid=%d, global=%d, local=%d\n", getpid(), global, local);
    }
    
    exit(0);
}