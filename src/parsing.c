
#include "fileio.h"
#include "parsing.h"
#include "string_funcs.h"

#include <stdlib.h>
#include <fcntl.h>

// use pipe as deliminator "|"
int validate_line(char *line)
{
	int pipe_found;

	if (!line || *line == '\0')
		return 0;
	pipe_found = 0;
	while (*line != '\0')
		if (*line++ == '|' && ++pipe_found)
			break ;
	if (*(line-1) != '|')
		return 0;
	while (char_is_whtspc(*line))
		line++;
	if (*line == '\0' || !char_is_numeric(*line))
		return 0;
	while (char_is_numeric(*line))
		line++;
	while (char_is_whtspc(*line))
		line++;
	if (*line != '\0')
		return 0;
	return 1 * pipe_found;
}

// Return null pointer for any malformed data.
struct s_backlight *backlight_from_line(char *line)
{
	struct s_backlight *this;
	char *start;
	char *end;

	this = malloc(sizeof(struct s_backlight));
	start = line;
	while (char_is_whtspc(*start) && *start != '\0')
		start++;
	end = start;
	while (*end != '|' && *end != '\0')
		end++;
	if (*end == '\0')
		return 0;
	this->path = sub_str_dup(start, end-start);
	start = end+1;
	while (char_is_whtspc(*start) && *start != '\0')
		start++;
	if (*start == '\0' || !char_is_numeric(*start))
		return 0;
	end = start; 
	while (char_is_numeric(*end) && *end != '\0')
		end ++;
	this->max_brightness_string = sub_str_dup(start, end - start);
	this->max_brightness = simple_atoi(this->max_brightness_string);
	return this;
}

struct s_backlight **get_backlights(char *path, long *options)
{
	struct s_backlight **arr;
	unsigned long buffer_size;
	int fd;
	char *buffer;

	if (!options)
		return 0;
	*options = 0;
	buffer_size = max_line_length(path);
	fd = open(path, O_RDONLY);
	if (fd < 1 || buffer_size == 0)
		return 0;
	buffer = malloc(buffer_size);
	if (!buffer)
		return 0;
	arr = malloc(sizeof(struct s_backlight *));
	while (read_line(fd, buffer, buffer_size) && *buffer != '\0')
	{
		if (!validate_line(buffer))
			continue ;
		arr[*options] = backlight_from_line(buffer);
		*options += 1;
	}
	return arr;
}
