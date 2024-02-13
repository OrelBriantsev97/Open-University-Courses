magic:magic.o validation.o print.o
	gcc -g -ansi -Wall -pedantic magic.o validation.o print.o -o magic
magic.o:magic.c magic.h
	gcc -c -ansi -Wall -pedantic magic.c -o magic.o
validation.o:validation.c magic.h
	gcc -c -ansi -Wall -pedantic validation.c -o validation.o	
print.o:print.c magic.h
	gcc -c -ansi -Wall -pedantic print.c -o print.o


	 
