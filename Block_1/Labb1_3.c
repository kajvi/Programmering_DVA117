#include <stdio.h>

// Daniel och Göran 2016-01-28

// ============================================================================

int main13(void)
{
    int angle = 0;
    int error = 0;

    do
    {
        printf_s("Hi! Type an angle in the range (0, 360) : ");
        scanf_s("%d", &angle);
        if ((angle <= 0 || angle >= 360))
        {
            error = 1;
            printf_s(" **** You have entered a integer outside the range, please choose an integer in the range [0, 360]!\n");
        }
        else
        {
            error = 0;
        }
    } while (error == 1);
    
    if (angle < 90)
    {
        printf_s("Your angle is accute!\n");
    }
    else if (angle == 90)
    {
        printf_s("Your angle is perpendicular!\n");
    }
    else
    {
        printf_s("Your angle is obtuse!\n");
    }
    return 0;
} // main

// ============================================================================
