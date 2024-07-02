
#ifndef FILEIO_H
# define FILEIO_H

unsigned long max_line_length(char *path);
char *read_line(int fd, char *buffer, unsigned long size);

#endif
