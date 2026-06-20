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
    atob_fd = open(ATOB, O_RDONLY | O_NONBLOCK);
    btoa_fd = open(BTOA, O_WRONLY | O_CREAT | O_TRUNC | O_NONBLOCK, 0666);

    if (atob_fd < 0 || btoa_fd < 0) {
        perror("Error opening files");
        return 1;
    }

    while (1) {
        // Read "Hello B" from AtoB.txt
        bytes_read = read(atob_fd, buffer, sizeof(buffer) - 1);
        if (bytes_read > 0) {
            buffer[bytes_read] = '\0';
            printf("%s", buffer); // Print the message from A
            ftruncate(atob_fd, 0); // Clear the file content

            // Write "Hello A" to BtoA.txt
            write(btoa_fd, "Hello A\n", strlen("Hello A\n"));
            fsync(btoa_fd);
        }

        sleep(1); // Add delay for alternation
    }

    close(atob_fd);
    close(btoa_fd);
    return 0;
}
