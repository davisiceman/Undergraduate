#include <stdio.h>
#include "Game.h"
#include "Location.h"
#include "Item.h"
#include "Player.h"

// Initializes the game by loading the map, items, and player setup
int GameInitialize(Game *pGame) {
    // Load map
    pGame->numLocations = LocationReadMap(pGame->map, MAX_MAP_LOCATIONS, "map.txt");
    if (pGame->numLocations == -1) {
        printf("Error loading map.\n");
        return -1;
    }

    // Load items
    pGame->itemCount = ItemLoadFromFile(pGame->items, MAX_ITEM_COUNT, "items.txt");
    if (pGame->itemCount == -1) {
        printf("Error loading items.\n");
        return -1;
    }

    // Initialize the player at the first location (location index 0)
    PlayerInit(&pGame->player, 0);

    return 0; // Return success
}
