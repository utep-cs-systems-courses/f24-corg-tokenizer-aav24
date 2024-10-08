#include <stdio.h>
#include <stdlib.h>
#include "src/tokenizer.h"
#include "src/history.h"


int main()
{
  puts("Welcome to the tokenizer ui!");
  List *history = init_history();
  
  while(1){

    char input[20];
    printf("$ ");
    fgets(input, 20, stdin);
    
    printf("%s", input);

    goto done;
  }

  
 done:
  free_history(history);
  return 0;

}
