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

bool is_empty_stack(const Stack * s);;

void free_stack(Stack * s);

String *get_string_from_stack(const Stack *s);

void push_string_to_stack(Stack *s, const String *str);

void clear_stack(Stack * s);

#endif
