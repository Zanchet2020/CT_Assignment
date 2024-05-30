#ifndef STACK_H_
#define  STACK_H_

#define STACK_INIT_SIZE 16

typedef struct {
  char * data;
  size_t capacity;
  size_t count;
} Stack;

Stack * new_stack(){
  Stack * new = malloc(sizeof(Stack));
  new->capacity = 0;
  new->count = 0;
  new->data = NULL;
  return new;
}

void push_stack(Stack * s, char value){
  if(s->count >= s->capacity){
    s->capacity += STACK_INIT_SIZE;
    s->data = realloc(s->data, s->capacity * sizeof(s->data[0]));
  }
  s->data[s->count++]= value;
}

char pop_stack(Stack * s){
  return s->data[--s->count];
}

char get_top_from_stack(Stack * s){
  return s->data[s->count - 1];
}

int is_empty_stack(Stack * s){
  return !s->count;
}

void free_stack(Stack * s){
  free(s->data);
  free(s);
}

#endif
