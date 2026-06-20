#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

#define MAX_WORDS 100
#define WORD_LENGTH 50

char word_array[MAX_WORDS][WORD_LENGTH];
int word_count = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* thread1_func(void* arg) {
    FILE* file = fopen("words.txt", "r");
    if (file == NULL) {
        perror("Failed to open file");
        return NULL;
    }

    // Read words from the file into the array
    while (fscanf(file, "%s", word_array[word_count]) != EOF && word_count < MAX_WORDS) {
        word_count++;
    }
    fclose(file);

    int i = 0;
    while (1) {
        pthread_mutex_lock(&mutex);
        printf("[Thread 1] Sending: %s\n", word_array[i]);
        fflush(stdout);
        pthread_mutex_unlock(&mutex);

        i = (i + 1) % word_count;
        sleep(1);
    }
    return NULL;
}

void* thread2_func(void* arg) {
    int i = 0;
    while (1) {
        pthread_mutex_lock(&mutex);
        printf("[Thread 2] Received: %s\n", word_array[i]);
        fflush(stdout);
        pthread_mutex_unlock(&mutex);

        i = (i + 1) % word_count;
        sleep(1);
    }
    return NULL;
}

int main() {
    pthread_t thread1, thread2;

    pthread_create(&thread1, NULL, thread1_func, NULL);
    pthread_create(&thread2, NULL, thread2_func, NULL);

    sleep(10); // Allow the threads to run for 10 seconds
    pthread_cancel(thread1);
    pthread_cancel(thread2);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    return 0;
}
