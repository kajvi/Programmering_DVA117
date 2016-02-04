#include <stdio.h>
// Daniel och Göran 20160204

float getKr(void)
{
    float kr = 0.0;
    printf_s("Enter the amount in Sek that you wish to convert: ");
    scanf_s("%f", &kr);
    return kr;
}

float krToEuro(float i_kr)
{
    float euro = 0.0;
    float kurs = 10.0;
    euro = i_kr * kurs;

    return euro;
}

void printer(float i_euro)
{
    printf_s("This equals %.2f Euro\n", i_euro);
    return;
}

int main22(void)
{
    float kr, euro = 0;

    printf_s("Welcome to the Sek to Euro exchangerate calculator!\n\n");
    kr = getKr();
    euro = krToEuro(kr);
    printer(euro);

    return 0;
}