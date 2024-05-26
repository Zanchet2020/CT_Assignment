#include <stdio.h>
#include <stdlib.h>

#define STACK_INIT_SIZE 128

typedef struct {
  Datatype type_size;
  char * data;
  size_t capacity;
  size_t count;
} Stack;

Stack * new_stack(Datatype type){
  Stack * new = malloc(sizeof(Stack));
  new->type =(size_t)type;
  new->capacity = 0;
  new->count = 0;
  new->data = NULL;
  return new;
}

void push_stack(Stack * s, void * value){
  if(s->count >= s->capacity){
    s->capacity += STACK_INIT_SIZE;
    s->data = realloc(s->data, s->capacity * s->type_size);
  }
  *((uint8_t**)s->data * s->count * s->type_size) = value;
  s->count++;
}

void * pop_stack(Stack * s){
  return ((uint_t**)s->data)[s->count--];
}

int main(){
  printf("Hello World");  
  return 0;
}
