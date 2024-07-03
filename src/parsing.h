

#ifndef PARSING_H
# define PARSING_H

struct s_backlight
{
	char *path;
	unsigned long max_brightness;
	char *max_brightness_string;
};

int		validate_line(char *line);
struct	s_backlight *backlight_from_line(char *line);
struct	s_backlight **get_backlights(char *path, long *options);

#endif