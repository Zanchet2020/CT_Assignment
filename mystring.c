#include "mystring.h"

String * new_string(){
  String * str = (String*)malloc(sizeof(String));
  str->count = 0;
  str->capacity = STRING_INIT_SIZE;
  str->text = (char*) malloc(str->capacity * sizeof(char));
  str->text[0] = '\0';
  return str;
}

void append_to_string(String* str, char * txt){
  for(size_t i = 0; txt[i] != '\0'; ++i){
    if(str->count + 1 >= str->capacity){
      str->capacity += STRING_INIT_SIZE;
      str->text = (char*)realloc(str->text, str->capacity * sizeof(char));
    }
    str->text[str->count++] = txt[i];
    str->text[str->count] = '\0';
  }
}

void free_string(String * str){
  free(str->text);
  free(str);
}
