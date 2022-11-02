#include <stdio.h>
#include <stdlib.h>
#include "tokenizer.h"

int space_char(char c){
  if(c=='\t' || c==' ' || c=='\n'){
    return 1;
  }
  return 0;
}

int non_space_char(char c){
  if(c != '\t' && c != ' ' && c != '\n' && c != '\0'){
    return 1;
  }
  return 0;
}

char *word_start(char *str){
  int i = 0;
  while(str[i] != '\0'){
    if(non_space_char(str[i])){
      return &str[i];
    }
    i++;
  }
  return "\0";
}

char *word_terminator(char *word){
  int i =0;
  while(non_space_char(word[i])){
    i++;
  }
  if(word[i] == '\0'){
    return "\0";
  }
  i--;
  return &word[i];
}

int count_words(char *str){
  int r = 0;
  int i = 0;
  while(str[i] != '\0'){
    if(non_space_char(str[i]) && (space_char(str[i+1]) || (str[i+1] == '\0'))){
      r++;
    }
    i++;
  }
  return r;
}

char *copy_str(char *inStr, short len){
  char* newStr = (char*) malloc ((len+1) * sizeof(char));
  int i = 0;
  while(i < len){
    newStr[i] = inStr[i];
    i++;
  }
  newStr[len] = '\0';
  return newStr;
}

char **tokenize(char* str){
  char** tokens = (char**) malloc ((count_words(str)+1) * sizeof (char*));
  int i = 0;
  while(count_words(str)){
    if(space_char(str[0])){
      str = word_start(word_terminator(str)+1);
    }
    int test = *word_terminator(str) + 1 - *word_start(str);
    tokens[i] = copy_str(str, word_terminator(str) + 1 - word_start(str));
    str = word_start(word_terminator(str)+1);
    i++;
  }
  tokens[i] = "\0";
  return tokens;
}

void print_tokens(char **tokens){
  int i = 0;
  while(*tokens[i] != '\0'){
    printf("%s\n", tokens[i]);
    i++;
  }
}

void free_tokens(char **tokens){
  int i = 0;
  while(*tokens[i] != '\0'){
    free(tokens[i]);
    i++;
  }
  free(tokens);
}
