objects = main.o

cc = gcc

output : ${objects}
	cc -o output ${objects}

main.o : main.c
	cc -I /usr/local/include/freetype/ -c main.c

.PHONY : clean
clean :
	-rm output ${objects}