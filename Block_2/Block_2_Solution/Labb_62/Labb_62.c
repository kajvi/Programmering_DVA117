// 2016-03-07 Daniel Stenekap och Göran Forström

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
#define C_LIST_LENGTH 3

// Defines for readLine
#define C_BUFFER_SIZE 80

// Defines för Main
#define C_LIST_BUFFER 10
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
    Sleep(2000);
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



void inputFilename(char* ior_fileName, int i_maxLength)
{
    int okFlag = FALSE;
    char* tempInputPtr;
    tempInputPtr = malloc(sizeof(char) * i_maxLength);
    if (tempInputPtr == NULL)
    {
        systemAbort("Out of memory");
    }

    printf_s("Hit Enter to use Current File Name: (\"%s\") ", ior_fileName, i_maxLength);
    printf_s("or input New File Name!\n)");
    printf_s("Enter File Name = %s = ", ior_fileName, i_maxLength);

    do
    {
        okFlag = readLine(ior_fileName, i_maxLength);


    } while (!okFlag);
    
}


// ============================================================================

void inputItem(ItemStruct* ior_item)
{
    int numberOfArgumentsRecived;
    int okFlag;

    do
    {
        //TODO (Extra): Blanka alla ch_arr innan vi skriver till dem!!
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
    // ior_currItemCount ger os antalet föremål som finns i listan just nu.
    // Anropet till realloc behöver ett föremål extra: därav ior_currItemCount + 1
    // När realloc framgångsrikt returnerat en pekare till det nya minnet räknas ior_currItemCount upp.
    // Annars returneras en Nullpekare.
    ItemStruct* ptr;
    ptr = (ItemStruct*)realloc(ior_itemList, sizeof(ItemStruct)*(*ior_currItemCount + 1));
    if (ptr != NULL)
    {
        ptr[*ior_currItemCount].isId = *ior_currItemCount + 1;
        inputItem(&ptr[*ior_currItemCount]);
        (*ior_currItemCount)++;
    }
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
    printf_s("2 - Load itemlist from file. \n");
    printf_s("3 - Print itemlist. \n");
    printf_s("4 - Save itemlist to file. \n");
    printf_s("5 - Edit item in itemlist. \n");
    printf_s("6 - Delete item in itemlist. \n");
    printf_s("7 - Exit Program. \n");

    printf_s("Enter selection: ");
} // printMeny



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
        return NULL;
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
    int itemCount = 0;
    char selection;
    int errorFlag = TRUE;
    int continueFlag = TRUE;
    char fileName[C_FILE_NAME_LENGTH] = "test.bin";

    printf_s("Welcome to the shopping list!\n");

    itemList = (ItemStruct*)malloc(sizeof(ItemStruct));

    do
    {
        if (itemList == NULL)
        {
            printf_s("\n");
            printf_s("*** Out of Memory! Program abort! ***\n");
            Sleep(1000);
            return 1;
        }
        printMeny();
        selection = _getch();
        printf_s("%c\n\n", selection);
        Sleep(400);


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
            // 2 - Load itemlist from file
            // Vi ska ladda en lista, kasta bort den gamla
            // TODO: Fråga om operatorn vill kasta den gamla listan: om inte återgå till menyn.
            free(itemList);
            itemList = loadItemList("test.bin", &itemCount);
            break;
        }
        case '3':
        {
            // 3 - Print itemlist
            printList(itemList, itemCount);
            break;
        }
        case '4':
        {
            // 4 - Save itemlist to file.
            errorFlag = saveItemList("test.bin", itemList, itemCount);
            break;
        }
        case '5':
        {
            // 5 - Edit item in itemlist. 
            // TODO:
            break;
        }
        case '6':
        {
            // 6 - Delete item in itemlist.
            // TODO:
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