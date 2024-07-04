
#include <fcntl.h>
#include <unistd.h>
#include "static.h"
#include "string_funcs.h"
#include "parsing.h"

// takes string to be the value we are setting the backlight too.
// will check that there is no whitespace, all numeric,
// and less than max_brightness set in static.h
// will return 1 if valid else invalid.
int validate_input_str(char *str, char *max_brightness)
{
	// checking that the str is a number would be a good start.
	if (!str_is_number(str))
		return 0;
	// then check lengths
	if (my_str_len(str) > my_str_len(max_brightness))
		return 0;
	// then check greater
	if (my_str_len(str) == my_str_len(max_brightness) 
		&& my_str_cmp(str, max_brightness) > 0)
		return 0;
	return 1;
}

int clear_backlight(char *backlight_path)
{
	int fd;

	fd = open(backlight_path, O_WRONLY | O_TRUNC);
	if (fd < 1)
		return 0;
	write(fd, "0", 1); 
	return 1;
}

// External interface, will check inputs are valid.
// Returns:
// 0 for a valid write
// a non zero int for an invalid operation.
int set_backlight(char *str, struct s_backlight *target)
{
	int fd;

	if (!str  || !validate_input_str(str, target->max_brightness_string))
		return 0;
	fd = open(target->path, O_WRONLY | O_TRUNC);
	if (fd < 1)
		return 0;
	write(fd, str, my_str_len(str));
	return 1;
}

