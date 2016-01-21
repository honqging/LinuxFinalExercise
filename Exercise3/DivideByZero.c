#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdlib.h>
#include <setjmp.h>
#include <string.h>

sigjmp_buf sigEnv;
void handle_SIGFPE(int sigfpe);

int main(int argc, const char *argv[]) {
    int a = 10;
    int b = 0;
    //判断a/b的时候会怎么样

    if (signal(SIGFPE, handle_SIGFPE) == SIG_ERR)
        printf("Error: signal error\n");
    
    int signalJump = sigsetjmp(sigEnv, 1);
    printf("signaljump: %d\n", signalJump);

    if (0 == signalJump) {
        printf("%d\n", a / b);
    } else {
        printf("%d signal jump is finished successfully. \n", signalJump);
    }
    
    exit(EXIT_SUCCESS);
}

void handle_SIGFPE(int sigfpe) {
    if (sigfpe == SIGFPE) {
        printf("Cannot be divided by 0.\n");
        siglongjmp(sigEnv, SIGFPE);
    }
}
