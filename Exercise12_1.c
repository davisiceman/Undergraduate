#include <stdio.h>
#include <time.h>

int main() {
    time_t current_time;
    char* time_string;

    // Get the current time
    current_time = time(NULL);

    // Convert to local time string
    time_string = ctime(&current_time);

    // Print the current time
    printf("Current date and time: %s", time_string);

    return 0;
}
