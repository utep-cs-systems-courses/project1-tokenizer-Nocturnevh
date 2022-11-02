#include <stdio.h>
#include <stdlib.h>
#include "tokenizer.h"
#include "history.h"

#define MAX 100

List* init_history(){
  List* history = (List*) malloc (sizeof(List));
  history -> root = NULL;
  return history;
}

void add_history(List *list, char *str){
  Item* newItem = (Item*) malloc (sizeof (Item));
  newItem -> str = copy_str (str, MAX);
  newItem -> next = NULL;

  if (!list -> root){
  newItem -> id = 0;
  list -> root = newItem;
  }
  else{
    Item* curr_node = list -> root;

    while (curr_node -> next){
      curr_node = curr_node -> next;
    }
    curr_node -> next = newItem;
    newItem -> id = curr_node -> id+1;
  }
}

char *get_history (List *list, int id){
  if (id >= 0){
    Item *curr_node = list -> root;
    while (curr_node && (curr_node -> id < id)){
      curr_node = curr_node -> next;
    }
    if (curr_node){
      return curr_node -> str;
    }
    return "\0";
  }
}

void print_history (List *list) {
  if (list -> root){
    Item* curr_node = list -> root;
    while (curr_node){
      printf ("%d\n", curr_node -> id);
      printf ("%s\n", curr_node -> str);
      curr_node = curr_node -> next;
    }
  }
}

void free_history (List *list){
  Item *curr_node =  list -> root;
  Item *next_node;
  while (curr_node){
    next_node = curr_node -> next;
    free (curr_node);
    curr_node = next_node;
  }
  free (list);
}
