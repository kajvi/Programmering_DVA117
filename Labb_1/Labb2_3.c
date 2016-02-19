#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// Daniel och Göran 20160204

// ---------------------------------------------------------------------------- 

int comparer(int i_answer, int i_guess)
{
    int directionOfGuess = 2;

    if (i_guess < i_answer)
    {
        // Gissat för lågt
        directionOfGuess = -1;
    }
    else if (i_guess > i_answer)
    {
        // Gissat för högt
        directionOfGuess = 1;
    }
    else
    {
        // Bra gissat!
        directionOfGuess = 0;
    }

    return directionOfGuess;
} // comparer

// ---------------------------------------------------------------------------- 

int main23(void)
{
    int guess, answer = 0;
    char repeatChar = '\0';

    printf_s("Welcome to the \"Guess a Number\" Game!\n");

    do
    {
        int tryCount = 0;

        // Slumpar ett tal
        srand((unsigned int)time(0));
        answer = rand() % 100 + 1;

        printf_s("You may now guess a number [1, 100] : \n");
        do
        {
            // Result returneras från comparer() och kan vara -1 = lågt, 0 = rätt, 1 = högt.
            int result = 2;

            printf_s("Guess: %d ", scanf_s("%d", &guess));
            //scanf_s("%d", &guess);

            result = comparer(answer, guess);
            tryCount = tryCount + 1;

            if (result == -1)
            {
                // Gissat för lågt
                printf_s(" Your guess is too low! try again!\n");
            }
            else if (result == 1)
            {
                // Gissat för högt
                printf_s(" Your guess is too High! try again!\n");
            }
            else
            {
                // Bra gissat!
                printf_s(" Your guess is correct!\n");
                printf_s("You made %d guesses!\n", tryCount);
                break;
            }
        } while (1 == 1);

        do
        {
            printf_s("Would you like to play again? (y/n): ");
            
            // Löser problemet med oönskade \n genom att läsa tills de är slut. 
            do
            {
                scanf_s("%c", &repeatChar, 1);
                //printf_s("\n%d\n", repeatChar);
            } while (repeatChar == 10);

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

    printf_s("\nThank you for playing the \"Guess a Number\" Game!\n\n");

    //system("pause");
    return 0;
} // main

// ---------------------------------------------------------------------------- 