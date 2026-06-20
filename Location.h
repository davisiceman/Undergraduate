#ifndef LOCATION_H
#define LOCATION_H

#include "Inventory.h" // Including Inventory to track items in each location

#define MAX_LOC_NAME_STRING 25
#define MAX_LOC_DESCRIPTION_STRING 250
#define MAX_LOCATIONS 10

typedef struct {
    char name[MAX_LOC_NAME_STRING];                // Name of the location
    char description[MAX_LOC_DESCRIPTION_STRING];  // Description of the location
    int north;   // Index of the location to the north (-1 if none)
    int east;    // Index of the location to the east (-1 if none)
    int south;   // Index of the location to the south (-1 if none)
    int west;    // Index of the location to the west (-1 if none)
    Inventory items;  // Items in this location
} Location;

// Function declarations
int LocationReadMap(Location map[], int maxLocations, const char *filename);
void LocationAddItem(Location *pLocation, void *pItem);
void LocationRemoveItem(Location *pLocation, void *pItem);
bool LocationHasItem(Location *pLocation, void *pItem);

#endif // LOCATION_H
