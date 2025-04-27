#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>

time_t start;
int ctrl_z_count = 0;

void handle_sigint(int sig);
void handle_sigtstp(int sig);
void stop(int sig);

int main() {
    time(&start);
    signal(SIGINT, handle_sigint);   // Ctrl+C
    signal(SIGTSTP, handle_sigtstp); // Ctrl+Z
    
    while(1) {
        sleep(1);
        fprintf(stderr, ".");
    }
    return 0;
}

void handle_sigint(int sig) {
    if (ctrl_z_count >= 2) {
        stop(sig);
    }
}

void handle_sigtstp(int sig) {
    ctrl_z_count++;
}

void stop(int sig) {
    time_t end;
    time(&end);
    fprintf(stderr, "\n シグナル番号=%d, 実行時間= %ld 秒\n", sig, end-start);
    exit(0);
}