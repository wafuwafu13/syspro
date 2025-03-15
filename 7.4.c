#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

int pid;
int ctrl_z_pressed = 0;
time_t last_activity_time;

int main(void) {
    void display();
    void send();
    void handle_sigtstp();
    int st;

    signal(SIGTSTP, handle_sigtstp);
    time(&last_activity_time);

    // 返り値
    // 親プロセスには子プロセスのプロセス ID
    // 子プロセスには 0
    pid = fork();
    fprintf(stderr, "PID1=%d\n", pid); // 6152 0
    fprintf(stderr, "PID2=%d\n", getpid()); // 6151 6152

    if (pid == 0) {
        sleep(600);
    }
    else {
        while(1) {
            if (ctrl_z_pressed) {
                send();
                break;
            }
            else {
                time_t current_time;
                time(&current_time);
                if (difftime(current_time, last_activity_time) >= 3) {
                    display();
                    time(&last_activity_time);
                }
            }
            sleep(1);
        }

        fprintf(stderr, "PID5=%d\n", pid); // 6152
        fprintf(stderr, "PID6=%d\n", getpid()); // 6151
        printf("終了\n");
    }
    return EXIT_SUCCESS;
}

void handle_sigtstp(int sig) {
    ctrl_z_pressed = 1;
}

void display() {
    printf("Press Ctrl+Z\n");
}

void send() {
    sleep(1);
    fprintf(stderr, "PID3=%d\n", pid); // 6152
    fprintf(stderr, "PID4=%d\n", getpid()); // 6151
    kill(pid, SIGINT);
}