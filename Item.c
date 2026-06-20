#include <stdio.h>
#include <string.h>
#include "Item.h"

int ItemLoadFromFile(Item items[], int maxItems, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        return -1;
    }

    int itemCount = 0;
    while (itemCount < maxItems && fscanf(file, " \"%[^\"]\" \"%[^\"]\" %d",
                                          items[itemCount].itemName,
                                          items[itemCount].itemDescription,
                                          &items[itemCount].itemUse) == 3) {
        itemCount++;
    }

    fclose(file);
    return itemCount;
}

Item *ItemFindByName(Item items[], int maxItems, const char *itemName) {
    for (int i = 0; i < maxItems; i++) {
        if (strcmp(items[i].itemName, itemName) == 0) {
            return &items[i];
        }
    }
    return NULL;
}

int ItemShow(void *pItem, int displayAll) {
    Item *item = (Item *)pItem;
    if (displayAll) {
        printf("Item: %s\nDescription: %s\n", item->itemName, item->itemDescription);
    } else {
        printf("Item: %s\n", item->itemName);
    }
    return 0;
}
