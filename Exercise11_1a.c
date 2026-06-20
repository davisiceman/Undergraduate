#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define ATOB "AtoB.txt"
#define BTOA "BtoA.txt"

int main() {
    int atob_fd, btoa_fd;
    char buffer[100];
    ssize_t bytes_read;

    // Open files in non-blocking mode
    atob_fd = open(ATOB, O_WRONLY | O_CREAT | O_TRUNC | O_NONBLOCK, 0666);
    btoa_fd = open(BTOA, O_RDONLY | O_NONBLOCK);

    if (atob_fd < 0 || btoa_fd < 0) {
        perror("Error opening files");
        return 1;
    }

    while (1) {
        // Write "Hello B" to AtoB.txt
        write(atob_fd, "Hello B\n", strlen("Hello B\n"));
        fsync(atob_fd);

        // Read "Hello A" from BtoA.txt
        bytes_read = read(btoa_fd, buffer, sizeof(buffer) - 1);
        if (bytes_read > 0) {
            buffer[bytes_read] = '\0';
            printf("%s", buffer); // Print the message from B
            ftruncate(btoa_fd, 0); // Clear the file content
        }

        sleep(1); // Add delay for alternation
    }

    close(atob_fd);
    close(btoa_fd);
    return 0;
}
