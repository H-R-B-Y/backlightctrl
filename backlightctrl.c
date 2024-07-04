#include "src/fileio.h"
#include "src/static.h"
#include "src/string_funcs.h"
#include "src/write_backlight.h"
#include "src/string_calc.h"
#include "src/parsing.h"

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

void handle_relative_input(int increment, struct s_backlight *target)
{
    int fd;
    char *cv;
    char *nv;
    int buffer;

    buffer = max_line_length(target->path);
    cv = malloc(buffer + 1);
    cv[buffer] = '\0';
    fd = open(target->path, O_RDONLY);
    read_line(fd, cv, buffer);
    close(fd);
    nv = my_str_add(cv, increment);
    free(cv);
    if (validate_input_str(nv, target->max_brightness_string))
        set_backlight(nv, target);
    free(nv);
}

// need some way to handle the inputs
// we have
// backlightctrl add
// backlightctrl add <number>
// backlightctrl min
// backlightctrl min <number>
// backlightctrl set
// backlightctrl set <number>
// backlightctrl clr
void handle_inputs(int argc, char **argv, struct s_backlight *target)
{
	int value;

	if (argc == 1)
		return ;
	if (!my_str_cmp(argv[1], "add") || !my_str_cmp(argv[1], "min"))
	{
		value = DEFAULT_INCREMENT;
		if (argc > 2)
			value = simple_atoi(argv[2]);
		if (!my_str_cmp(argv[1], "min"))
			value *= -1;
		handle_relative_input(value, target);
	}
	else if (!my_str_cmp(argv[1], "set"))
	{
		if (argc < 3)
			return ;
		if (!validate_input_str(argv[2], target->max_brightness_string))
			return ;
		set_backlight(argv[2], target);
	}
	else if (!my_str_cmp(argv[1], "clr"))
		clear_backlight(target->path);
}

int main(int argc, char **argv)
{
	long c_count; 
	struct s_backlight **configs;
	long target;

	configs = 0;
	if (argc == 1 || argc == 2)
	{
		write(1, "Error: Invalid input", 20);
		return -1;
	}
	configs = get_backlights("./devices.cfg", &c_count);
	if (c_count < 1 || (configs == 0 && *configs == 0))
	{
		write(1, "Error loading configs, please configure devices.cfg", 51);
		return -1;
	}
	target = simple_atoi(argv[1]);
	if (target > c_count-1)
	{
		write(1, "Error: Invalid target", 21);
		return -1;
	}
	handle_inputs(argc-1, argv+1, configs[target]);
}
