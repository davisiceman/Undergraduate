#include "Player.h"
#include <stdbool.h>

// Initializes the Player by setting their initial location and emptying their inventory
void PlayerInit(Player *pPlayer, int locationNumber) {
    pPlayer->location = locationNumber;
    InventoryInit(&pPlayer->items);  // Initialize an empty inventory for the player
}

// Adds an item to the player's inventory
void PlayerAddItem(Player *pPlayer, void *pItem) {
    InventoryAdd(&pPlayer->items, pItem);  // Add item to player's inventory
}

// Removes an item from the player's inventory
void PlayerRemoveItem(Player *pPlayer, void *pItem) {
    InventoryRemove(&pPlayer->items, pItem);  // Remove item from player's inventory
}

// Checks if the player has a specific item in their inventory
bool PlayerHasItem(Player *pPlayer, void *pItem) {
    return InventoryFind(&pPlayer->items, pItem);  // Return true if the player has the item
}
