#ifndef ITEM_H
#define ITEM_H

#define MAX_ITEM_NAME_STRING 25
#define MAX_ITEM_DESCRIPTION_STRING 80

#define ITEM_USE_NONE 0
#define ITEM_USE_TELEPORT 1

typedef struct {
    char itemName[MAX_ITEM_NAME_STRING];
    char itemDescription[MAX_ITEM_DESCRIPTION_STRING];
    int itemUse;
} Item;

int ItemLoadFromFile(Item items[], int maxItems, const char *filename);
Item *ItemFindByName(Item items[], int maxItems, const char *itemName);
int ItemShow(void *pItem, int displayAll);

#endif // ITEM_H
