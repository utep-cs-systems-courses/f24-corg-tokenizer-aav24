#include <stdio.h>
#include <stdlib.h>
#include "src/tokenizer.h"
#include "src/history.h"

// used to look for 'exit' or 'history' command
int compare(char *str1, char *str2){

  int i = 0;
  while (str1[i] !='\0'){
    if (str1[i] == str2[i]){
      i++;
    }
    if (str1[i] > str2[i]){
      return 1;
    }
    if (str1[i] < str2[i]){
      return -1;
    }
  }
  return 0; /* both strings are equal */
}

int len(char *str){
  int length = 0;
  while (str[length] != '\0'){
    length++;
  }
  return length;
}
/* removes newline after fgets() in order to
   allow for comparison to exit command */
void remove_newline(char *str){

  int length = len(str);
  while (length > 0 && str[length-1] == '\n'){
    str[length-1] = '\0';
  }
}


int main()
{
  puts("Welcome to the tokenizer ui! enter 'exit' to quit");
  List *history = init_history();
  
  while(1){
    // obtain input
    char input[40];
    printf("\n$ ");
    fgets(input, 40, stdin);

    // check for exit
    remove_newline(input);
    if(compare(input, "exit") == 0){
      goto done;
    }
    if(compare(input, "history") == 0){
      printf("\nhistory: \n");
      print_history(history);
      continue;
    }
    
    // check for history commands
    if(input[0] == '!'){
      char *ptr = input;
      ptr++;
      int id = atoi(ptr);     /* convert number after ! */
      if (id == 0){
	printf("Invalid Input!");
	continue;
      }
      char *hist_item = get_history(history, id);     /* get item from history list */
      if (hist_item == NULL){    /* null if failed to retrieve */
	printf("There is no history at %d\n", id);
	continue;
      }
      printf("Token at %d: ", id);
      printf(" %s\n", hist_item);
      continue;
    }

    // tokenize input and print tokens
    char **tokens = tokenize(input);
    print_tokens(tokens);
    // add tokens to history
    for (int i = 0; tokens[i] != NULL; i++){
      add_history(history, copy_str(tokens[i],len(tokens[i])));
    }
    free_tokens(tokens);

  }

  
 done:
  free_history(history);
  printf("See you later!");
  return 0;

}
