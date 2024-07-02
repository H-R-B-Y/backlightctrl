#include "src/fileio.h"
#include "src/static.h"
#include "src/string_funcs.h"
#include "src/write_backlight.h"
#include "src/string_calc.h"

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

void handle_relative_input(int increment)
{
    int fd;
    char *cv;
    char *nv;
    int buffer;

    buffer = max_line_length(BACKLIGHT_PATH);
    cv = malloc(buffer + 1);
    cv[buffer] = '\0';
    fd = open(BACKLIGHT_PATH, O_RDONLY);
    read_line(fd, cv, buffer);
    close(fd);
    nv = my_str_add(cv, increment);
    free(cv);
    if (validate_inputs(nv))
        set_backlight(nv);
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
void handle_inputs(int argc, char **argv)
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
        handle_relative_input(value);
    }
    else if (!my_str_cmp(argv[1], "set"))
    {
        if (argc < 3)
            return ;
        if (!validate_inputs(argv[2]))
            return ;
        set_backlight(argv[2]);
    }
    else if (!my_str_cmp(argv[1], "clr"))
        clear_backlight();
}


int main (int argc, char **argv)
{
    if (argc > 1)
        handle_inputs(argc, argv);
    else
        write(1, "No Opertation Specified", 23);
}


// #include <stdio.h>
// #include <stdlib.h>
// int main ()
// {
//     char *t;
//     t = malloc(4+1);
//     t[4] = '\0';
//     t[3] = '2';
//     t[2] = '9';
//     t[1] = '9';
//     t[0] = '0';
//     printf("%s\n", t);
//     t = my_str_add(t, -10);
//     printf("%s", t);
// }