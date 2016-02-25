#include <stdio.h>

// 2016-02-18 Daniel Stenekap och Göran Forström


#define C_SIZE_OF_PRIME_SIEVE 1001
#define C_SIZE_OF_TARGET_ARR 100


void flushRestOfLine(void);

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

void primeSieve(int ir_primeSieveArr[], int i_maxSieveSize)
{
    // Skapar ett primtalssåll (Eratosthenes algorithm) med primtal upp till C_SIZE_OF_PRIME_SIEVE

	int index; // Adapted for VS2010

    // indexerar arrayen till C_SIZE_OF_PRIME_SIEVE
    for (index = 0; index < i_maxSieveSize; index++)
    {
        ir_primeSieveArr[index] = index;
    }

    // Sätter alla icke primtal till -1 enligt Eratosthenes algorithm
    for (index = 2; index < i_maxSieveSize; index++)
    {
        int currPrime = ir_primeSieveArr[index];

        if (currPrime != -1)
        {
			int index2; // Adapted for VS2010
            for (index2 = currPrime * 2; index2 < i_maxSieveSize; index2 = index2 + currPrime)
            {
                ir_primeSieveArr[index2] = -1;
            }
        }
    }

    // 0 och -1 är inte primtal
    ir_primeSieveArr[0] = -1;
    ir_primeSieveArr[1] = -1;
} // primeSieve

// ============================================================================

int keepPrimes(int ir_primeSieveArr[], int i_maxSieveSize, unsigned long long  ir_targetArr[], int i_targetSize)
{
    // Räknar antalet primtal i ir_targetArr samt sätter ickeprimtal i arrayen till -1

    int targetIndex = 0;
    int count = 0;
    do
    {

        if (ir_targetArr[targetIndex] > i_maxSieveSize)
        {
            // Brute Force metod Dividerar med alla tal upp till target (vi kunde ha tagit roten ur först)
			unsigned long long testInt; // Adapted for VS2010
            for (testInt = 2; testInt < ir_targetArr[targetIndex]; testInt++)
            {
                if ((ir_targetArr[targetIndex] % testInt) == 0)
                {
                    ir_targetArr[targetIndex] = -1;
                    break;
                }
            }
            if (ir_targetArr[targetIndex] != -1)
            {
                count++;
            }
        }
        else
        {
            // Använder primtalssållet genom slå upp index i sållet.
            if (-1 != ir_primeSieveArr[ir_targetArr[targetIndex]])
            {
                count++;
            }
            else
            {
                ir_targetArr[targetIndex] = -1;
            }
        }

        targetIndex++;

    } while (targetIndex < i_targetSize);

    return count;
} // keepPrimes

// ============================================================================

void main41(void)
{
    int primeSieveArr[C_SIZE_OF_PRIME_SIEVE];
    unsigned long long targetArr[C_SIZE_OF_TARGET_ARR];
    int targetCount;
    int numberOfPrimes;
	int i; // Adapied for VS2010

    //unsigned long long test;
    //printf_s("%d %d\n", sizeof(targetCount), sizeof(test));

    printf_s("Welcome to PrimeChecker!\n\n");

    // Skapar primtalssållet
    primeSieve(primeSieveArr, C_SIZE_OF_PRIME_SIEVE);
    do
    {
        do
        {
            printf_s("\nEnter the number of Integers to check: ");
            scanf_s("%d", &targetCount);
            flushRestOfLine();

            // Kollar att användaren inte matat in primtalet för tidigt
            if (10 <= targetCount)
            {
                printf_s("\nDo you realy want to check %d numbers?\n", targetCount);
            }
            else
            {
                break;
            }
        } while (1 == yesNoRepeater("Reenter the number of integers to check?"));

        // Läser in tal
        printf_s("Enter %d Integers: \n", targetCount);
        for (i = 0; i < targetCount; i++)
        {
            printf_s("Enter a number: ");
            scanf_s("%llu", &targetArr[i]);
            flushRestOfLine();
        }

        // Skriver ut talen
        printf_s("You entered the following: [ ");
        for (i = 0; i < targetCount; i++)
        {
            printf_s("%llu ", targetArr[i]);
        }
        printf_s("]\n");

        // Anropar keepPrimes algorithmen
        numberOfPrimes = keepPrimes(primeSieveArr, C_SIZE_OF_PRIME_SIEVE, targetArr, targetCount);

        // Skriver ut antalet primtal och vilka av talen som är primtal
        printf_s("You entered %d Prime(s) as follows: [ ", numberOfPrimes);
        for (i = 0; i < targetCount; i++)
        {
            if (-1 != targetArr[i])
            {
                printf_s("%llu ", targetArr[i]);
            }
        }
        printf_s("]\n");

    } while (1 == yesNoRepeater("Would you like to run the Primechecker again?"));


    printf_s("\nThank you for using PrimeChecker!\n\n");

} // main
