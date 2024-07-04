

#ifndef STRING_FUNCS_H
# define STRING_FUNCS_H

# define char_is_numeric(c) (c >= '0' && c <= '9')
# define char_is_whtspc(c) (c == '\t' || c == '\n' || c == '\f' || c == '\r' || c == '\v' || c == ' ')
# define char_is_print(c) (c >= 32 && c <= 126)

int		str_is_number(char *str);
int		my_str_len(char *str);
long	simple_atoi(char *str);
int		my_str_cmp(char *str1, char *str2);
char	*sub_str_dup (char *str, long nb);

#endif
