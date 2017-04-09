CC=gcc

GLIB_FLAGS = `pkg-config --cflags --libs glib-2.0`

ex_compile: ex_compile.c
	gcc -o ex_compile ex_compile.c $(GLIB_FLAGS)

word_count: word_count.c
	gcc -o word_count word_count.c $(GLIB_FLAGS)

