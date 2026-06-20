#include <stdio.h>
#include <errno.h>

int main() {
    FILE* file;

    // Try to open a non-existent file
    file = fopen("non_existent_file.txt", "r");

    // Check if the file pointer is NULL
    if (!file) {
        // Print the error
        perror("Error opening file");
    }

    return 0;
}
