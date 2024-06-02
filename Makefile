main_h:
	cc -Wall -Wextra -o main main.c


main: stack.o mystring.o pda.o
	cc -Wall -Wextra -o main main.c stack.o pda.o mystring.o pda.o

pda: stack.o mystring.o
	cc -Wall -Wextra -c pda.c stack.o mytring.o -o pda.o 

stack: mystring.o
	cc -Wall -Wextra -c strack.c mystring.o -o stack.o

mystring:
	cc -Wall -Wextra -c mystring.c -o mystring.o
