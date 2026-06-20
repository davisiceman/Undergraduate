#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define SHARED_FILE "shared_file.txt"

int main() {
    int fd;
    char buffer[100];
    ssize_t bytes_read;

    // Open the shared file
    fd = open(SHARED_FILE, O_RDWR | O_CREAT, 0666);
    if (fd < 0) {
        perror("Error opening file");
        return 1;
    }

    while (1) {
        // Lock the file for reading
        lockf(fd, F_LOCK, 0);
        // Wait for and read "Hello B"
        bytes_read = read(fd, buffer, sizeof(buffer) - 1);
        if (bytes_read > 0) {
            buffer[bytes_read] = '\0';
            printf("%s", buffer);  // Print the message from A
        }
        lseek(fd, 0, SEEK_SET);  // Move file pointer to the beginning
        ftruncate(fd, 0);  // Clear the file content
        lockf(fd, F_ULOCK, 0);  // Unlock the file

        // Lock the file for writing
        lockf(fd, F_LOCK, 0);
        // Write "Hello A" to the shared file
        write(fd, "Hello A\n", strlen("Hello A\n"));
        fsync(fd);  // Ensure the content is written to disk
        lseek(fd, 0, SEEK_SET);  // Move file pointer to the beginning
        lockf(fd, F_ULOCK, 0);  // Unlock the file

        sleep(1);  // Add a small delay for smooth alternation
    }

    close(fd);
    return 0;
}
