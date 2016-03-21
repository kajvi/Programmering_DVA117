// 2016-03-20 Daniel Stenekap och Göran Forström

#ifndef ITEM_LIST_FUNKTIONS_H
#define ITEM_LIST_FUNKTIONS_H

// Defines för itemStruct
#define C_ITEM_NAME_LENGTH 30
#define C_UNIT_NAME_LENGTH 30

// Defines för Listan
#define C_LIMIT 0

#define C_MAGIC_NUMBER 0x11223344
struct fileHeader
{
	int sf_magicNumber;
	int sf_recordCount;
};
typedef struct fileHeader FileHeader;

struct itemStruct
{
    char isName[C_ITEM_NAME_LENGTH];
    float isAmount;
    char isUnit[C_UNIT_NAME_LENGTH];
    int isId;
};
typedef struct itemStruct ItemStruct;

void inputItem(ItemStruct* ior_item, int i_editFlag);
ItemStruct* addItemToListinHeap(ItemStruct* ior_itemList, int* ior_currslotCount);
void printList(ItemStruct* ior_itemList, int i_listLength);
int countListItems(ItemStruct* ir_itemList, int i_slotCount);
int searchItemId(ItemStruct* ir_itemList, int i_slotCount, int i_itemId);
ItemStruct* loadItemList(char* ir_fileName, int* or_listSize);
int saveItemList(char* ir_fileName, ItemStruct* ir_itemList, int i_listSize);

#endif // ITEM_LIST_FUNKTIONS_H