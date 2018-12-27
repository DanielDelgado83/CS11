#
# CS 11: Makefile for C track, assignment 5.
#

CC     = gcc
CFLAGS = -g -Wall -Wstrict-prototypes -ansi -pedantic

all: 1dca_array_ops 1dca_pointer_ops

1dca_array_ops: 1dca_array_ops.o memcheck.o
	$(CC) 1dca_array_ops.o -o 1dca_array_ops

1dca_pointer_ops: 1dca_pointer_ops.o memcheck.o
	$(CC) 1dca_pointer_ops.o -o 1dca_pointer_ops

1dca_array_ops.o: 1dca_array_ops.c
	$(CC) $(CFLAGS) -c 1dca_array_ops.c

1dca_pointer_ops.o: 1dca_pointer_ops.c
	$(CC) $(CFLAGS) -c 1dca_pointer_ops.c

memcheck.o: memcheck.c
	$(CC) $(CFLAGS) -c memcheck.c

check:
	sudo ./c_style_check 1dca_pointer_ops.c 1dca_array_ops.c

clean:
	rm -f *.o 1dca_array_ops 1dca_pointer_ops



