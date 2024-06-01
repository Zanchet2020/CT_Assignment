#ifndef PDA_H_
#define PDA_H_

#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>

#include "mystring.h"
#include "stack.h"

#define NODE_SUBNODE_ARRAY_INIT_SIZE STRING_INIT_SIZE

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
  size_t state;
  String * current_word;
  String * current_stack;
} Computation;

typedef struct {
  Computation * c;
  size_t capacity;
  size_t count;
} Comp_Stack;

Comp_Stack * new_computation_stack(){
  Comp_Stack * ncs = (Comp_Stack*) malloc(sizeof(Comp_Stack));
  ncs->capacity = 0;
  ncs->count = 0;
  ncs->c = NULL;
  return ncs;
}

void push_computation_stack(Comp_Stack *cs, Computation c) {
  if(cs->count >= cs->capacity){
    cs->capacity += STACK_INIT_SIZE;
    cs->c = (Computation*)realloc(cs->c, cs->capacity * sizeof(Computation));
  }
  cs->c[cs->count++] = c;
}

Computation pop_computation_stack(Comp_Stack *cs) {
  return cs->c[--cs->count];
}

void free_computation_stack(Comp_Stack *cs) {
  free(cs->c);
  free(cs);
}

bool is_computation_stack_empty(Comp_Stack *cs) {
  return cs->count == 0;
}

/* typedef struct Node{ */
/*   Computation c; */
/*   Node ** sub_nodes; */
/*   size_t num_of_nodes; */
/*   size_t capacity; */
/* } Node; */

typedef struct {
  Stack * stack;
  Graph states;
  size_t num_of_states;
  //  Node * history;
} PDA;

/* Node *new_node() { */
/*   Node * n = (Node*) malloc(sizeof(Node)); */
/*   n->num_of_nodes = 0; */
/*   n->sub_nodes = NULL; */
/*   n->c = {0}; */
/*   n->capacity = 0; */
/*   return n; */
/* } */

/* void add_computation_to_node(Node* tree, Computation new_computation){ */
/*   if(tree->num_of_nodes >= tree->capacity){ */
/*     tree->capacity += NODE_SUBNODE_ARRAY_INIT_SIZE; */
/*     tree->sub_nodes = (Node**) realloc(tree->sub_nodes, tree->capacity * sizeof(Node*)); */
/*   } */
/*   Node * n = new_node(); */
/*   n->c = new_computation; */
/*   tree->sub_nodes[tree->num_of_nodes++] = n; */
/* } */


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

bool is_word_in_lang(PDA * pda, char * word, size_t state, Comp_Stack * cs){
  size_t value =
    ((uint8_t)(word[0] == '\0') << 2) +
    ((uint8_t)(pda->states.is_final_state[state]) << 1) + 
    ((uint8_t)(is_empty_stack(pda->stack)) << 0);

  // 111 (7) -> word is in language                                -> return true and save computation
  // 110 (6) -> word empty but stack isn't empty                   -> false and don't save computation
  // 101 (5) -> word n stack empty but didn't reach final state    -> false and don't save computation
  // 100 (4) -> word empty but stack not and isn't final state     -> false and don't save computation
  // 011 (3) -> word isn't empty                                   -> continue recursion
  // 010 (2) -> final state but word and stack aren't empty        -> continue recursion
  // 001 (1) -> stack is empty but word isn't and is final state   -> continue recursion
  
  switch(value){
  case 7:{
    Computation c;
    c.current_word = new_string();
    c.current_stack = new_string();
    c.state = state;
    append_to_string(c.current_word, word);
    c.current_stack = get_string_from_stack(pda->stack);
    push_computation_stack(cs, c);
    return true;
  }
    //INTENTIONAL FALLTHROUGH
  case 6:
  case 5:
  case 4:{
    return false;
  }
  case 3:
  case 2:
  case 1:
  default:
    break;
  }

  bool is_it = false;
  for(size_t i = 0; i < pda->num_of_states; ++i){
    char to_consume = pda->states.transitions[state][i].consume;
    char to_unstack = pda->states.transitions[state][i].unstack;
    char current_stack_top = get_top_from_stack(pda->stack);
    if(word[0] == to_consume && current_stack_top == to_unstack){
      pop_stack(pda->stack);
      push_string_to_stack(pda->stack, pda->states.transitions[i]->stack);
      is_it = is_it || is_word_in_lang(pda, word + 1, i, cs);
      if(is_it) break;
    }
  }
  return is_it;
}

#endif
