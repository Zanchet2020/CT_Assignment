#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "stack.h"

#define STRING_INIT_SIZE 10

typedef struct {
  char * text;
  size_t count;
  size_t capacity;
} String;

String * new_string(){
  String * str = (String*)malloc(sizeof(String));
  str->count = 0;
  str->capacity = STRING_INIT_SIZE;
  str->text = (char*) malloc(str->capacity * sizeof(char));
  return str;
}

void append_to_string(String* str, char * txt){
  for(size_t i = 0; txt[i] != '\0'; ++i){
    if(str->count >= str->capacity){
      str->capacity += STRING_INIT_SIZE;
      str->text = realloc(str->text, str->capacity * sizeof(char));
    }
    str->text[i + str->count] = txt[i];
    str->count++;
  }
}

void free_string(String * str){
  free(str->text);
  free(str);
}


typedef struct {
  char consume;
  char unstack;
  String * stack;
} Transition;

typedef struct {
  Transition ** transitions;
  bool * is_final_state;
} Graph;

typedef struct {
  Stack * stack;
  Graph states;
  size_t num_of_states;
  
} PDA;

PDA * new_pda(size_t number_of_states){
  size_t Q = number_of_states;
  PDA * pda = (PDA*)malloc(sizeof(*pda));
  pda->num_of_states = Q;
  pda->stack = new_stack();
  pda->states.transitions = (Transition**) malloc(Q*sizeof(Transition*));
  pda->states.is_final_state = (bool*) malloc(Q*sizeof(bool));
  for(size_t i = 0; i < Q; ++i){
    pda->states.transitions[i] = (Transition*) malloc(Q*sizeof(Transition));
    pda->states.is_final_state[i] = false;
    for(size_t j = 0; j < Q; ++j){
      pda->states.transitions[i][j].stack = new_string();
    }
  }
  return pda;
}

void free_pda(PDA * pda){
  for(size_t i = 0; i < pda->num_of_states; ++i){
    for(size_t j = 0; j < pda->num_of_states; ++j){
      free_string(pda->states.transitions[i][j].stack);
    }
    free(pda->states.transitions[i]);
  }
  free(pda->states.transitions);
  free_stack(pda->stack);
  free(pda);
}

int main(){
  size_t Q = 0, T = 0;
  scanf("%zu %zu", &Q, &T);
  PDA * pda = new_pda(Q);
  
  for(size_t i = 0; i < T; ++i){
    size_t from_state, to_state;
    char consume, unstack;
    char stack[100];
    scanf("%zu %c %c %s %zu", &from_state, &consume, &unstack, stack, &to_state);
    //    printf("%zu %c %c %s %zu", from_state, consume, unstack, stack, to_state);
    Transition t = {
      .consume = consume,
      .unstack = unstack,
      .stack = new_string()
    };
    append_to_string(t.stack, stack);
    pda->states.transitions[from_state][to_state] = t;
  }

  size_t num_of_final_states = 0;
  scanf("%zu", &num_of_final_states);
  for(size_t i = 0; i < num_of_final_states; ++i){
    size_t index;
    scanf("%zu", &index);
    pda->states.is_final_state[index] = true;
  }
  
  free_pda(pda);
  //  printf("Hello\n");
  return 0;
}
