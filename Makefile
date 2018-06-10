objects = main.o

CFLAGS = -I/usr/local/include/freetype2 \
	-I/usr/local/include/libpng16/

CPPFLAGS = -g 

LDFLAGS = -L/usr/local/lib

LIBS = -lfreetype \
	-lpng16

FS = ../freetype2/src/

E1S = $(FS)autofit/autofit.c \
	$(FS)base/basepic.c \
	$(FS)base/ftapi.c \
	$(FS)base/ftbase.c \
	$(FS)base/ftbbox.c \
	$(FS)base/ftbitmap.c \
	$(FS)base/ftdbgmem.c \
	$(FS)base/ftdebug.c \
	$(FS)base/ftglyph.c \
	$(FS)base/ftinit.c \
	$(FS)base/ftpic.c \
	$(FS)base/ftstroke.c \
	$(FS)base/ftsynth.c \
	$(FS)base/ftsystem.c \
	$(FS)/cff/cff.c \
	$(FS)/pshinter/pshinter.c \
	$(FS)/psnames/psnames.c \
	$(FS)/raster/raster.c \
	$(FS)/sfnt/sfnt.c \
	$(FS)/smooth/smooth.c \
	$(FS)/truetype/truetype.c

CC = gcc
CXX = g++

output : ${objects}
	cc $(LDFLAGS) $(LIBS) -o output $(objects)

main.o : main.c
	cc $(CFLAGS) -c main.c

example1 : example1.c $(E1S)
	$(CC) -I../freetype2/include \
	-I../freetype2/include/freetype \
	-I../freetype2/include/freetype/config \
	-I../freetype2/include/freetype/internal \
	-o example example1.c $(E1S)

example5 : example5.cpp
	$(CXX) $(CFLAGS) $(LDFLAGS) $(LIBS) -o example5 example5.cpp

.PHONY : clean
clean :
	-rm output $(objects)