#include <stdio.h>

// Daniel och Göran 2016-01-28

// ============================================================================

int main12(void)
{
    int a = 0;
    int b = 0;

    printf_s("Welcome to the additionprogram PlussPluss! \nType your first integer: ");
    scanf_s("%d", &a);
    
    printf_s("Type your second integer: ");
    scanf_s("%d", &b);

    printf_s("The resulting sum is: %d + %d = %d\n\n", a, b, a+b);

    //system("pause");
    return 0;
}

// ============================================================================
