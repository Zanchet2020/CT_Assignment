#ifndef MYSTRING_H_
#define  MYSTRING_H_

#include <stdlib.h>

#define STRING_INIT_SIZE 10

typedef struct {
  char * text;
  size_t count;
  size_t capacity;
} String;


String * new_string();

void append_to_string(String*, char *);

void free_string(String *);

#endif
