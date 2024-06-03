#ifndef PDA_H_
#define PDA_H_

#include <stdbool.h>
#include <stddef.h>
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
  Transition * tran;
  size_t count;
  size_t capacity;
} Transition_Array;

typedef struct {
  Transition_Array *** transitions;
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

typedef struct {
  Stack * stack;
  Graph states;
  size_t num_of_states;
  //  Node * history;
} PDA;


Transition_Array * new_transition_array();

void push_transition_array(Transition_Array *, Transition );

void free_transition_array(Transition_Array* );

Comp_Stack * new_computation_stack();

void push_computation_stack(Comp_Stack *, Computation );

Computation pop_computation_stack(Comp_Stack *);

void free_computation_stack(Comp_Stack *);

bool is_computation_stack_empty(Comp_Stack *);

PDA * new_pda(size_t);

void free_pda(PDA *);

bool is_word_in_lang(PDA *, char *, size_t, Comp_Stack *, int);



#endif
