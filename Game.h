#ifndef GAME_H
#define GAME_H

#include "Location.h"
#include "Item.h"
#include "Player.h"

#define MAX_MAP_LOCATIONS 10
#define MAX_ITEM_COUNT 100

typedef struct {
    int numLocations;                  // Number of locations in the game
    Location map[MAX_MAP_LOCATIONS];   // Array of locations
    int itemCount;                     // Number of items in the game
    Item items[MAX_ITEM_COUNT];        // Array of items
    Player player;                     // Player in the game
} Game;

// Function declarations
int GameInitialize(Game *pGame);

#endif // GAME_H
