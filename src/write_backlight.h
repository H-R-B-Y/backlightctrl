
#ifndef WRITE_BACKLIGHT_H
# define WRITE_BACKLIGHT_H

# include "static.h"
# include "parsing.h"

int str_is_number(char *str);
int validate_input_str(char *str, char *max_brightness);
int clear_backlight(char *backlight_path);
int set_backlight(char *str, struct s_backlight *target);

#endif