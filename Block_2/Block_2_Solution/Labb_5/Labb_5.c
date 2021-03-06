// 2016-03-02 Daniel Stenekap och G�ran Forstr�m

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE -1
#define FALSE 0


// Defines f�r flushRestOfLine
#define C_RADSLUT 10

// Defines f�r itemStruct
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

        // Vi har en korrekt, inl�sning spara den.
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
            // Inmatningen �r f�r l�ng.
            printf_s("WARNING! The entered Name has been truncated!\n");
            okFlag = TRUE;
        }
        // scanf_s("%s", &ior_item->isName[0], sizeof(ior_item->isName)); // Bryter vid mellanslag
        // flushRestOfLine();
    } while (!okFlag);

    do
    {
        printf_s("Number of this item: ");
        numberOfArgumentsRecived = scanf_s("%f", &ior_item->isAmount);
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

void printList(ItemStruct* ior_item, int listLength)
{
    int i = 0;
    unsigned int maxNameLength = 0;
    unsigned int maxUnitLength = 0;
    char formatStr[100];

    printf_s("The items on the list are...\n");

    // Find length of longest text string...
    for (i = 0; i < C_LIST_LENGTH; i++)
    {
        if (strlen(ior_item[i].isName) > maxNameLength)
        {
            maxNameLength = strlen(ior_item[i].isName);
        }
        if (strlen(ior_item[i].isUnit) > maxUnitLength)
        {
            maxUnitLength = strlen(ior_item[i].isUnit);
        }
    }

    // Created adapted format string for the list
    // %.3g ger 3 signifikanta siffror men ger f�r vissa v�rden utskrift i grundpotensform
    sprintf_s(&formatStr[0], 100, "%%3d %%%ds %%6.3g %%%ds\n", maxNameLength, maxUnitLength);

    // Print list...
    for (i = 0; i < C_LIST_LENGTH; i++)
    {
        printf_s(formatStr, (ior_item + i)->isId, (ior_item + i)->isName, (ior_item + i)->isAmount, (ior_item + i)->isUnit);
    }

} // printList


  // ============================================================================


void main(void)
{
    ItemStruct itemList[C_LIST_LENGTH];
    int i = 0;

    printf_s("Welcome to the shopping list 5.0!\n\n");
    printf_s("You may now enter your items!\n");

    // S�tter unikt id till vilket nummer den har p� listan
    for (i = 0; i < C_LIST_LENGTH; i++)
    {
        itemList[i].isId = i + 1;
        inputItem(&itemList[i]);
        printf_s("\n");
    }


    printList(itemList, C_LIST_LENGTH);


} // labb_51
