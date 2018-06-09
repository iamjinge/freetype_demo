objects = main.o

CFLAGS = -I/usr/local/include/freetype2 \
	-I/usr/local/include/libpng16/

CPPFLAGS = -g 

LDFLAGS = -L/usr/local/lib

LIBS = -lfreetype \
	-lpng16

CC = gcc
CXX = g++

output : ${objects}
	cc $(LDFLAGS) $(LIBS) -o output ${objects}

main.o : main.c
	cc $(CFLAGS) -c main.c

example : example1.c
	$(CC) $(CFLAGS) $(LDFLAGS) $(LIBS) -o example example1.c

example5 : example5.cpp
	$(CXX) $(CFLAGS) $(LDFLAGS) $(LIBS) -o example5 example5.cpp

.PHONY : clean
clean :
	-rm output ${objects}