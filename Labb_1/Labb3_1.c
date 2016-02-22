#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Daniel och G�ran 20160211

#define C_ARRAY_COUNT 10

// ============================================================================

void fillArray(int i_count, int or_numArray[])
{
    int num;

    // Slumpar ett tal
    srand((unsigned int)time(0));
    for (int i = 0; i < i_count; i++)
    {
        num = rand() % 10 + 1;
        or_numArray[i] = num;
    }

    return;

} // fillArray

// ============================================================================

void flushRestOfLine(void)
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

int searchArray(int i_count, int ir_numArray[], int i_target)
{
    int targetCount = 0;

    for (int i = 0; i < i_count; i++)
    {
        if (ir_numArray[i] == i_target)
        {
            targetCount++;
        }
    }

    return targetCount;
} // searchArray

// ============================================================================

int main31(void)
{
    int numArray[C_ARRAY_COUNT];
    int target = -1;
    char repeatChar;
    int targetCount = -1;

    printf_s("Welcome to the Number Finder!\n\n");
    do
    {
        // Initierar Arrayen med slumptal
        fillArray(C_ARRAY_COUNT, numArray);

        // Skriver ut arrayen.
        for (int i = 0; i < C_ARRAY_COUNT; i++)
        {
            printf_s("Number: %d\n", numArray[i]);
        }

        printf_s("\nChoose the number to search for : ");
        scanf_s("%d", &target);
        
        // T�mmer resten av In-str�mmen fr�n tangentbordet fram till radslut.
        flushRestOfLine();

        // Anropar J�mf�relse algoritmen
        targetCount = searchArray(C_ARRAY_COUNT, numArray, target);
        printf_s("The target number %d exists %d time(s) in the array!\n\n", target, targetCount);

        do
        {
            // Loopar tills man v�ljer att avsluta eller b�rja om.

            printf_s("Would you like to search a new sequence? (y/n): ");
            scanf_s("%c", &repeatChar, 1);

            // T�mmer resten av In-str�mmen fr�n tangentbordet fram till radslut.
            flushRestOfLine();

            if (repeatChar == 'y' || repeatChar == 'n')
            {
                break;
            }
            else
            {
                printf_s("Please enter either y (yes) or n (no)\n");
            }
        } while (1 == 1);
    } while (repeatChar == 'y');


    printf_s("\nThank you for using the Number Finder!\n\n");
    return 0;

} // main

// ============================================================================

