
#include <fcntl.h>
#include <unistd.h>
#include "static.h"
#include "string_funcs.h"

// Returns 1 if string is all numeric


// takes string to be the value we are setting the backlight too.
// will check that there is no whitespace, all numeric,
// and less than max_brightness set in static.h
// will return 1 if valid else invalid.
int validate_inputs(char *str)
{
    // checking that the str is a number would be a good start.
    if (!str_is_number(str))
        return 0;
    // then check lengths
    if (my_str_len(str) > my_str_len(MAX_BRIGHTNESS))
        return 0;
    // then check greater
    if (my_str_len(str) == my_str_len(MAX_BRIGHTNESS) 
        && my_str_cmp(str, MAX_BRIGHTNESS) > 0)
        return 0;
    return 1;
}

int clear_backlight()
{
    int fd;

    fd = open(BACKLIGHT_PATH, O_WRONLY | O_TRUNC);
    if (fd < 1)
        return 0;
    write(fd, "0", 1); 
    return 1;
}

// External interface, will check inputs are valid.
// Returns:
// 0 for a valid write
// a non zero int for an invalid operation.
int set_backlight(char *str)
{
    int fd;

    if (!str  || !validate_inputs(str))
        return 0;
    fd = open(BACKLIGHT_PATH, O_WRONLY | O_TRUNC);
    if (fd < 1)
        return 0;
    write(fd, str, my_str_len(str));
    return 1;
}

