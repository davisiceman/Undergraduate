#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <semaphore.h>
#include <sys/stat.h>

#define SHARED_FILE "shared_file.txt"
#define SEMAPHORE_NAME "/semaphore_sync"

int main() {
    int fd;
    char buffer[100];
    ssize_t bytes_read;

    // Open or create semaphore
    sem_t *sem = sem_open(SEMAPHORE_NAME, O_CREAT, 0666, 1);
    if (sem == SEM_FAILED) {
        perror("Error creating semaphore");
        return 1;
    }

    // Open the shared file
    fd = open(SHARED_FILE, O_RDWR | O_CREAT | O_TRUNC, 0666);
    if (fd < 0) {
        perror("Error opening shared file");
        sem_close(sem);
        sem_unlink(SEMAPHORE_NAME);
        return 1;
    }

    while (1) {
        // Wait for semaphore
        sem_wait(sem);

        // Write "Hello B" to the shared file
        lseek(fd, 0, SEEK_SET); // Move to the beginning of the file
        write(fd, "Hello B\n", strlen("Hello B\n"));
        fsync(fd); // Ensure data is written to the file
        printf("Program A: Sent 'Hello B'\n");

        // Read "Hello A" from the shared file
        lseek(fd, 0, SEEK_SET);
        bytes_read = read(fd, buffer, sizeof(buffer) - 1);
        if (bytes_read > 0) {
            buffer[bytes_read] = '\0'; // Null-terminate the string
            printf("Program A: Received '%s'\n", buffer);
        }

        // Post to semaphore
        sem_post(sem);

        sleep(1); // Add a delay for alternation
    }

    // Clean up
    close(fd);
    sem_close(sem);
    sem_unlink(SEMAPHORE_NAME);
    return 0;
}
