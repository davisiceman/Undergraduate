#include "Inventory.h"
#include <stdio.h>
#include <string.h>

// Initializes the inventory by setting the count to zero
void InventoryInit(Inventory *pInventory) {
    pInventory->count = 0;
}

// Adds an object to the inventory and returns the updated count
int InventoryAdd(Inventory *pInventory, void *pObject) {
    if (pInventory->count < MAX_OBJECTS) {
        pInventory->objects[pInventory->count] = pObject;
        pInventory->count++;
    }
    return pInventory->count;
}

// Removes an object from the inventory and returns the updated count
int InventoryRemove(Inventory *pInventory, void *pObject) {
    for (int i = 0; i < pInventory->count; i++) {
        if (pInventory->objects[i] == pObject) {
            // Shift remaining items left to fill the gap
            for (int j = i; j < pInventory->count - 1; j++) {
                pInventory->objects[j] = pInventory->objects[j + 1];
            }
            pInventory->count--;
            break;
        }
    }
    return pInventory->count;
}

// Returns true if the object is found in the inventory, otherwise false
bool InventoryFind(Inventory *pInventory, void *pObject) {
    for (int i = 0; i < pInventory->count; i++) {
        if (pInventory->objects[i] == pObject) {
            return true;
        }
    }
    return false;
}
