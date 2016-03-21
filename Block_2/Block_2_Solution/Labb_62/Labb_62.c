// 2016-03-07 Daniel Stenekap och Göran Forström

// TODO: (EXTRA) handle input int/float with letter following number.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#ifndef TRUE
#define TRUE -1
#define FALSE 0
#endif // !TRUE

#include <windows.h>

// Defines för flushRestOfLine
#define C_RADSLUT 10

// Defines för itemStruct
#define C_ITEM_NAME_LENGTH 30
#define C_UNIT_NAME_LENGTH 30

// Defines for readLine
#define C_BUFFER_SIZE 80

// Defines för Listan
#define C_LIMIT 0
#define C_FILE_NAME_LENGTH 80

struct fileHeader
{
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

// ============================================================================

void systemAbort(char* ir_message)
{
    printf_s("\n\n ***** %s ****** \n\n", ir_message);
    Sleep(5000);
    exit(EXIT_FAILURE);
} // systemAbort


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

// Print prompt: wait for "y" or "n" to be entered and return 1 = yes , 0 = no
int yesNoRepeater(char ir_prompt[])
{
    char repeatChar;
    do
    {
        // Loopar tills man väljer y eller n.

        printf_s("%s (y/n): ", ir_prompt);
        scanf_s("%c", &repeatChar, 1);

        // Tömmer resten av In-strömmen från tangentbordet fram till radslut.
        flushRestOfLine();

        if (repeatChar == 'y' || repeatChar == 'Y')
        {
            return 1;
        }
        else if (repeatChar == 'n' || repeatChar == 'N')
        {
            return 0;
        }
        else
        {
            printf_s("Please enter either y (yes) or n (no)\n");
        }
    } while (TRUE);
} // yesNoRepeater


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

// Se till att användaren matar in korrekt värde större än limit, returnera detta!
int inputIntGreaterThanLimit(char * ir_PromptChArr, int i_limit)
{
    int resInt;
    int numberOfArgumentsRecived;
    int errorFlag;

    do
    {
        printf_s(ir_PromptChArr);
        numberOfArgumentsRecived = scanf_s("%d", &resInt);
        flushRestOfLine();

        errorFlag = TRUE;

        if (numberOfArgumentsRecived == 1)
        {
            if (resInt <= i_limit)
            {
                printf_s("Please enter an integer value above %d !\n\n", i_limit);
            }
            else
            {
                errorFlag = FALSE;
            }
        }
    } while (errorFlag == TRUE);

    return resInt;

} // inputIntGreaterThanLimit

// ============================================================================

// Get input as string, use current string as default if edit mode!

void inputStrWithDefault(char * ir_promptStr, char * ior_Str, int i_maxLen, int i_editFlag)
{
    int okFlag;
    char* tempInputPtr;

    tempInputPtr = malloc(sizeof(char) * i_maxLen);
    if (tempInputPtr == NULL)
    {
        systemAbort("Out of memory in inputStrWithDefault");
    }

    do
    {
        printf_s(ir_promptStr);
        if (i_editFlag)
        {
            // Print old value as default
            printf_s("%s = ", ior_Str);
        }

        okFlag = readLine(tempInputPtr, i_maxLen);

        // Check if empty string as input
        if (tempInputPtr[0] == '\0')
        {
            if (i_editFlag)
            {
                // No Entry - means keep old name...
                okFlag = TRUE;
                break;
            }
            printf_s("Input cannot be empty!\n");
            okFlag = FALSE;
        }
        else if (okFlag == FALSE)
        {
            // Inmatningen är för lång.
            printf_s("WARNING! The entered input has been truncated!\n");
            okFlag = TRUE;
        }

        if (okFlag)
        {
            // Use the new input!
            strcpy_s(ior_Str, i_maxLen, tempInputPtr);
        }
    } while (!okFlag);

    free(tempInputPtr);
    tempInputPtr = NULL;

} // inputStrWithDefault


  // ============================================================================


