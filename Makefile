
CFLAGS = -Werror -O2 -std=c99

all: linked-list

linked-list.o: linked-list.c
	gcc $(CFLAGS) -c -o linked-list.o linked-list.c

linked-list: linked-list.o
	gcc $(CFLAGS) -o linked-list linked-list.o

clean:
	rm -f linked-list.o linked-list

