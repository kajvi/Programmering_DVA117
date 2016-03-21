#include <stdio.h>

void main(void)
{
    int i1, i2, i3;

    i1 = 1;
    i2 = !1;
    i3 = !0x01;


    printf_s("%d   %d   %d\n", i1, i2, i3);

}