  // Get input as string, use current string as default if edit mode!

void inputFloatWithDefault(char * ir_promptStr, float * ior_Float, int i_editFlag)
{
	int sizeOfTmpFloatStr = 16;
    char* tmpFloatAsStr;
	char tmpCh;
    int numberOfArgumentsRecived;
    float tempFloat;

    tmpFloatAsStr = malloc(sizeof(char) * sizeOfTmpFloatStr); // Plats för 16 tecken i floaten
    if (tmpFloatAsStr == NULL)
    {
        systemAbort("Out of memory in inputFloatWithDefault");
    }

    do
    {
        if (i_editFlag)
        {
            sprintf_s(tmpFloatAsStr, sizeof(tmpFloatAsStr), "%g", *ior_Float);
        }
        inputStrWithDefault(ir_promptStr, tmpFloatAsStr, sizeOfTmpFloatStr, i_editFlag);

        if (tmpFloatAsStr[0] == 0)
        {
            // Empty input, no change - Use default value...
        }
        else
        {
            // Some input, check value...
            numberOfArgumentsRecived = sscanf_s(tmpFloatAsStr, "%f%c", &tempFloat, &tmpCh);
            if (numberOfArgumentsRecived == 1)
            {
                // Use the entered value...
                *ior_Float = tempFloat;
                break;
            }
            else
            {
                printf_s("*** Please enter a number! ***\n");
            }
        }
    } while (TRUE);

} // inputFloatWithDefault


// ============================================================================

void inputFilename(char* ior_fileName, int i_maxLength)
{

    printf_s("Hit Enter to use Current File Name: (\"%s\") ", ior_fileName);
    printf_s("or input New File Name!\n");

    inputStrWithDefault("File Name: ", ior_fileName, i_maxLength, TRUE);
} // inputFilename

// ============================================================================

// Input data for an item, param. i_DoEdit = TRUE means prompt with default (used at Edit Item)
void inputItem(ItemStruct* ior_item, int i_editFlag)
{
    char promptName[20] = "Name:     ";
    char promptAmount[20] = "Amount:   ";
    char promptUnit[20] = "Unit:     ";

    //TODO (EXTRA): Blanka alla ch_arr innan vi skriver till dem!!

    printf_s("Update item %d: \n", (*ior_item).isId);
    inputStrWithDefault(promptName, ior_item->isName, sizeof(ior_item->isName), i_editFlag);

    inputFloatWithDefault(promptAmount, &ior_item->isAmount, i_editFlag);

    inputStrWithDefault(promptUnit, ior_item->isUnit, sizeof(ior_item->isUnit), i_editFlag);

} // inputItem



// ============================================================================


// Dynamisk Minneshantering
ItemStruct* addItemToListinHeap(ItemStruct* ior_itemList, int* ior_currslotCount)
{
    // ior_currslotCount ger os antalet möjliga föremål som finns i listan just nu.
    // Anropet till realloc behöver ett föremål extra: därav ior_currslotCount + 1
    // När realloc framgångsrikt returnerat en pekare till det nya minnet räknas ior_currslotCount upp.
    // Annars returneras en Nullpekare.
    ItemStruct* ptr;
    int index;

    // Undersöker om det finns lediga slots, om ja: återanvänd. 
    // Unik ID refererar till plats i listan. Är inte knutet till föremålet.
    for (index = 0; index < *ior_currslotCount; index++)
    {
        if (ior_itemList[index].isId == 0)
        {
            ior_itemList[index].isId = index + 1;
            inputItem(&ior_itemList[index], FALSE);
            return ior_itemList;
        }
    }

    // Skapa en ny slott i listan och flytta den i heapen om det behövs.
    ptr = (ItemStruct*)realloc(ior_itemList, sizeof(ItemStruct)*(*ior_currslotCount + 1));
    if (ptr != NULL)
    {
        // Om allokering framgångsrik: flytta till ledig possition och lägg till föremål.
        ptr[*ior_currslotCount].isId = *ior_currslotCount + 1;
        inputItem(&ptr[*ior_currslotCount], FALSE);
        (*ior_currslotCount)++; // Uppdaterar antal slots i listan.
    }

    // Returnera en pekare till listans start.
    return ptr;
} // addItemToListinHeap


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
            if (ior_itemList[i].isId == 0)
            {
                continue; // Invers till Break fortsätt till nästa index i for-loopen (på den närmaste övre nivån).
            }
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
        sprintf_s(&formatStr[0], 100, "%%3d %%-%ds %%6.3g %%-%ds\n", maxNameLength, maxUnitLength);

        // Print list...
        for (i = 0; i < i_listLength; i++)
        {
            if (ior_itemList[i].isId == 0)
            {
                continue;
            }
            printf_s(formatStr, (ior_itemList + i)->isId, (ior_itemList + i)->isName, (ior_itemList + i)->isAmount, (ior_itemList + i)->isUnit);
        }
    }
} // printList



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


