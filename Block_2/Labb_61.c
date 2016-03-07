// 2016-03-07 Daniel Stenekap och Göran Forström

#include <stdio.h>
#include <stdlib.h>

#define TRUE -1
#define FALSE 0


// Defines för flushRestOfLine
#define C_RADSLUT 10

// Defines för itemStruct
#define C_ITEM_NAME_LENGTH 30
#define C_UNIT_NAME_LENGTH 30
#define C_LIST_LENGTH 3

// Defines for readLine
#define C_BUFFER_SIZE 80

struct itemStruct
{
    char isName[C_ITEM_NAME_LENGTH];
    float isAmount;
    char isUnit[C_UNIT_NAME_LENGTH];
    int isId;
};
typedef struct itemStruct ItemStruct;

// ============================================================================



void inputItem(ItemStruct* ior_item)
{
    int numberOfArgumentsRecived;
    int okFlag;

    do
    {
        printf_s("Name of item %d: ", (*ior_item).isId);
        okFlag = readLine(ior_item->isName, sizeof(ior_item->isName));

        if (ior_item->isName[0] == '\0')
        {
            printf_s("Name cannot be empty!\n");
            okFlag = FALSE;
        }
        else if (okFlag == FALSE)
        {
            // Inmatningen är för lång.
            printf_s("WARNING! The entered Name has been truncated!\n");
            okFlag = TRUE;
        }
        // scanf_s("%s", &ior_item->isName[0], sizeof(ior_item->isName)); // Bryter vid mellanslag
        // flushRestOfLine();
    } while (!okFlag);

    do
    {
        printf_s("Number of this item: ");
        numberOfArgumentsRecived = scanf_s("%f", &ior_item->isAmount, sizeof(ior_item->isAmount));
        flushRestOfLine();

        if (numberOfArgumentsRecived == 1)
        {
            break;
        }
        else
        {
            printf_s("*** Please enter a number! ***\n");
        }
    } while (TRUE);

    printf_s("Enter the Unit: ");
    okFlag = readLine(ior_item->isUnit, sizeof(ior_item->isUnit));

    // scanf_s("%s", &ior_item->isUnit[0], C_UNIT_NAME_LENGTH);
    // flushRestOfLine();
} // inputItem


  // ============================================================================

ItemStruct* addItemToList(ItemStruct* ior_itemList, int i_currItemCount, int i_newItemCount)
{
    ItemStruct* ptr;
    ptr = (ItemStruct*)realloc(ior_itemList, sizeof(ItemStruct)*i_newItemCount);
    inputItem(&ptr[i_currItemCount]);
    return ptr;
}

void printMeny()
{
    printf_s("1 - Add item to itemlist. \n");
    printf_s("2 - Print itemlist. \n");
    printf_s("3 - Exit Program. \n");
    
    printf_s("Enter selection: ");

}

void labb_61(void)
{
    printf_s("Welcome to the shopping list!\n\n");
    
    printMeny();
    
}