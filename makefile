
FLAGS = -Wall -Wextra -Werror

all: backlightctrl

backlightctrl: backlightctrl.c src/write_backlight.o src/string_funcs.o src/fileio.o src/string_calc.o
	gcc $(FLAGS) backlightctrl.c src/write_backlight.o src/string_funcs.o src/fileio.o src/string_calc.o -o backlightctrl

src/string_calc.o: src/string_calc.c
	gcc $(FLAGS) -c src/string_calc.c -o src/string_calc.o

src/write_backlight.o: src/write_backlight.c src/string_funcs.o
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

.phony: clean fclean 