// ============================================================================
// GetNumberWithoutENTER.c
//
// Receive an integer number without detecting any ENTER-key.
// For use in the Nunber Guessing Game
// Restrictions: 
//	1. Cannot handle negative max int as it received number as a positiva value...
//  2- No edit facility (i.e. backspace etc.)
//
// History
// 2016-02-05/GF	Introduced.
// ======================================================================================

#include <stdio.h>
#include <conio.h>

#include "GetNumberWithoutENTER.h"

// ======================================================================================

int getNumberWithoutENTER(int i_UsedWidth)
{
	int theNumber = 0;
	char ch;
	int anyDigitOrSignRecieved = 0;
	int isNegative = 0;
	int pos = 0;

	do
	{
		ch = _getch();
		if ( (anyDigitOrSignRecieved == 0) && ( (ch == '-') || (ch == '+') ) )
		{
			if (ch == '-')
			{
				// We have a minus sign
				isNegative = 1;
			}
			anyDigitOrSignRecieved = 1;
			printf("%c", ch);
			pos++;
		}
		else if ( (ch >= '0') && (ch <= '9') )
		{
			// We have a digit - add up 
			theNumber = theNumber * 10 + (ch - '0');
			anyDigitOrSignRecieved = 1;
			printf("%c", ch);
			pos++;
		}
		else
		{
			// Assume number is finished...
			if (isNegative)
			{
				theNumber = -theNumber; // NB: Does not handle MAX NEG INT!
			}

			// Adjust width
			for (; pos < i_UsedWidth; pos++)
			{
				printf(" ");
			}
			return theNumber;
		}
	} while (1);

} // getNumberWithoutENTER

// ======================================================================================

