
int char_is_numeric(char c)
{
    return (c >= '0' && c <= '9');
}

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

