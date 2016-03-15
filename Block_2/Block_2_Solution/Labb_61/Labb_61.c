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

// Dynamisk Minneshantering
ItemStruct* addItemToListinHeap(ItemStruct* ior_itemList, int* ior_currItemCount)
{
    ItemStruct* ptr;
    ptr = (ItemStruct*)realloc(ior_itemList, sizeof(ItemStruct));
    ptr[*ior_currItemCount].isId = *ior_currItemCount + 1;
    inputItem(&ptr[*ior_currItemCount]);
    (*ior_currItemCount)++;
    return ptr;
} //addItemToListinHeap


  // ============================================================================

void printList(ItemStruct* ior_itemList, int i_listLength)
{
    int i = 0;
    unsigned int maxNameLength = 0;
    unsigned int maxUnitLength = 0;
    char formatStr[100];

    if (i_listLength == 0)
    {
        printf_s("The list is empty!\n");
    }
    else
    {
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
    }
} // printList


  // ============================================================================

void printMeny()
{
    printf_s("\n");
    printf_s("1 - Add item to itemlist. \n");
    printf_s("2 - Print itemlist. \n");
    printf_s("3 - Exit Program. \n");

    printf_s("Enter selection: ");
}

// ============================================================================


void main(void)
{
    ItemStruct *itemList;
    int itemCount = 0;
    char selection;
    int errorFlag = TRUE;
    int continueFlag = TRUE;

    printf_s("Welcome to the shopping list!\n");

    itemList = (ItemStruct*)malloc(sizeof(ItemStruct));

    do
    {
        printMeny();
        selection = _getch();
        printf_s("%c\n\n", selection);

        switch (selection)
        {
        case '1':
        {
            // 1 - Add item to itemlist.
            itemList = addItemToListinHeap(itemList, &itemCount);
            break;
        }
        case '2':
        {
            // 2 - Print itemlist
            printList(itemList, itemCount);
            break;
        }
        case '3':
        {
            // 3 - Exit Program.
            continueFlag = FALSE;
            break;
        }
        default:
            printf_s("*** Please select a number between 1 and 3! ***\n");
            break;
        }
    } while (continueFlag);

    printf_s("Thank you for using the shopping list!\n\n");

    free(itemList);
} // Main