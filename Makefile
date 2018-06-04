objects = main.o

CFLAGS = -I/usr/local/include/freetype2 \
	-I/usr/local/include/libpng16/

LDFLAGS = -L/usr/local/lib

LIBS = -lfreetype \
	-lpng16

cc = gcc

output : ${objects}
	cc $(LDFLAGS) $(LIBS) -o output ${objects}

main.o : main.c
	cc $(CFLAGS) -c main.c

example : example1.o
	$(CC) $(LDFLAGS) $(LIBS) -o example example1.o

example.o : example1.c
	$(CC) $(CFLAGS) -c example1.c

.PHONY : clean
clean :
	-rm output ${objects}