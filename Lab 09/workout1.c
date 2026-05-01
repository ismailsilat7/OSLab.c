#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void sigint_handler(int sig) {
    write(STDOUT_FILENO, "\nSIGINT caught!\n", 16); //async-signal-safe
    // STDOUT_FILENO is just the integer 1, followed by string then its length
    // to terminate the program we can use exit(0) or raise(SIGKILL); SIGKILL & SIGSTOPP can also bypass signal handlers entirely as they are enforced by the kernel
    // exit(0) calls cleanup functions registered with atexit() and flushes buffers before terminating — clean shutdown
    // raise(SIGKILL) is enforced by the kernel directly, no cleanup, no handlers, instant death
    raise(SIGKILL);
}

void my_handler(int sig) {
    printf("\nUserdefined signal was called :D\n");
}

int main() {
    signal(SIGINT, sigint_handler);
    signal(SIGUSR1, my_handler);
    printf("Program running... Press Ctrl+C\n");
    while (1) {
        sleep(1);
        kill(getpid(), SIGUSR1);
    }
    return 0;
}