#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void* thread_func(void* arg) {
    while (1) {
        printf("hello world\n");
        sleep(1);
    }
    return NULL;
}

int main() {
    pthread_t thread;
    pthread_create(&thread, NULL, thread_func, NULL);
    sleep(5); // Allow the thread to run for 5 seconds
    pthread_cancel(thread); // Cancel the thread
    pthread_join(thread, NULL);
    return 0;
}
