#ifndef INVENTORY_H
#define INVENTORY_H

#include <stdbool.h>

#define MAX_OBJECTS 16

// Inventory structure that holds a list of generic objects
typedef struct {
    void *objects[MAX_OBJECTS]; // Array of pointers to objects
    int count;                  // Number of items in the list
} Inventory;

// Initializes the inventory as an empty list
void InventoryInit(Inventory *pInventory);

// Adds an object to the inventory and returns the current count
int InventoryAdd(Inventory *pInventory, void *pObject);

// Removes an object from the inventory and returns the current count
int InventoryRemove(Inventory *pInventory, void *pObject);

// Checks if the object exists in the inventory and returns true/false
bool InventoryFind(Inventory *pInventory, void *pObject);

#endif // INVENTORY_H
