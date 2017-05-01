#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "header.h"

// make the tree for the words from dictionary
// the node contains a word and maximum 8 other nodes
struct TreeNode* newNode() {
  struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
  if (node == NULL) {
    printf("System error");
    exit(1);
  } else {
    node->word = NULL;
    for (int i = 0; i < 8; i++) {
      node->position[i] = NULL;
    }
  return node;
  }
}

// Make the list for the words in a certain node
// next points to the next word
// word contains the word in this position
struct CharList* newString(char* word) {
  struct CharList* string =  (struct CharList*)malloc(sizeof(struct CharList));
  string->word = (char*)malloc(sizeof(char*)*strlen(word));
  if (string == NULL || string->word == NULL) {
    printf("System error");
  exit(1);
  } else {
    strncpy(string->word, word, strlen(word));
    string->word[strlen(word) - 1] = '\0';
    string->next = NULL;
    return string;
  }
}

// free the entire tree
void freethem(TreeNode* node) {
  for (int i = 0; i < 8; i++) {
    if (node->position[i] != NULL) {
      freethem(node->position[i]);
    }
  }
  if (node->word != NULL) {
    free(node->word);
  }
  free(node);
}

// free the list of word in a node
// be called by freethem
void freeString(CharList* string) {
  if (string->next != NULL) {
    freeString(string->next);
  }
  free(string->word);
  free(string);
}
