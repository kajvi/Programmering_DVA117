// 2016-03-20 Daniel Stenekap och G�ran Forstr�m

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#include <windows.h>

#include "Generic.h"
#include "itemListFunktions.h"

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
    // ior_currslotCount ger os antalet m�jliga f�rem�l som finns i listan just nu.
    // Anropet till realloc beh�ver ett f�rem�l extra: d�rav ior_currslotCount + 1
    // N�r realloc framg�ngsrikt returnerat en pekare till det nya minnet r�knas ior_currslotCount upp.
    // Annars returneras en Nullpekare.
    ItemStruct* ptr;
    int index;

    // Unders�ker om det finns lediga slots, om ja: �teranv�nd. 
    // Unik ID refererar till plats i listan. �r inte knutet till f�rem�let.
    for (index = 0; index < *ior_currslotCount; index++)
    {
        if (ior_itemList[index].isId == 0)
        {
            ior_itemList[index].isId = index + 1;
            inputItem(&ior_itemList[index], FALSE);
            return ior_itemList;
        }
    }

    // Skapa en ny slott i listan och flytta den i heapen om det beh�vs.
    ptr = (ItemStruct*)realloc(ior_itemList, sizeof(ItemStruct)*(*ior_currslotCount + 1));
    if (ptr != NULL)
    {
        // Om allokering framg�ngsrik: flytta till ledig possition och l�gg till f�rem�l.
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
                continue; // Invers till Break forts�tt till n�sta index i for-loopen (p� den n�rmaste �vre niv�n).
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
        // %.3g ger 3 signifikanta siffror men ger f�r vissa v�rden utskrift i grundpotensform
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



  // Returnerar antalet f�rem�l i listan.
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

  // returnerar -1 om det inte finns n�got f�rem�l p� den platsen.
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

  // Returnerar NULL om det g�tt �t pipan.
ItemStruct* loadItemList(char* ir_fileName, int* or_listSize)
{
    ItemStruct* itemListPtr = NULL;
    FILE* fp = NULL;
    FileHeader fHeader;
    int readRecordCount;
    int errorFlag;

    // Om vi inte lyckas l�sa fileHeader initieras denna till 0.
    *or_listSize = 0;

    errorFlag = fopen_s(&fp, ir_fileName, "rb");
    if (fp == NULL || errorFlag != 0)
    {
        return NULL;
    }

    // L�s File Header till listSize;
    readRecordCount = fread(&fHeader, sizeof(FileHeader), 1, fp); // Inneh�llet i i_listSize skrivs till file.
    if (readRecordCount != 1)
    {
        return NULL;
    }

    *or_listSize = fHeader.sf_recordCount;
    itemListPtr = malloc(sizeof(ItemStruct) * (*or_listSize));
    if (itemListPtr == NULL)
    {
        *or_listSize = 0; // Vi har inte f�tt minne till alla poster vi ville l�sa.
        free(itemListPtr);
        itemListPtr = NULL;
        systemAbort("\n*** Out of Memory at loadItemList! Program aborts! ***\n");
    }

    // L�s listan till Minnet
    readRecordCount = fread(itemListPtr, sizeof(ItemStruct), *or_listSize, fp); // Inneh�llet i i_listSize skrivs till file.
    if (readRecordCount != fHeader.sf_recordCount)
    {
        *or_listSize = 0; // Vi kunde inte l�sa in alla poster vi f�rv�ntade oss.
        free(itemListPtr);
        itemListPtr = NULL;
        return NULL;
    }


    errorFlag = fclose(fp); // returnerar 0 om allt g�tt bra.
    if (errorFlag != 0)
    {
        *or_listSize = 0; // Vi kunde inte st�nga filen, vi litar inte p� resultatet
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
    writenRecordCount = fwrite(&fHeader, sizeof(FileHeader), 1, fp); // Inneh�llet i i_listSize skrivs till file.
    if (writenRecordCount != 1)
    {
        return FALSE;
    }

    // Skriv in Hela listan till filen
    writenRecordCount = fwrite(ir_itemList, sizeof(ItemStruct), fHeader.sf_recordCount, fp); // Inneh�llet i i_listSize skrivs till file.
    if (writenRecordCount != fHeader.sf_recordCount)
    {
        return FALSE;
    }


    errorFlag = fclose(fp); // returnerar 0 om allt g�tt bra.
    if (errorFlag != 0)
    {
        return FALSE;
    }

    return TRUE;
} // saveItemList