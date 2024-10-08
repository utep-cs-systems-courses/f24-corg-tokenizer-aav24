#include <stdlib.h>
#include "tokenizer.h"
#include "stdio.h"


/* Return true if c is a whitespace character */
int space_char(char c){

  return (c == ' ' || c == '\t');

}

/* Return true if c is a non-whitespace character (tab or space) */
int non_space_char(char c){

  if(c == ' ' || c == '\t'){
    return 0;
  }else{
    return 1;
  }
}

/* Returns a pointer to the first character of the next
   space-seperated token */
char *token_start(char *str){

  if (str == 0){
    return 0;
  }
  while (space_char(*str)){
    str++;    /* move the pointer to the next char in string */
  }
  // returns 0 if we reach end of string
  if (*str == '\0'){
    return 0;
  }
  return str;    /* returns a pointer now pointing to the first char in a token */

}

/* Returns a pointer terminator char following *token */
char *token_terminator(char *token){

  while (*token != '\0' && non_space_char(*token)){
    token++;    /* increment token pointer */
  }
  return token;    /* returns the position of the token terminator */
}

/* Counts the number of tokens in the string argument */
int count_tokens(char *str){

  int counter = 0;
  char *token = token_start(str);

  while (token){
    counter++;    /* increment number of tokens */
    char *end = token_terminator(token);
    token = token_start(end);    /* update pointer to the next token */
  }
  return counter;
}

/* Returns a freshly allocated new zero-terminated string
   containing <len> chars from <inStr> */
char *copy_str(char *inStr, short len){

  if (inStr == 0){
    return 0;
  }

  char *newStr =(char *) malloc(len+1);    /* allocates space for string + terminator */

  for (int i = 0; i < len; i++){
    newStr[i] = inStr[i];
  }
  newStr[len] = '\0';   /* sets last element as terminator */
    return newStr;
}


char **tokenize(char* str){

  int num_tokens = count_tokens(str);
  char **tokens = (char **) malloc(num_tokens + 1);    /* allocates space for tokens and 0 term.)*/
  
  char *token = token_start(str);    /* gets the beginning of first token */
  int i = 0;

  while (token){
    char *end = token_terminator(token);
    tokens[i] = copy_str(token, end - token);    /* copies and stores sub-string token */
    i++;
    token = token_start(end);
  }
  tokens[i] = 0;    /* ensures zero-terminated vector */
  return tokens;
}

// print all tokens
void print_tokens(char **tokens){

  for (int i = 0; tokens[i] != NULL; i++){
    printf("%s\n", tokens[i]);
  }
}

// free all tokens
void free_tokens(char **tokens){

  for (int i = 0; tokens[i] != NULL; i++){
    free(tokens[i]);
  }
  free(tokens);
}
