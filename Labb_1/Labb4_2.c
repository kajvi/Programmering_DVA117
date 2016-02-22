#include <stdio.h>

// 2016-02-18 Daniel Stenekap och Göran Forström


#define C_SIZE_OF_TARGET_ARR 100

// ============================================================================

static void flushRestOfLine(void)
{
    // Call ONLY when EOL expected from the keyboardstream.

    char ch;
    do
    {
        scanf_s("%c", &ch, 1);
        //printf_s("\n%d\n", ch);
    } while (ch != 10);

}// flushRestOfLine

// ============================================================================

static int yesNoRepeater(char ir_prompt[])
{
   // Print prompt, wait for "y" or "n" to be entered and return 1 = yes , 0 = no

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
        else if (repeatChar == 'n' || repeatChar == 'Y')
        {
            return 0;
        }
        else
        {
            printf_s("Please enter either y (yes) or n (no)\n");
        }
    } while (1 == 1);
} // yesNoRepeater

// ============================================================================

void freqAnalyser(int ior_targetArr[], int i_count, int *ro_value, int *ro_frequency)
{
    // Please note that the ior_targetArr will be overwritten.
    // Value = -1 means that the input array had no positive integers

    int currCount = 0;
    int currValue = 0;
    int tempIndex = 0;
	int index; // Adapted for VS2010

    *ro_value = -1;
    *ro_frequency = 0;

    for (index = 0; index < i_count; index++)
    {
        if (-1 != ior_targetArr[index])
        {
            // nytt värde, räkna förekomst härifrån och frammåt.
            currValue = ior_targetArr[index];
            currCount = 0;
            tempIndex = index;
            do
            {
                if (currValue == ior_targetArr[tempIndex])
                {
                    currCount++;
                    ior_targetArr[tempIndex] = -1; // Markera att den räknats
                }
                tempIndex++;
                
            } while (tempIndex < i_count);

            // check if currCount exceedes ro_frequency
            if (currCount > *ro_frequency)
            {
                *ro_frequency = currCount;
                *ro_value = currValue;
            }
        }
    }
} // freqAnalyser

// ============================================================================

void main4_2(void)
{
    int targetArr[C_SIZE_OF_TARGET_ARR];
    int nextFreeTargetArrIndex = 0;
    int endFlag = 0;
    int value;
    int frequency;

    printf_s("Welcome to Frequency Analyser!\n");

    do
    {

        nextFreeTargetArrIndex = 0;
        endFlag = 0;

        printf_s("\nPlease enter integers between [0:1000]. You may enter upp to 100 integers.\n");
        printf_s("To finish inputting integers enter a negative value.\n");

        // Läser in tal
        do
        {
            int temp;

            printf_s("Enter a number: ");
            scanf_s("%d", &temp);
            flushRestOfLine();

            if (0 <= temp)
            {
                targetArr[nextFreeTargetArrIndex] = temp;
                nextFreeTargetArrIndex++;
            }
            else
            {
                endFlag = 1;
            }

        } while (0 == endFlag);

        freqAnalyser(targetArr, nextFreeTargetArrIndex, &value, &frequency);
        if (value >= 0)
        {
            printf_s("The number %d is the first of the integers that has the highest frequency: %d occurrencies\n", value, frequency);
        }
        else
        {
            printf_s("No integers found!\n");
        }
        

    } while (1 == yesNoRepeater("Would you like to run the Frequency Analyser again?"));

    printf_s("\nThank you for using Frequency Analyser\n\n");

} // main

// ============================================================================