// Returnerar antalet föremål i listan.
int countListItems(ItemStruct* ir_itemList, int i_slotCount)
{
    int i = 0;
    int itemCount = 0;

    for (i = 0; i < i_slotCount; i++)
    {
        if (ir_itemList[i].isId != 0)
        {
            itemCount++;
        }
    }
    return itemCount;
} // countListItems



// ============================================================================

// returnerar -1 om det inte finns något föremål på den platsen.
// Returnerar index om allt bra.
int searchItemId(ItemStruct* ir_itemList, int i_slotCount, int i_itemId)
{

    if (i_itemId > i_slotCount)
    {
        return -1;
    }
    if (i_itemId != ir_itemList[i_itemId - 1].isId)
    {
        return -1;
    }
    return i_itemId - 1;
} // searchItemId


// ============================================================================

// Returnerar NULL om det gått åt pipan.
ItemStruct* loadItemList(char* ir_fileName, int* or_listSize)
{
    ItemStruct* itemListPtr = NULL;
    FILE* fp = NULL;
    FileHeader fHeader;
    int readRecordCount;
    int errorFlag;

    // Om vi inte lyckas läsa fileHeader initieras denna till 0.
    *or_listSize = 0;

    errorFlag = fopen_s(&fp, ir_fileName, "rb");
    if (fp == NULL || errorFlag != 0)
    {
        return NULL;
    }

    // Läs File Header till listSize;
    readRecordCount = fread(&fHeader, sizeof(FileHeader), 1, fp); // Innehållet i i_listSize skrivs till file.
    if (readRecordCount != 1)
    {
        return NULL;
    }

    *or_listSize = fHeader.sf_recordCount;
    itemListPtr = malloc(sizeof(ItemStruct) * (*or_listSize));
    if (itemListPtr == NULL)
    {
        *or_listSize = 0; // Vi har inte fått minne till alla poster vi ville läsa.
        free(itemListPtr);
        itemListPtr = NULL;
        systemAbort("\n*** Out of Memory at loadItemList! Program aborts! ***\n");
    }

    // Läs listan till Minnet
    readRecordCount = fread(itemListPtr, sizeof(ItemStruct), *or_listSize, fp); // Innehållet i i_listSize skrivs till file.
    if (readRecordCount != fHeader.sf_recordCount)
    {
        *or_listSize = 0; // Vi kunde inte läsa in alla poster vi förväntade oss.
        free(itemListPtr);
        itemListPtr = NULL;
        return NULL;
    }


    errorFlag = fclose(fp); // returnerar 0 om allt gått bra.
    if (errorFlag != 0)
    {
        *or_listSize = 0; // Vi kunde inte stänga filen, vi litar inte på resultatet
        free(itemListPtr);
        itemListPtr = NULL;
        return NULL;
    }

    return itemListPtr;
} // loadItemList



// ============================================================================

// Returnerar TRUE om allt gick bra, annars returnerar den FALSE
int saveItemList(char* ir_fileName, ItemStruct* ir_itemList, int i_listSize)
{
    FILE* fp = NULL;
    FileHeader fHeader;
    int writenRecordCount;
    int errorFlag;

    errorFlag = fopen_s(&fp, ir_fileName, "wb");
    // fp = fopen(ir_fileName, "wb");
    if (fp == NULL || errorFlag != 0)
    {
        return FALSE;
    }

    // Uppdatera File Header till listSize;
    fHeader.sf_recordCount = i_listSize;
    writenRecordCount = fwrite(&fHeader, sizeof(FileHeader), 1, fp); // Innehållet i i_listSize skrivs till file.
    if (writenRecordCount != 1)
    {
        return FALSE;
    }

    // Skriv in Hela listan till filen
    writenRecordCount = fwrite(ir_itemList, sizeof(ItemStruct), fHeader.sf_recordCount, fp); // Innehållet i i_listSize skrivs till file.
    if (writenRecordCount != fHeader.sf_recordCount)
    {
        return FALSE;
    }


    errorFlag = fclose(fp); // returnerar 0 om allt gått bra.
    if (errorFlag != 0)
    {
        return FALSE;
    }

    return TRUE;
} // saveItemList



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

    printf_s("Welcome to the shopping list 6.2!\n");

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

