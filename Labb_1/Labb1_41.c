#include <stdio.h>
// Daniel och Göran 20160128


int main(void)
{
    int code = -1;
    int error = 0;
    int end = -1;

    do
    {
        do
        {
            printf_s("Type an integer in the range [0,5]: ");
            scanf_s("%d", &code);
            error = 0;

            if (code < 0 || code > 5)
            {
                error = 1;
                printf_s("**** The number you chose was out of range!!\n");
            }
        } while (error == 1);

        printf_s("Morse code: ");
        switch (code)
        {
        case 0:
            printf_s("-----\n");
            break;
        case 1:
            printf_s(".----\n");
            break;
        case 2:
            printf_s("..---\n");
            break;
        case 3:
            printf_s("...--\n");
            break;
        case 4:
            printf_s("....-\n");
            break;
        case 5:
            printf_s(".....\n");
            break;
        default:
            break;
        }
        printf_s("Do you want to continue? Yes = 1, No = 0? ");
        scanf_s("%d", &end);

    } while (end != 0);

    return 0;
}