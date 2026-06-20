#include <stdio.h>
#include <time.h>

int main() {
    struct tm moon_landing = {0};
    time_t moon_time;
    char* time_string;

    // Set the date for the first moon landing
    moon_landing.tm_year = 1969 - 1900;  // Year since 1900
    moon_landing.tm_mon = 6;             // July (0-based index)
    moon_landing.tm_mday = 20;           // Day of the month
    moon_landing.tm_hour = 0;
    moon_landing.tm_min = 0;
    moon_landing.tm_sec = 0;

    // Convert to time_t
    moon_time = mktime(&moon_landing);

    // Convert to string
    time_string = ctime(&moon_time);

    // Print the date
    printf("The first moon landing was: %s", time_string);

    return 0;
}
