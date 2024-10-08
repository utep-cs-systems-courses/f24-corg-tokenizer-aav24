#include <stdlib.h>
#include <stdio.h>
#include "history.h"

/* initialize linked list for history */
List* init_history(){

  List *list = (List *) malloc(sizeof(List));   /* allocates memory for list */
  list->root = NULL;    /* sets list root to null */
  return list;
}

void add_history(List *list, char *str){

  if(list == NULL || str == NULL){
    return;
  }
  // create a new item
  Item *new_item = (Item *) malloc(sizeof(Item));
  new_item->str = str;
  new_item->next = NULL;
  if(!list->root){    /* add item to root if root is empty */
    new_item->id = 1;
    list->root = new_item;
  }else{
    Item *current = list->root;
    int counter = 1;
    while(current->next){    /* traverse list until next item is empty */
      current = current->next;
      counter++;
    }
    // add the item as the next element in the list
    counter++;
    new_item->id = counter;
    current->next = new_item;
  }

}

// get a specified element in the list
char *get_history(List *list, int id){

  Item *current = list->root;
  while(current){
    if(current->id == id){
      return current->str;    /* returns the str pointer to string */
    }
    current = current->next;
  }
  return NULL;
}

// prints the elements in the list (history)
void print_history(List *list){
  Item *current = list->root;
  while (current){
    printf("%d %s\n",current->id, current->str);
    current = current->next;
  }
}

// frees all elements in list
void free_history(List *list){
  Item *current = list->root;
  while(current){
    Item *next = current->next;
    free(current->str);
    free(current);
    current = next;
  }
  free(list);
}
