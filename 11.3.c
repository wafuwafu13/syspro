#include <stdio.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_NUM 10000000

typedef struct {
    int start;
    int end;
    int count;
} PrimeCountArgs;

bool is_prime(int n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

void *count_primes(void *arg) {
    PrimeCountArgs *args = (PrimeCountArgs *)arg;
    args->count = 0;
    for (int i = args->start; i <= args->end; i++) {
        if (is_prime(i)) {
            args->count++;
        }
    }
    return NULL;
}

int main() {
    pthread_t thread;
    PrimeCountArgs thread_args = {1, MAX_NUM / 2, 0};
    PrimeCountArgs main_args = {MAX_NUM / 2 + 1, MAX_NUM, 0};

    pthread_create(&thread, NULL, count_primes, &thread_args);

    count_primes(&main_args);

    pthread_join(thread, NULL);

    int total_primes = thread_args.count + main_args.count;
    printf("Total number of primes up to %d: %d\n", MAX_NUM, total_primes);

    return 0;
}