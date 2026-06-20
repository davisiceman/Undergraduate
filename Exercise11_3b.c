#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>

#define FIFO_A_TO_B "fifoAtoB"
#define FIFO_B_TO_A "fifoBtoA"

int main() {
    int fd_write, fd_read;
    char buffer[100];
    ssize_t bytes_read;

    // Create FIFOs if they don't already exist
    if (mkfifo(FIFO_A_TO_B, 0666) < 0 && errno != EEXIST) {
        perror("Error creating fifoAtoB");
        return 1;
    }
    if (mkfifo(FIFO_B_TO_A, 0666) < 0 && errno != EEXIST) {
        perror("Error creating fifoBtoA");
        return 1;
    }

    // Open FIFO for writing (fifoBtoA) in blocking mode temporarily
    fd_write = open(FIFO_B_TO_A, O_WRONLY);
    if (fd_write < 0) {
        perror("Error opening fifoBtoA for writing");
        return 1;
    }

    // Open FIFO for reading (fifoAtoB) in blocking mode temporarily
    fd_read = open(FIFO_A_TO_B, O_RDONLY);
    if (fd_read < 0) {
        perror("Error opening fifoAtoB for reading");
        close(fd_write);
        return 1;
    }

    // Switch to non-blocking behavior for communication
    fcntl(fd_write, F_SETFL, O_NONBLOCK);
    fcntl(fd_read, F_SETFL, O_NONBLOCK);

    while (1) {
        // Try reading "Hello B" from fifoAtoB
        bytes_read = read(fd_read, buffer, sizeof(buffer) - 1);
        if (bytes_read > 0) {
            buffer[bytes_read] = '\0';
            printf("%s", buffer); // Print the message from A

            // Write "Hello A" to fifoBtoA
            if (write(fd_write, "Hello A\n", strlen("Hello A\n")) == -1) {
                if (errno != EAGAIN) {
                    perror("Error writing to fifoBtoA");
                }
            }
        } else if (bytes_read == -1 && errno != EAGAIN) {
            perror("Error reading from fifoAtoB");
        }

        sleep(1); // Add a small delay for alternation
    }

    close(fd_write);
    close(fd_read);
    return 0;
}
