
#ifndef myATtoi_H
#define myATtoi_H
//http://www.geeksforgeeks.org/write-your-own-atoi/
// A simple C++ program for implementation of atoi

#include <stdio.h>
#include <stdlib.h>

// A utility function to check whether x is numeric
bool isNumericChar(char x)
{
	return (x >= '0' && x <= '9')? true: false;
}

// A simple atoi() function. If the given string contains
// any invalid character, then this function returns 0
int myAtoi(char *str)
{
	if (*str == 0) return 0;

	int res = 0; // Initialize result
	int sign = 1; // Initialize sign as positive
	int i = 0; // Initialize index of first digit

  for (; str[i] != '\0'; ++i)
	{
		if(str[i] == ' ' && res == 0) continue;
		else if(str[i] == '-' &&  res == 0) sign = -1;
		else if(str[i] == '+' &&  res == 0) sign = 1;
		else if(isNumericChar(str[i]) == false) break;
		else res = res*10 + str[i] - '0';
	}
	// Return result with sign
	return sign*res;
}

char* myItoa(int value, char* result, int base) {
	// check that the base if valid
	if (base < 2 || base > 36) { *result = '\0'; return result; }

	char* ptr = result, *ptr1 = result, tmp_char;
	int tmp_value;

	do {
		tmp_value = value;
		value /= base;
		*ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
	} while ( value );

	// Apply negative sign
	if (tmp_value < 0) *ptr++ = '-';
	*ptr-- = '\0';
	while(ptr1 < ptr) {
		tmp_char = *ptr;
		*ptr--= *ptr1;
		*ptr1++ = tmp_char;
	}
	return result;
}

#endif
