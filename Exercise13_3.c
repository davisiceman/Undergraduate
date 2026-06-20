#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

void* thread1_func(void* arg) {
    char* str = "ping";
    int len = strlen(str);
    int i = 0;
    while (1) {
        putc(str[i], stdout);
        fflush(stdout);
        i = (i + 1) % len;
        usleep(100000); // Sleep for 100,000 microseconds
    }
    return NULL;
}

void* thread2_func(void* arg) {
    char* str = "pong";
    int len = strlen(str);
    int i = 0;
    while (1) {
        putc(str[i], stdout);
        fflush(stdout);
        i = (i + 1) % len;
        usleep(100000); // Sleep for 100,000 microseconds
    }
    return NULL;
}

int main() {
    pthread_t thread1, thread2;

    pthread_create(&thread1, NULL, thread1_func, NULL);
    pthread_create(&thread2, NULL, thread2_func, NULL);

    sleep(5); // Allow the threads to run for 5 seconds
    pthread_cancel(thread1);
    pthread_cancel(thread2);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    return 0;
}
