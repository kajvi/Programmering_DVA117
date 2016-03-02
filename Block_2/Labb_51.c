// 2016-03-02 Daniel Stenekap och Göran Forström

#include <stdio.h>
#include <stdlib.h>

#define TRUE -1
#define FALSE 0


// Defines för flushRestOfLine
#define C_RADSLUT 10

// Defines för itemStruct
#define C_ITEM_NAME_LENGTH 30
#define C_UNIT_NAME_LENGTH 30
#define C_LIST_LENGTH 5

struct itemStruct
{
    char isName[C_ITEM_NAME_LENGTH];
    float isAmount;
    char isUnit[C_UNIT_NAME_LENGTH];
    int isId;
};
typedef struct itemStruct ItemStruct;


// ============================================================================

static void flushRestOfLine(void)
{
    // Call ONLY when EOL expected from the keyboardstream.

    char ch;
    do
    {
        scanf_s("%c", &ch, 1);
        //printf_s("\n%d\n", ch);
    } while (ch != C_RADSLUT);
}// flushRestOfLine

// ============================================================================

void inputItem(ItemStruct* ior_item)
{
    int numberOfArgumentsRecived;

    printf_s("Name of item %d: ", (*ior_item).isId);
    scanf_s("%s", &ior_item->isName[0], sizeof(ior_item->isName));
    flushRestOfLine();

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
    } while (1);

    printf_s("Enter the Unit: ");
    scanf_s("%s", &ior_item->isUnit[0], C_UNIT_NAME_LENGTH);
    flushRestOfLine();
} // inputItem


// ============================================================================


void printList(ItemStruct* ior_item, int listLength)
{
    int i = 0;

    printf_s("The items on the list are...\n");

    for (i = 0; i < C_LIST_LENGTH; i++)
    {
        printf_s("Name: %s\t Amount: %f\t Unit %s\t Unik Id: %d\n", (ior_item + i)->isName, (ior_item + i)->isAmount, (ior_item + i)->isUnit, (ior_item + i)->isId);
    }

} // printList


// ============================================================================


void labb_51(void)
{
    ItemStruct itemList[C_LIST_LENGTH];
    int i = 0;

    printf_s("Welcome to the shopping list!\n\n");
    printf_s("You may now enter your items!\n");

    // Setter unikt id till vilket nummer den har på listan
    for (i = 0; i < C_LIST_LENGTH; i++)
    {
        itemList[i].isId = i + 1;
        inputItem(&itemList[i]);
        printf_s("\n");
    }


    printList(itemList, C_LIST_LENGTH);


} // labb_51
