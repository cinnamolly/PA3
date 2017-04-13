CC=gcc
CFLAGS=-I.
DEPS = maxheap.h
OBJ = maxheap.o kk.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

kk: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)