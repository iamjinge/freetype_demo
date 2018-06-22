objects = main.o

CFLAGS = -I/usr/local/include/freetype2 \
	-I/usr/local/include/libpng16/

CPPFLAGS = -g 

LDFLAGS = -L/usr/local/lib

LIBS = -lfreetype \
	-lpng16

FS = ../freetype2/src/
FO = ../freetype2/objs/.libs

E1S = $(FS)*/*.c

E1O = $(FO)*.o

CC = gcc
CXX = g++

output : ${objects}
	cc $(LDFLAGS) $(LIBS) -o output $(objects)

main.o : main.c
	cc $(CFLAGS) -c main.c

analyze : 
	$(CC) -MM $(CFLAGS) \
	example5.cpp

example1 : example1.o
	$(CC) -o example1 example1.o \
	$(FO)/libfreetype.6.dylib

example1.o : example1.c 
	$(CC) -I../freetype2/include \
	-I../freetype2/include/freetype \
	-I../freetype2/include/freetype/config \
	-I../freetype2/include/freetype/internal \
	 -c example1.c

example5 : example5.o
	$(CXX) $(LDFLAGS) $(LIBS) -o example5 example5.o

example5.o : example5.cpp
	$(CXX) $(CFLAGS) -c example5.cpp

test : test.o
	$(CC) $(LDFLAGS) $(LIBS) -o test test.o

test.o : test.c
	$(CC) $(CFLAGS) -c test.c

example6 : example6.o
	$(CXX) $(LDFLAGS) $(LIBS) -o example6 example6.o

example6.o : example6.cpp
	$(CXX) $(CFLAGS) -c example6.cpp

filetest : filetest.c
	$(CC) -o filetest filetest.c

.PHONY : clean
clean :
	-rm output $(objects)