#include <stdlib.h>
#include "string_funcs.h"

int str_is_number(char *str)
{
    while (*str)
    {
        if (!char_is_numeric(*str))
            return 0;
        str++;
    }
    return 1;
}

int my_str_len(char *str)
{
    int i;

    i = 0;
    while (str[i])
        i++;
    return i;
}
// Defensive:
// Input could be null ptr.
// Input could not contain a number
// Do we deal with whitespace or just see that as null?
// Dont accept whitespace, keep it simple stupid.
// Do we bother checking for overflow?
// Why are we even converting the number to int?
long simple_atoi(char *str)
{
	long output;
	int i;
	int sign;

	output = 0;
	i = 0;
	sign = 1;
	while (str[i] == '-' && ++i)
		sign *= -1;
	while (char_is_numeric(str[i]))
	{
		output *= 10;
		output += str[i] - '0';
		i++;
	}
	return output * sign;
}

int my_str_cmp(char *str1, char *str2)
{
	if (!str1 || !str2)
		return 0;
	while (*str1 && *str1 == *str2)
	{
		str1++;
		str2++;
	}
	return *str1 - *str2;
}

char *sub_str_dup (char *str, long nb)
{
	char *output;
	int i;
	
	if (!str || nb == 0)
		return 0;
	i = -1;
	output = malloc(nb+1);
	if (!output)
		return 0;
	output[nb] = '\0';
	while (++i < nb)
		output[i] = str[i];
	return output;
}


char *my_string_cat (char *str1, char *str2)
{
	char *output;
	long len;
	long i;

	if (!str1 || !str2)
		return 0;
	len = my_str_len(str1) + my_str_len(str2) + 1;
	output = malloc(len);
	output[len-1] = '\0';
	i = 0;
	while (*str1 != '\0' && ++i)
		output[i-1] = *str1++;
	while (*str2 != '\0' && ++i)
		output[i-1] = *str2++;
	return output;
}