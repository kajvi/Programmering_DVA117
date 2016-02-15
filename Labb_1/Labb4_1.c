// Daniel Stenekap och Göran Forström

#include <stdio.h>

#define C_SIZE_OF_PRIME_SIEVE 102
#define C_SIZE_OF_TARGET_ARR 100


void flushRestOfLine(void);

int yesNoRepeater()
{
    // Return 1 = yes (continue with program), 0 = no (close program)

    char repeatChar;
    do
    {
        // Loopar tills man väljer att avsluta eller börja om.

        printf_s("Would you like to runagain? (y/n): ");
        scanf_s("%c", &repeatChar, 1);

        // Tömmer resten av In-strömmen från tangentbordet fram till radslut.
        flushRestOfLine();

        if (repeatChar == 'y')
        {
            return 1;
        }
        else if (repeatChar == 'n')
        {
            return 0;
        }
        else
        {
            printf_s("Please enter either y (yes) or n (no)\n");
        }
    } while (1 == 1);
} // yesNoRepeater


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


void primeSieve(int ir_primeSieveArr[], int i_maxSieveSize)
{
    int counter = 0;
    for (int index = 0; index < i_maxSieveSize; index++)
    {
        ir_primeSieveArr[index] = counter;
        counter++;
    }

    counter = 0;
    for (int index = 2; index < i_maxSieveSize; index++)
    {
        int currPrime = ir_primeSieveArr[index];
        
        if (currPrime != -1)
        {
            for (int index2 = currPrime * 2; index2 < i_maxSieveSize; index2 = index2 + currPrime)
            {
                ir_primeSieveArr[index2] = -1;
            }
        }
    }
} // primeSieve

int keepPrimes(int ir_primeSieveArr[], int i_maxSieveSize, int ir_targetArr[], int i_targetSize)
{
    int targetIndex = 0;
    int count = 0;
    FORTSÄTT HÄR

    return 0;
}

void main(void)
{
    int primeSieveArr[C_SIZE_OF_PRIME_SIEVE];
    int targetArr[C_SIZE_OF_TARGET_ARR];
    int targetCount;
    
    printf_s("Welcome to PrimeChecker!\n\n");

    primeSieve(primeSieveArr, C_SIZE_OF_PRIME_SIEVE);
    do
    {
        printf_s("\nEnter the number of Integers to check: ");
        scanf_s("%d", &targetCount);
        flushRestOfLine();

        printf_s("Enter %d Integers: \n", targetCount);
        
        for (int i = 0; i < targetCount; i++)
        {
            printf_s("Enter a number: ");
            scanf_s("%d", &targetArr[i]);
            flushRestOfLine();
        }

        printf_s("You entered the following: [ ");

        for (int i = 0; i < targetCount; i++)
        {
            printf_s("%d ", targetArr[i]);
        }
        printf_s("]\n");



    } while (1 == yesNoRepeater());



    printf_s("Thank you for using PrimeChecker!\n\n");
    return 0;

    for (int i = 0; i < C_SIZE_OF_PRIME_SIEVE; i++)
    {
        if (-1 != primeSieveArr[i])
        {
            printf_s("%d  %d\n", i, primeSieveArr[i]);
        }
    }
}