#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void handler(int sig) {
    printf("\nSIGINT received using sigaction\n");
    exit(0);
}

int main() {
    struct sigaction sa;
    sa.sa_handler = handler; // points to actual handler function
    // sa_handler can have a function pointer, SIG_DFL (default handling), SIG_IGN (ignore the signal)
    sigemptyset(&sa.sa_mask); // empty set; block nothing extra
    // sa.sa_mask: a set of additional signals to block while the handler is executing (so another signal can't interrupt your handler mid-run)

    // sigfillset(&sa.sa_mask); // block ALL signals during handler
    // sigaddset(&sa.sa_mask, SIGTERM); // block specific signal during handler
    // sigdelset(&sa.sa_mask, SIGTERM); // remove specific signal from mask
   
    sa.sa_flags = SA_RESTART;
    // sa.sa_flags: behaviour flags like SA_RESTART
    // SA_RESTART Auto-restart interrupted system calls 
    // SA_RESETHAND Reset handler to SIG_DFL after first signal (one-shot)
    // SA_NODEFER Don't block the signal while handler is running
    // SA_SIGINFO Use sa_sigaction instead of sa_handler (gives extra signal info)
    // 0 No special behaviour
    sigaction(SIGINT, &sa, NULL);
    
    printf("Running... Press Ctrl+C\n");
    while (1) {
        sleep(1);
    }
    return 0;
}