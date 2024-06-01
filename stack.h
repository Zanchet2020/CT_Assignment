#ifndef STACK_H_
#define  STACK_H_

#include <stdlib.h>

#include "mystring.h"

#define STACK_INIT_SIZE 16

typedef struct {
  char * data;
  size_t capacity;
  size_t count;
} Stack;

void push_stack(Stack * s, char value){
  if(s->count >= s->capacity){
    s->capacity += STACK_INIT_SIZE;
    s->data = (char*)realloc(s->data, s->capacity * sizeof(s->data[0]));
  }
  s->data[s->count++]= value;
}

Stack * new_stack(){
  Stack * newstack = (Stack*)malloc(sizeof(Stack));
  newstack->capacity = 0;
  newstack->count = 0;
  newstack->data = NULL;
  push_stack(newstack, 'Z');
  return newstack;
}

char pop_stack(Stack * s){
  return s->data[--s->count];
}

char get_top_from_stack(Stack * s){
  return s->data[s->count - 1];
}

bool is_empty_stack(Stack * s){
  return get_top_from_stack(s) == 'Z';
}

void free_stack(Stack * s){
  free(s->data);
  free(s);
}

String *get_string_from_stack(Stack *s) {
  String * str = new_string();
  for(size_t i =0; i < s->count; ++i){
    char c[2];
    c[0] = s->data[i];
    c[1] = '\0';
    append_to_string(str, c);
  }
  return str;
}

void push_string_to_stack(Stack * s, String * str) {
  for(int i = str->count - 1; i >= 0; --i){
    push_stack(s, str->text[i]);
  }
}

#endif
