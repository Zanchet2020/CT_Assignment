#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "stack.h"
#include "mystring.h"
#include "pda.h"

int main(){
  size_t Q = 0, T = 0;
  scanf("%zu %zu", &Q, &T);
  PDA * lang = new_pda(Q);
  
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
    lang->states.transitions[from_state][to_state] = t;
  }

  size_t num_of_final_states = 0;
  scanf("%zu", &num_of_final_states);
  for(size_t i = 0; i < num_of_final_states; ++i){
    size_t index;
    scanf("%zu", &index);
    lang->states.is_final_state[index] = true;
  }

  Comp_Stack * cs = new_computation_stack();
  while(true){
    char input_buff[500];
    scanf("%s", input_buff);
    if(input_buff[0] == '*') break;

    if(is_word_in_lang(lang, input_buff, 0, cs)){
      printf("%s: sim\n", input_buff);
      for(size_t i = 0; !is_computation_stack_empty(cs); ++i){
	printf("(q%d, %s, %s) |-\n", cs->c[i].state, cs->c[i].current_word, cs->c[i].current_stack);
      }
    }
  }

  
  
  free_pda(lang);
  //  printf("Hello\n");
  return 0;
}
