// 2016-03-07 Daniel Stenekap och Göran Forström

// TODO: (EXTRA) handle input int/float with letter following number.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#include <windows.h>

#include "Generic.h"
#include "itemListFunktions.h"

// Define för Main
#define C_FILE_NAME_LENGTH 80

// ============================================================================

void printMeny()
{
    printf_s("\n");
    printf_s("1 - Add item to itemlist. \n");
    printf_s("2 - Load itemlist from file. \n");
    printf_s("3 - Print itemlist. \n");
    printf_s("4 - Save itemlist to file. \n");
    printf_s("5 - Edit item in itemlist. \n");
    printf_s("6 - Delete item in itemlist. \n");
    printf_s("7 - Exit Program. \n");

    printf_s("Enter selection: ");
} // printMeny


// ============================================================================

void inputFilename(char* ior_fileName, int i_maxLength)
{

    printf_s("Hit Enter to use Current File Name: (\"%s\") ", ior_fileName);
    printf_s("or input New File Name!\n");

    inputStrWithDefault("File Name: ", ior_fileName, i_maxLength, TRUE);
} // inputFilename


// ============================================================================

int main(void)
{
    ItemStruct *itemList = NULL;
    int slotCount = 0;
    char selection;
    int errorFlag = TRUE;
    int okFlag;
    int continueFlag = TRUE;
    char fileName[C_FILE_NAME_LENGTH] = "test.bin";

    printf_s("Welcome to the shopping list 7.0!\n");

    itemList = (ItemStruct*)malloc(sizeof(ItemStruct));

    do
    {

        printMeny();
        selection = _getch();
        printf_s("%c\n\n", selection);
        Sleep(400);

        switch (selection)
        {
        case '1':
        {
            // 1 - Add item to itemlist.
            itemList = addItemToListinHeap(itemList, &slotCount);
            if (itemList == NULL)
            {
                systemAbort("\n*** Out of Memory in main! Program aborts! ***\n");
            }
            break;
        }
        case '2':
        {
            // 2 - Load itemlist from file
            // Vi ska ladda en lista, kasta bort den gamla
            int continueFlag;
            int itemCount;

            itemCount = countListItems(itemList, slotCount);

            if (itemCount > 0)
            {
                continueFlag = yesNoRepeater("You have unsaved values in ur list. Do you want to delete them?");

                if (!continueFlag)
                {
                    printf_s("Load aborted! No change in current list.\n\n");
                    break;
                }
            }

            free(itemList);
            inputFilename(fileName, sizeof(fileName));
            itemList = loadItemList(fileName, &slotCount);
            if (itemList == NULL)
            {
                printf("ERROR: File Read of \"%s\" failed!\n\n", fileName);
            }
            else
            {
                printf("File Read of \"%s\" OK.\n", fileName);
            }

            break;
        }
        case '3':
        {
            // 3 - Print itemlist
            printList(itemList, slotCount);
            break;
        }
        case '4':
        {
            // 4 - Save itemlist to file.
            inputFilename(fileName, sizeof(fileName));
            okFlag = saveItemList(fileName, itemList, slotCount);
            if (!okFlag)
            {
                printf("ERROR: File Save to \"%s\" failed!\n\n", fileName);
            }
            else
            {
                printf("File Save to \"%s\" OK.\n", fileName);
            }
            break;
        }
        case '5':
        {
            // 5 - Edit item in itemlist. 
            int itemId, index;

            itemId = inputIntGreaterThanLimit("Enter the item ID that you want to edit: ", C_LIMIT);

            // Leta upp Item ID i listan, om ej hittat returneras -1;
            index = searchItemId(itemList, slotCount, itemId);
            if (index < 0)
            {
                printf_s("*** Item not Found. No item to be edited! ***\n\n");
            }
            else
            {
                // As input of new item but with prompt of current contents
                printf_s("Hit Enter to use Current Value or input New Value! \n");
                inputItem(&itemList[index], TRUE);
            }
            break;
        }
        case '6':
        {
            // 6 - Delete item in itemlist.

            int itemId, index;

            itemId = inputIntGreaterThanLimit("Enter the item ID that you want to remove: ", C_LIMIT);

            // Leta upp Item ID i listan, om ej hittat returneras -1;
            index = searchItemId(itemList, slotCount, itemId);
            if (index < 0)
            {
                printf_s("*** Index not Found. No item Removed! ***\n\n");
            }
            else
            {
                // TODO (EXTRA): Gör en print på item och be om bekräftelse!

                // Vi blankar item ID för att markera ledig slot
                itemList[index].isId = 0;
                printf_s("You have now removed item-Id: %d\n", itemId);

            }
            break;
        }
        case '7':
        {
            // 7 - Exit Program.
            continueFlag = FALSE;
            break;
        }
        default:
            printf_s("*** Please select a number between 1 and 7! ***\n");
            break;
        }
    } while (continueFlag);

    printf_s("Thank you for using the shopping list!\n\n");

    free(itemList);
    itemList = NULL;
    return 0;
} // Main

  // ============================================================================

