#ifndef MYSTRING_H_
#define  MYSTRING_H_

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

#endif
