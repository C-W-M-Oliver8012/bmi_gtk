default: main.c
	gcc -W -Werror -std=c17 main.c -o bmi `pkg-config --cflags --libs gtk4`