#include <stdio.h>

#define C_SIZE_OF_TARGET_ARR 100



// Hämtat från windows 10 dosfönster (svenskt språk).
#define C_DOS_AA -113
#define C_DOS_AE -114
#define C_DOS_OE -103
#define C_DOS_aa -122
#define C_DOS_ae -124
#define C_DOS_oe -108

#define C_RADSLUT 10


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


void scanLine(char ro_chArr[], int i_maxSize)
{
    int wordIndex = 0;
    char ch; 

    while (1 == 1)
    {
        if (wordIndex < i_maxSize)
        {
            scanf_s("%c", &ch, 1);
            if (ch == C_RADSLUT)
            {
                ro_chArr[wordIndex] = '\0'; // Avsluta sträng
                break;
            }
            else
            {
                ro_chArr[wordIndex] = ch;
            }
            wordIndex++;
        }
        else
        {
            wordIndex--; // Sträng för lång, backa och sätt radslut
            ro_chArr[wordIndex] = '\0'; // Avsluta sträng
            break;
        }
    } 
} // scanLine

static int yesNoRepeater(char ir_prompt[])
{
    // Return 1 = yes , 0 = no

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


int isAlphabet(char i_ch)
{
    int resInt = 0;

    // printf_s("%c, %d, %X\n", i_ch, i_ch, i_ch);
    if ((i_ch >= 'A' && i_ch <= 'Z') ||
        (i_ch >= 'a' && i_ch <= 'z') ||
        (i_ch == C_DOS_AA) || (i_ch == C_DOS_AE) || (i_ch == C_DOS_OE) ||
        (i_ch == C_DOS_aa) || (i_ch == C_DOS_ae) || (i_ch == C_DOS_oe))
    {
        resInt = 1;
    }
    return resInt;
} // isAlphabet

void printFirstWord(char ir_chArr[])
{
    int wordStartIndex = -1;
    int wordEndIndex = -2; // Början på ordet ligger efter slutet på ordet om inget ord hittats för att hjälpa utskriften nedan
    int index = 0;

    // Hitta början på första ordet
    do
    {
        if (1 == isAlphabet(ir_chArr[index]))
        {
            wordStartIndex = index;
            break;
        }
        index++;
    } while (ir_chArr[index] != '\0');

    // Hitta Slutet på första ordet
    do
    {
        if (1 == isAlphabet(ir_chArr[index]) && wordStartIndex != -1)
        {
            wordEndIndex = index;
        }
        else
        {
            break;
        }
        index++;
    } while (ir_chArr[index] != '\0');

    for (int i = wordStartIndex; i <= wordEndIndex; i++)
    {
        printf_s("%c", ir_chArr[i]);
    }
    
} // printFirstWord


char* getWord(char ir_charArr[], int i_wordIndex)
{
    int index = 0;
    int count = 0;
    char *wordPtr;
    int insideWord = 0;
    do 
    {
        if (1 == isAlphabet(ir_charArr[index]))
        {
            if (0 != insideWord)
            {
                // Nytt ord Börjar
                adress = &ir_charArr[index];
            }
            else
            {
                // Vi är i ett ord
            }
        }
        else
        {
            if (1 == insideWord)
            {
                // Ordet Slutar
                count++;
            }
            else
            {
                // Vi är mellan ord

            }
        }
        index++;
    } while (count != i_wordIndex);

    return wordPtr;
} // getWord


void main(void)
{
    char chArr[C_SIZE_OF_TARGET_ARR];
    int wordIndex = -1;
    char *chArrPtr;

    printf_s("Welcome Word Finder!\n");
    do
    {

        printf_s("\nPlease enter a sentence: ");


        scanLine(chArr, C_SIZE_OF_TARGET_ARR);
        printf_s("chArr = \"%s\"\n", chArr);
        // printf_s("\nThe first word is: \n");
        // printFirstWord(chArr);
        // printf_s("\n");

        printf_s("Which word index do you want to print?");
        scanf_s("%d", &wordIndex);
        flushRestOfLine();

        chArrPtr = getWord(chArr, wordIndex);
        printf_s("The word at index %d is: \"", wordIndex);
        
        printFirstWord(chArrPtr);
        printf_s("\"\n");

    } while (1 == yesNoRepeater("Would you like to run the Word Finder again?"));
}