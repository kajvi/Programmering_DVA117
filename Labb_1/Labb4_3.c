#include <stdio.h>

#define C_SIZE_OF_TARGET_ARR 100



// H�mtat fr�n windows 10 dosf�nster (svenskt spr�k).
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
                ro_chArr[wordIndex] = '\0'; // Avsluta str�ng
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
            wordIndex--; // Str�ng f�r l�ng, backa och s�tt radslut
            ro_chArr[wordIndex] = '\0'; // Avsluta str�ng
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
        // Loopar tills man v�ljer y eller n.

        printf_s("%s (y/n): ", ir_prompt);
        scanf_s("%c", &repeatChar, 1);

        // T�mmer resten av In-str�mmen fr�n tangentbordet fram till radslut.
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
    int wordEndIndex = -2; // B�rjan p� ordet ligger efter slutet p� ordet om inget ord hittats f�r att hj�lpa utskriften nedan
    int index = 0;

    if (NULL != ir_chArr)
    {
        // Hitta b�rjan p� f�rsta ordet
        while (ir_chArr[index] != '\0')
        {
            if (1 == isAlphabet(ir_chArr[index]))
            {
                wordStartIndex = index; // Vi har hittat f�rsta bokstaven. Spara adressen.
                break;
            }
            index++;
        }

        // Om vi hittat starten p� ett ord - hitta slutet
        if (wordStartIndex != -1)
        {
            do
            {
                if (1 == isAlphabet(ir_chArr[index]))
                {
                    wordEndIndex = index;
                }
                else
                {
                    break;
                }

                index++;
            } while (ir_chArr[index] != '\0');

            // Skriv ut ordet
            for (int i = wordStartIndex; i <= wordEndIndex; i++)
            {
                printf_s("%c", ir_chArr[i]);
            }
        }
    }
    if (-1 == wordStartIndex)
    {
        printf_s("There is no word at the requested index.");
    }
    
} // printFirstWord


char* getWord(char ir_charArr[], int i_wordIndex)
{
    // Returnerar pekare till det ord som ligger p� wordIndex.
    // Om wordIndex �r st�rre �n tillg�ngligt antal ord returneras pekare till '\0'

    int index = 0;
    int count = 0;
    char *wordPtr = NULL;
    int insideWord = 0;
    
    do 
    {
        if (1 == isAlphabet(ir_charArr[index]))
        {
            if (0 == insideWord)
            {
                // Nytt ord B�rjar
                if (count == i_wordIndex)
                {
                    wordPtr = &ir_charArr[index];
                    break; // Vi har satt pekarens v�rde: bryt
                }
                insideWord = 1;
            }
            else
            {
                // Vi �r i ett ord
                insideWord = 1;
            }
        }
        else
        {
            if (1 == insideWord)
            {
                // Ordet Slutar
                count++;
                insideWord = 0;
            }
            else
            {
                // Vi �r mellan ord
                insideWord = 0;
            }
        }
        index++;
    } while (ir_charArr[index] != '\0');

    return wordPtr;
} // getWord


void main(void)
{
    char chArr[C_SIZE_OF_TARGET_ARR];
    int wordIndex = -1;
    char *chArrPtr;
    char* temp;

    //temp = getWord("Hej p� dej", 1);
    //temp = getWord("en str�ng", 0);
    //temp = getWord("ett ord", 2);

    printf_s("Welcome Word Finder!\n");
    do
    {

        printf_s("\nPlease enter a sentence: ");

        scanLine(chArr, C_SIZE_OF_TARGET_ARR);
        printf_s("chArr = \"%s\"\n", chArr);
        // printf_s("\nThe first word is: \n");
        // printFirstWord(chArr);
        // printf_s("\n");

        printf_s("Which word index do you want to print? ");
        scanf_s("%d", &wordIndex);
        flushRestOfLine();

        chArrPtr = getWord(chArr, wordIndex);
        if (NULL != chArrPtr)
        {
            printf_s("The word at index %d is: \"", wordIndex);
            printFirstWord(chArrPtr);
            printf_s("\"\n");
        }
        else
        {
            printFirstWord(chArrPtr);
            printf_s("\n");
        }
        


    } while (1 == yesNoRepeater("Would you like to run the Word Finder again?"));
}