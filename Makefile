main_h:
	cc -Wall -Wextra -o main main.c


main: stack.c pda.c main.c mystring.c
	cc -Wall -Wextra -o main main.c stack.c pda.c mystring.c pda.o
