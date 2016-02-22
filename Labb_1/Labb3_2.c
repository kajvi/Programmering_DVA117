#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

// Daniel och Göran 20160211

#define C_DICE_COUNT 5
#define C_DICE_FACE_COUNT 6

// ============================================================================

void rollDice(int i_count, int or_diceArray[])
{
    int num;

    // Slumpar ett tal
    srand((unsigned int)time(0));
    for (int i = 0; i < i_count; i++)
    {
        num = rand() % 6 + 1;
        or_diceArray[i] = num;
    }

    return;

} // rollDice

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

int sumDice(int i_count, int ir_diceArray[])
{
    int sum = 0;

    for (int i = 0; i < i_count; i++)
    {
        sum = sum + ir_diceArray[i];
    }

    return sum;
} // sumDice

// ============================================================================

int countDice(int i_count, int ir_diceArray[], int i_target)
{
    int targetCount = 0;

    for (int i = 0; i < i_count; i++)
    {
        if (ir_diceArray[i] == i_target)
        {
            targetCount++;
        }
    }

    return targetCount;
} // countDice

// ============================================================================

void printNumAsText(int i_num)
{
    if (i_num == 1)
    {
        printf_s("One");
    }
    if (i_num == 2)
    {
        printf_s("Two");
    }
} // printNumAsText

// ============================================================================

void printDices(int i_count, int ir_diceArray[])
{
   char diceFace[6][3][3] = {        { {' ', ' ', ' '}, {' ', '*', ' '}, {' ', ' ', ' '} }, /* Ett */               { {'*', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', '*'} }, /* Två */        { {'*', ' ', ' '}, {' ', '*', ' '}, {' ', ' ', '*'} }, /* Tre */        { {'*', ' ', '*'}, {' ', ' ', ' '}, {'*', ' ', '*'} }, /* Fyra */        { {'*', ' ', '*'}, {' ', '*', ' '}, {'*', ' ', '*'} }, /* Fem */        { {'*', ' ', '*'}, {'*', ' ', '*'}, {'*', ' ', '*'} } /* Sex */                            };
   for (int i = 0; i < i_count; i++)
   {
        int face = ir_diceArray[i] - 1;
        for (int row = 0; row < 3; row++)
        {
            printf_s("  ");
            for (int col = 0; col < 3; col++)
            {
                printf_s("%c ", diceFace[face][row][col]);
            }
            printf_s("\n");
        }
        printf_s("\n"); 
        printf_s("\n");
        Sleep(500);
    }

} // printDices

// ============================================================================

int main32(void)
{
    int diceArray[C_DICE_COUNT];
    int sum = 0;
    char repeatChar;
    int diceFaceCountArray[C_DICE_FACE_COUNT]; // using index 0 means face = 1.


    printf_s("Welcome to the Yatzy Game!\n\n");
    do
    {

        // Initierar Arrayen med slumptal
        rollDice(C_DICE_COUNT, diceArray);

        // Skriver ut arrayen.
        printDices(C_DICE_COUNT, diceArray);

        // Summerar tärningarna
        sum = sumDice(C_DICE_COUNT, diceArray);

        // Utskrivt
        printf_s("Summa: (");
        for (int i = 0; i < C_DICE_COUNT; i++)
        {
            printf_s("%d", diceArray[i]);
            if (i != C_DICE_COUNT - 1)
            {
                printf_s("+");
            }
        }
        printf_s(") : %d\n", sum);


        for (int i = 0; i < C_DICE_FACE_COUNT; i++)
        {
            diceFaceCountArray[i] = countDice(C_DICE_COUNT, diceArray, i + 1);
        }


        {
            int pairCount = 0;
            int trissCount = 0;

            for (int i = 0; i < C_DICE_FACE_COUNT; i++)
            {
                if (diceFaceCountArray[i] == 2)
                {
                    pairCount++;
                }
                if (diceFaceCountArray[i] == 3)
                {
                    trissCount++;
                }
            }

            if (pairCount > 0)
            {
                printNumAsText(pairCount);
                printf_s(" Pair(s)\n");
            }
            if (trissCount > 0)
            {
                printNumAsText(trissCount);
                printf_s(" Triss\n");
            }
        }


        do
        {
            // Loopar tills man väljer att avsluta eller börja om.

            printf_s("Would you like roll again? (y/n): ");
            scanf_s("%c", &repeatChar, 1);

            // Tömmer resten av In-strömmen från tangentbordet fram till radslut.
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



    printf_s("\nThank you for playing the Yatzy Game!\n\n");
    return 0;

} // main

// ============================================================================

