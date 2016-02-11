#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
// Daniel och Göran 20160211

#define C_SENTENCE_COUNT 100

// Hämtat från windows 10 dosfönster (svenskt språk).
#define C_DOS_AA -113
#define C_DOS_AE -114
#define C_DOS_OE -103
#define C_DOS_aa -122
#define C_DOS_ae -124
#define C_DOS_oe -108

// ---------------------------------------------------------------------------- 
int isLetter(char i_ch)
{
    int resInt = 0;

    printf_s("%c, %d, %X\n", i_ch, i_ch, i_ch);
    if ((i_ch >= 'A' && i_ch <= 'Z') ||
        (i_ch >= 'a' && i_ch <= 'z') ||
        (i_ch == C_DOS_AA) || (i_ch == C_DOS_AE) || (i_ch == C_DOS_OE) ||
        (i_ch == C_DOS_aa) || (i_ch == C_DOS_ae) || (i_ch == C_DOS_oe))
    {
        resInt = 1;
    }
    return resInt;
} // isLetter

char makeUppercase(char i_ch)
{
    char resChar = '?';

    resChar = i_ch;

    if (i_ch >= 'a' && i_ch <= 'z')
    {
        resChar = i_ch - ('a' - 'A');
    }
    if (i_ch == C_DOS_aa)
    {
        resChar = C_DOS_AA;
    }
    if (i_ch == C_DOS_ae)
    {
        resChar = C_DOS_AE;
    }
    if (i_ch == C_DOS_oe)
    {
        resChar = C_DOS_OE;
    }

    return resChar;
} // makeUppercase

int isPalindrome(char* ir_SentenceChArr)
{
    char workSentenceChArr[C_SENTENCE_COUNT];
    int resInt = 0;
    int index, wIndex = 0;
    int forwardIndex = 0;
    int backwardIndex = -1;

    // Steg ett: filtrera till bara bokstäver
    index = 0;
    while (ir_SentenceChArr[index] != '\0')
    {
        if (1 == isLetter(ir_SentenceChArr[index]))
        {
            workSentenceChArr[wIndex] = makeUppercase(ir_SentenceChArr[index]);
            wIndex++;
        }
        index++;
    }

    if (0 == wIndex)
    {
        return resInt;
    }

    // Steg 2: Kolla om texten är ett palindrom.
    resInt = 1;
    
    backwardIndex = wIndex - 1;
    while (forwardIndex < backwardIndex)
    {
        if (workSentenceChArr[forwardIndex] != workSentenceChArr[backwardIndex])
        {
            resInt = 0;
            break;
        }
        forwardIndex++;
        backwardIndex--;
    }

    return resInt;
} // isPalindrome

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



int main33(void)
{
    char sentenceChArr[C_SENTENCE_COUNT];
    char repeatChar;
    char ch;
    int index = -1;
    int result = -1;
    
    printf_s("Welcome to the Palindrome Checker!\n\n");
    do
    {
     
        printf_s("Enter your sentence: ");
        index = 0;
        do
        {
            scanf_s("%c", &ch, 1);
            if (ch == 10)
            {
                sentenceChArr[index] = '\0';
                break;
            }
            else
            {
                sentenceChArr[index] = ch;
                index++;
            }
        } while (1 == 1);

        result = isPalindrome(sentenceChArr);
        if (1 == result)
        {
            printf_s("The sentence is a Palindrome!\n");
        }
        else
        {
            printf_s("The sentence is NOT a Palindrome!\n");
        }

        do
        {
            // Loopar tills man väljer att avsluta eller börja om.

            printf_s("Would you like to test and other sentence? (y/n): ");
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



    printf_s("Thank you for using PalindromTester!\n\n");
    return 0;
}