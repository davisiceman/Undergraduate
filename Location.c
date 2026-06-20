#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Location.h"

// Reads the map from the specified file and populates the map array
// Returns the number of locations loaded, or -1 if there was an error
int LocationReadMap(Location map[], int maxLocations, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        return -1;
    }

    int locationCount = 0;
    while (locationCount < maxLocations) {
        if (fscanf(file, " %d, %d, %d, %d, \"%[^\"]\", \"%[^\"]\"",
                   &map[locationCount].north,
                   &map[locationCount].east,
                   &map[locationCount].south,
                   &map[locationCount].west,
                   map[locationCount].name,
                   map[locationCount].description) == 6) {
            InventoryInit(&map[locationCount].items);
            locationCount++;
        } else {
            break; // Stop if the reading fails
        }
    }

    fclose(file);
    return locationCount;
}

// Adds an item to the location's inventory
void LocationAddItem(Location *pLocation, void *pItem) {
    InventoryAdd(&pLocation->items, pItem);
}

// Removes an item from the location's inventory
void LocationRemoveItem(Location *pLocation, void *pItem) {
    InventoryRemove(&pLocation->items, pItem);
}

// Checks if an item exists in the location's inventory
bool LocationHasItem(Location *pLocation, void *pItem) {
    return InventoryFind(&pLocation->items, pItem);
}
