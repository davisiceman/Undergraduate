#ifndef PLAYER_H
#define PLAYER_H

#include "Inventory.h"

typedef struct {
    int location;      // The current location of the player (index in the map)
    Inventory items;   // The player's inventory to store collected items
} Player;

// Initializes the Player at a specified location
void PlayerInit(Player *pPlayer, int locationNumber);

// Adds an item to the player's inventory
void PlayerAddItem(Player *pPlayer, void *pItem);

// Removes an item from the player's inventory
void PlayerRemoveItem(Player *pPlayer, void *pItem);

// Checks if the player has a specific item
bool PlayerHasItem(Player *pPlayer, void *pItem);

#endif // PLAYER_H
