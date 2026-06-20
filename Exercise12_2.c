#include <stdio.h>
#include <time.h>

int main() {
    time_t current_time;
    struct tm* gm_time;
    char* time_string;

    // Get the current time
    current_time = time(NULL);

    // Convert to GMT
    gm_time = gmtime(&current_time);

    // Convert GMT to string
    time_string = asctime(gm_time);

    // Print the current time
    printf("Current date and time in GMT: %s", time_string);

    return 0;
}
