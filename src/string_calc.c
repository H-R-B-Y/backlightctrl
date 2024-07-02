
#include "string_funcs.h"
#include <stdlib.h>

#include <stdio.h>

unsigned long characters_needed(long val)
{
    int i = 1;
    while (val / 10)
    {
        i++;
        val /= 10;
    }
    return i;
}
// works fine for positive values, negative values are converted to 0;
char *my_str_add(char *str, int add)
{
    long value;
    int length;
    char *output;

    if (!str || !str_is_number(str))
        return 0;
    value = simple_atoi(str);
    if (add < 0 && add * -1 > value)
        value = 0;
    else
        value += add;
    length = characters_needed(value);
    output = malloc(length + 1);
    output[length] = '\0';
    while (length--)
    {
        output[length] = (value % 10) + '0';
        value /= 10;
        printf("%d\n", length);
    }
    return output;
}