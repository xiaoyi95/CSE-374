#ifndef HEADER_H
#define HEADER_H

struct TreeNode {
  struct TreeNode* position[8];
  struct CharList* word;
};

// Struct for the linked list that exists in each node
struct CharList {
  char* word;
  struct CharList* next;
};

struct TreeNode* newNode();
struct CharList* newString(char* word);
typedef struct TreeNode TreeNode;
typedef struct CharList CharList;
void freethem(TreeNode* node);
void freeString(CharList* string);

#endif
