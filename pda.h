#ifndef PDA_H_
#define PDA_H_

#include <stdbool.h>
#include <stdlib.h>

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

bool is_word_in_lang(PDA * pda, char * word){
  size_t current_letter_index = 0, current_state = 0;

  
  
  for(size_t i = 0; i < pda->num_of_states; ++i){
    char to_consume = pda->states.transitions[current_state][i].consume;
    char to_unstack = pda->states.transitions[current_state][i].unstack;
    char current_stack_top = get_top_from_stack(pda->stack);

    
    
  }
  return false;
}

#endif
