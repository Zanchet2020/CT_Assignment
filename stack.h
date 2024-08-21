#ifndef STACK_H_
#define  STACK_H_

#include <stdlib.h>
#include <stdbool.h>

#include "mystring.h"

#define STACK_INIT_SIZE 16

typedef struct {
  char * data;
  size_t capacity;
  size_t count;
} Stack;

void push_stack(Stack * s, const char value);

Stack * new_stack();

char pop_stack(Stack * s);

char get_top_from_stack(const Stack * s);

// retorna true se a stack tiver apenas o caractere Z
bool is_empty_stack(const Stack * s);;

void free_stack(Stack * s);

// retorna a string alocada dinamicamente sem a letra Z
String *get_string_from_stack(const Stack *s);

// insere string na stack EM ORDEM REVERSA   abc -> cba
// para que quando der pop a ordem seja abc
void push_string_to_stack(Stack *s, const String *str);

void clear_stack(Stack * s);

#endif
