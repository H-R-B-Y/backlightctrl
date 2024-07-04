
FLAGS = -Wall -Wextra -Werror -g

all: backlightctrl

backlightctrl: backlightctrl.c src/write_backlight.o src/string_funcs.o src/fileio.o src/string_calc.o src/parsing.o
	gcc $(FLAGS) backlightctrl.c src/write_backlight.o src/string_funcs.o src/fileio.o src/string_calc.o src/parsing.o -o backlightctrl

src/parsing.o: src/string_funcs.c
	gcc $(FLAGS) -c src/parsing.c -o src/parsing.o

src/string_calc.o: src/string_calc.c
	gcc $(FLAGS) -c src/string_calc.c -o src/string_calc.o

src/write_backlight.o: src/write_backlight.c 
	gcc $(FLAGS) -c src/write_backlight.c -o src/write_backlight.o

src/string_funcs.o: src/string_funcs.c
	gcc $(FLAGS) -c src/string_funcs.c -o src/string_funcs.o

src/fileio.o: src/fileio.c
	gcc $(FLAGS) -c src/fileio.c -o src/fileio.o

fclean: clean
	rm -f backlightctrl

clean:
	rm  -f src/*.o

re: fclean all

.phony: clean fclean re