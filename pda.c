#include "pda.h"
#include "stack.h"

Transition_Array * new_transition_array(){
  Transition_Array * nts = (Transition_Array*) malloc(sizeof(Transition_Array));
  nts->capacity = 0;
  nts->count = 0;
  nts->tran = NULL;
  return nts;
}

void push_transition_array(Transition_Array *ts, Transition t) {
  if(ts->count >= ts->capacity){
    ts->capacity += STACK_INIT_SIZE;
    ts->tran = (Transition*)realloc(ts->tran, ts->capacity * sizeof(Transition));
  }
  ts->tran[ts->count++] = t;
}

void free_transition_array(Transition_Array* ts){
  for(size_t i = 0; i < ts->count; ++i){
    free_string(ts->tran[i].stack);
  }
  free(ts->tran);
  free(ts);
}

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

PDA * new_pda(size_t number_of_states){
  size_t Q = number_of_states;
  PDA * pda = (PDA*)malloc(sizeof(*pda));
  pda->num_of_states = Q;

  pda->stack = new_stack();
  push_stack(pda->stack, 'Z'); 

  pda->states.transitions = (Transition_Array***) malloc(Q*sizeof(Transition_Array**));
  pda->states.is_final_state = (bool*) malloc(Q*sizeof(bool));
  for(size_t i = 0; i < Q; ++i){
    pda->states.transitions[i] = (Transition_Array**) malloc(Q*sizeof(Transition_Array*));
    pda->states.is_final_state[i] = false;
    for(size_t j = 0; j < Q; ++j){
      pda->states.transitions[i][j] = new_transition_array();
    }
  }
  return pda;
}

void free_pda(PDA * pda){
  for(size_t i = 0; i < pda->num_of_states; ++i){
    for(size_t j = 0; j < pda->num_of_states; ++j){
      free_transition_array(pda->states.transitions[i][j]);
    }
    free(pda->states.transitions[i]);
  }
  free(pda->states.is_final_state);
  free(pda->states.transitions);
  free_stack(pda->stack);
  free(pda);
}

bool is_word_in_lang(PDA * pda, char * word, size_t state, Comp_Stack * cs){

  //word is in language                                -> return true and save computation
  //word empty but stack isn't empty                   -> false and don't save computation
  //word n stack empty but didn't reach final state    -> false and don't save computation
  //word empty but stack not and isn't final state     -> false and don't save computation
  //word isn't empty                                   -> continue recursion
  //final state but word and stack aren't empty        -> continue recursion
  //stack is empty but word isn't and is final state   -> continue recursion
  //nothing is done                                    -> continue recursion
  if(
     word[0]=='\0' &&
     pda->states.is_final_state[state] &&
     is_empty_stack(pda->stack)
      ){
    Computation c;
    c.current_word = new_string();
    c.state = state;
    c.current_stack = new_string();
    if(word[0] == '\0') append_to_string(c.current_word, (char*)"&");
    else append_to_string(c.current_word, word);
    append_to_string(c.current_stack, (char*)"Z");
    String * temp = get_string_from_stack(pda->stack);
    append_to_string(c.current_stack, temp->text);
    free_string(temp);
    push_computation_stack(cs, c);
    return true;
  }

  bool is_it = false;
  String * stack_image = get_string_from_stack(pda->stack);
  for(size_t i = 0; i < pda->num_of_states; ++i){
    Transition_Array * ta = pda->states.transitions[state][i];
    for(size_t j = 0; j < ta->count; ++j){
      
      Transition t = ta->tran[j];
      char to_consume = t.consume;
      char to_unstack = t.unstack;
      const String * to_stack = t.stack;
      char current_stack_top = get_top_from_stack(pda->stack);
      if(to_consume == '&' && to_unstack == '&'){
	push_string_to_stack(pda->stack, to_stack);
	is_it = is_it || is_word_in_lang(pda, word, i, cs); //dont add 1 to word
      } else if(to_consume == '&' && to_unstack == current_stack_top){
	pop_stack(pda->stack);
	push_string_to_stack(pda->stack, to_stack);
	is_it = is_it || is_word_in_lang(pda, word, i, cs); // dont add 1 to word
      } else if(to_consume == word[0] && to_unstack == '&'){
	push_string_to_stack(pda->stack, to_stack);
	is_it = is_it || is_word_in_lang(pda, word + 1, i, cs);
      } else if(to_consume == word[0] && current_stack_top == to_unstack){
	pop_stack(pda->stack);
	push_string_to_stack(pda->stack, to_stack);
	is_it = is_it || is_word_in_lang(pda, word + 1, i, cs);
      }
      if (is_it) {
        Computation c;
        c.current_word = new_string();
	c.current_stack = new_string();
        c.state = state;
        if (word[0] == '\0')
          append_to_string(c.current_word, (char *)"&");
        else
          append_to_string(c.current_word, word);
	append_to_string(c.current_stack, (char*)"Z");
	append_to_string(c.current_stack, stack_image->text);
	//        c.current_stack = get_string_from_stack(stack_image);
        push_computation_stack(cs, c);
	free_string(stack_image);
	return true;
      }
      //      free_string(stack_image);
    }
  }
  clear_stack(pda->stack);
  push_string_to_stack(pda->stack, stack_image);
  free_string(stack_image);
  return is_it;
}
