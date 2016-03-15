// 2016-03-07 Daniel Stenekap och Göran Forström

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

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

// Defines för Main
#define C_LIST_BUFFER 10

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

// Returns FALSE if: Nothing was read, Input out of range, Input cut off by fgets before EOL. 
// Return TRUE if a line was read including EOL, which is stripped from the target-array.

int readLine(char* ior_chArr, int i_sizeChArr)
{
    int index = 0;
    char bufferChArr[C_BUFFER_SIZE];
    void *fgetsReturnPtr;

    fgetsReturnPtr = fgets(bufferChArr, C_BUFFER_SIZE, stdin);

    if (fgetsReturnPtr == NULL)
    {
        return FALSE;
    }

    do
    {
        if (index >= i_sizeChArr || index >= C_BUFFER_SIZE)
        {
            ior_chArr[index - 1] = '\0';
            return FALSE;
        }

        if (bufferChArr[index] == '\0')
        {
            ior_chArr[index] = '\0';
            return FALSE;
        }

        // Vi har en korrekt, inläsning spara den.
        if (bufferChArr[index] == C_RADSLUT)
        {
            ior_chArr[index] = '\0';
            return TRUE;
        }

        ior_chArr[index] = bufferChArr[index];
        index++;

    } while (TRUE);

} //readLine

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
        numberOfArgumentsRecived = scanf_s("%f", &ior_item->isAmount); // Space after %f replaces flushRestOfLine
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

ItemStruct* addItemToList(ItemStruct* ior_itemList, int i_currItemCount)
{
    ItemStruct* ptr;
    ptr = (ItemStruct*)realloc(ior_itemList, sizeof(ItemStruct));
    inputItem(&ptr[i_currItemCount]);
    return ptr;
} //addItemToList


  // ============================================================================

void printList(ItemStruct* ior_itemList, int i_listLength)
{
    int i = 0;
    unsigned int maxNameLength = 0;
    unsigned int maxUnitLength = 0;
    char formatStr[100];

    printf_s("The items on the list are...\n");

    // Find length of longest text string...
    for (i = 0; i < i_listLength; i++)
    {
        if (strlen(ior_itemList[i].isName) > maxNameLength)
        {
            maxNameLength = strlen(ior_itemList[i].isName);
        }
        if (strlen(ior_itemList[i].isUnit) > maxUnitLength)
        {
            maxUnitLength = strlen(ior_itemList[i].isUnit);
        }
    }

    // Created adapted format string for the list
    // %.3g ger 3 signifikanta siffror men ger för vissa värden utskrift i grundpotensform
    sprintf_s(&formatStr[0], 100, "%%3d %%%ds %%6.3g %%%ds\n", maxNameLength, maxUnitLength);

    // Print list...
    for (i = 0; i < i_listLength; i++)
    {
        printf_s(formatStr, (ior_itemList + i)->isId, (ior_itemList + i)->isName, (ior_itemList + i)->isAmount, (ior_itemList + i)->isUnit);
    }

} // printList


  // ============================================================================

void printMeny()
{
    printf_s("1 - Add item to itemlist. \n");
    printf_s("2 - Load itemlist from file. \n");
    printf_s("3 - Print itemlist. \n");
    printf_s("4 - Save itemlist to file. \n");
    printf_s("5 - Edit item in itemlist. \n");
    printf_s("6 - Delete item in itemlist. \n");
    printf_s("7 - Exit Program. \n");

    printf_s("Enter selection: ");
}

// ============================================================================

ItemStruct* loadItemList()
{
    // Läser in en lista från en fil.
    ItemStruct* adress = NULL;
    //int errorFlag;

    //...

    return adress;
}

// ============================================================================

int saveItemList(ItemStruct* ir_itemList, int ir_listSize)
{
    // Sparar en itemList till en fil fil.
    int errorFlag = 1;

    //...

    return errorFlag;
}

// ============================================================================

void main(void)
{
    ItemStruct *itemList;
    int itemCount = 0;
    int selection;
    int errorFlag = TRUE;
    int continueFlag = TRUE;

    printf_s("Welcome to the shopping list!\n\n");

    itemList = (ItemStruct*)malloc(sizeof(ItemStruct));

    do
    {
        printMeny();
        selection = getc(stdin);

        switch (selection)
        {
        case 1:
        {
            // 1 - Add item to itemlist.
            itemList = addItemToList(itemList, itemCount);
            break;
        }
        case 2:
        {
            // 2 - Load itemlist from file
            itemList = loadItemList();
            break;
        }
        case 3:
        {
            // 3 - Print itemlist
            break;
        }
        case 4:
        {
            // 4 - Save itemlist to file.
            errorFlag = saveItemList(itemList, itemCount);
            break;
        }
        case 5:
        {
            // 5 - Edit item in itemlist. 
            break;
        }
        case 6:
        {
            // 6 - Delete item in itemlist.

            break;
        }
        case 7:
        {
            // 7 - Exit Program.
            continueFlag = FALSE;
            break;
        }
        default:
            printf_s("Please select a number between 1 and 7!\n\n");
            break;
        }
    } while (continueFlag);

    printf_s("Thank you for using the shopping list!\n\n");
} // Main