#include <stdio.h>

// Daniel och Göran 20160204


// ============================================================================

void main21(void)
{
    int inputNumber, min, max, sum, count = 0; 
    char repeatChar = '\0';

    printf_s("Welcome to the Sequence calculator MaxMinSumMean! \n ");

    do
    {
        int continueFlag = 1;

        printf_s("You may now enter nonnegative integer values.\nYour sequence will end when u enter a negative integer value.\n");
        do
        {
            printf_s("Enter an integer: ");
            scanf_s("%d", &inputNumber);
            //fflush(stdin);
            if (inputNumber >= 0)
            {
                // We have a positive nonnegative integer - Do calculations.

                if (count == 0)
                {
                    // This is the first number entered - Initialize variables.
                    min = inputNumber;
                    max = inputNumber;
                    sum = inputNumber;
                }
                else
                {
                    // We have several numbers - update the variables
                    if (inputNumber < min)
                    {
                        min = inputNumber;
                    }
                    if (inputNumber > max)
                    {
                        max = inputNumber;
                    }
                    sum = sum + inputNumber;
                }
                count = count + 1;
            }
            else
            {
                // We have a negative integer, end the sequence.
                continueFlag = 0;
            }

        } while (continueFlag == 1);

        // Sequence finnished - Display result.
        printf_s("\n");

        if (count == 0)
        {
            printf_s("No sequence entered. No results avalible\n");
        }
        else
        {
            printf_s("The smallest number is:    %d\n", min);
            printf_s("The largets number is:     %d\n", max);
            printf_s("The sum of the numbers is: %d\n", sum);
            printf_s("The mean of the number is: %f\n\n", (float)sum / count);
        }

        do
        {
            printf_s("Would you like to enter a new sequence? (y/n): ");
            do
            {
                scanf_s("%c", &repeatChar, 1);
                //printf_s("\n%d\n", repeatChar);
            } while (repeatChar == 10);
            
            //scanf_s("_%c", &repeatChar);
            // printf_s("\n%d\n", repeatChar);


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


    printf_s("\nThank you for using MaxMinSumMean!\n\n ");
    //system("pause");

} // main

// ============================================================================


