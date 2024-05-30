#ifndef PDA_H_
#define PDA_H_

#include <stdbool.h>

#include "mystring.h"
#include "stack.h"


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
  push_stack(pda->stack, 'Z'); 

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

int is_word_in_lang(PDA * pda, char * word){
  size_t current_letter_index = 0, current_state = 0;
  
  for(size_t i = 0; i < pda->num_of_states; ++i){
    char to_consume = pda->states.transitions[current_state][i].consume;
    char to_unstack = pda->states.transitions[current_state][i].unstack;
    char current_stack_top = get_top_from_stack(pda->stack);

    bool should_transition = true
    
    if(to_consume == '&'){
      if(
    }
    
    if(to_consume == word[current_letter_index] && to_unstack == current_stack_top){
      
    }
  }
}

#endif
