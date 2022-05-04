
CFLAGS = -Werror -O2 -std=c99

all: linked-list

linked-list.o: linked-list.c linked-list.h
	gcc $(CFLAGS) -c -o linked-list.o linked-list.c

linked-list-test.o: linked-list-test.c
	gcc $(CFLAGS) -c -o linked-list-test.o linked-list-test.c

linked-list: linked-list.o linked-list-test.o
	gcc $(CFLAGS) -o linked-list linked-list.o linked-list-test.o

clean:
	rm -f linked-list.o linked-list-test.o linked-list

