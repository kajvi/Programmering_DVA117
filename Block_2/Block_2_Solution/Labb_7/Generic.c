// 2016-03-20 Daniel Stenekap och Göran Forström

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#include <windows.h>

#include "Generic.h"

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
