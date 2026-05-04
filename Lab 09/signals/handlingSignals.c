#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

// cant send data, they are just notifications/software interrupt
// shld not print to screen, or modify data asw
// shld only call async-signal-safe functions inside handlers
void handle_sigtstp(int sig) {
    // printf not allowed in sig_handler as its not sync
    printf("Stop not allowed\n");
}

void handle_sigcont(int sig) {
    // printf not allowed in sig_handler as its not sync
    printf("Input number: ");
    fflush(stdout);
}

int main(int argc, char* argv[]) {
    struct sigaction sa;
    sa.sa_handler = &handle_sigtstp;
    sa.sa_flags = SA_RESTART; // only when using scanf
    sigaction(SIGCONT, &sa, NULL);


    // signal(SIGTSTP, &handle_sigtstp); // instead of the above we can simply use this but 

    int x;
    printf("Input number: ");
    scanf("%d", &x);
    printf("Result %d * 5 = %d\n", x, x * 5);
    return 0;
}
