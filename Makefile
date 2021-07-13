default: main.c
	gcc -W -std=c17 main.c -o bmi `pkg-config --cflags --libs gtk4`