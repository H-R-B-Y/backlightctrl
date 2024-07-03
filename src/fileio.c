
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

unsigned long max_line_length(char *path)
{
    char t;
    unsigned long len;
    unsigned long line_start;
    unsigned long index;
    int fd; 

    fd = open(path, O_RDONLY);
    if (fd < 1)
        return 0;
    len = 0;
    line_start = 0;
	index = 0;
    while (read(fd, &t, 1) == 1)
    {
        if (t != '\n' && ++index)
            continue ;
        else if (index - line_start > len || len == 0)
            len = index - line_start;
        line_start = index;
        index++;
    }
    if (len == 0)
        len = index;
    return len;
}

char *read_line(int fd, char *buffer, unsigned long size)
{
    unsigned long index;
    char t;

    if (!fd || !buffer || size < 1)
        return 0;
    index = 0;
    while (read(fd, &t, 1) == 1 && t != '\n' && index < size)
        buffer[index++] = t;
    buffer[index] = '\0';
    return buffer;
}
