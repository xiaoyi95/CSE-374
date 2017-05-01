#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "header.h"
#define INPUT_MAX 100

void makeTree(TreeNode* root, FILE* file);
int charToint(char letter);
void searchWord(TreeNode* node);

int main(int argc, char* argv[]) {
  if (argc < 2) {
    fprintf(stderr, "Error: Need an input file\n");
    return 1;
  }
  TreeNode* overallRoot = newNode();
  FILE* input = fopen(argv[1], "r");
  if (input == NULL) {
    fprintf(stderr, "Error: File not found\n");
    return 1;
  }
  makeTree(overallRoot, input);
  printf("makeTree");
  fclose(input);
  printf("fclose");
  searchWord(overallRoot);
  printf("searchWord");
  freethem(overallRoot);
  printf("freethem");
  return 0;
}

void makeTree(TreeNode* root, FILE* file) {
  char line[INPUT_MAX];
  TreeNode* makeNode;
  while (fgets(line, INPUT_MAX, file) != NULL) {
    makeNode = root;
    for (int i = 0; i < strlen(line) - 1; i++) {
      int charNum = charToint(line[i]);
      if (makeNode->position[charNum] == NULL) {
        makeNode->position[charNum] = newNode();
      }
      makeNode = makeNode->position[charNum];
      if (i == strlen(line) - 2) {
        if (makeNode->word == NULL) {
          makeNode->word = newString(line);
        } else {
          CharList* word = makeNode-> word;
          while (word->next != NULL) {
            word = word->next;
          }
          word->next = newString(line);
        }
      }
    }
  }
}

int charToint(char letter) {
  if (letter == 'a'|| letter == 'b' || letter == 'c') {
    return 0;
  } else if (letter == 'd' || letter == 'e' || letter == 'f') {
    return 1;
  } else if (letter == 'g' || letter == 'h' || letter == 'i') {
    return 2;
  } else if (letter == 'j' || letter == 'k' || letter == 'l') {
    return 3;
  } else if (letter == 'm' || letter == 'n' || letter == 'o') {
    return 4;
  } else if (letter == 'p' || letter == 'q' || letter == 'r' || letter == 's') {
    return 5;
  } else if (letter == 't' || letter == 'u' || letter == 'v') {
    return 6;
  } else {
    return 7;
  }
}


void searchWord(TreeNode* node) {
  printf("Enter \"exit\" to quit.\n");
  printf("Enter Key Sequence (or \"#\" for next word):\n> ");
  char userInput[INPUT_MAX];
  TreeNode* search = node;
  CharList* word;
  while (fgets(userInput, INPUT_MAX, stdin)) {
    int end = 0;
    int pound = 0;
    if (strncmp("exit", userInput, 4) == 0) {
      break;
    }
    if (userInput[0] == '#') {
      if (word != NULL && word->next != NULL) {
        word = word->next;
        printf("        \'%s\'\n", word->word);
      } else {
        printf("        There are no more T9onyms\n\n");
        end = 1;
      }
    } else {
      search = node;
      for (int i = 0; i < strlen(userInput) - 1; i++) {
        if (end == 1) {
          break;
        }
        int num = !isdigit(userInput[i]) || userInput[i] < 50;
        if (num && userInput[i] != '#') {
          printf("        Integer 2-9 or \'#\' needed\n\n");
          end = 1;
        } else if (userInput[i] == '#') {
          if (pound == 0 && (search == NULL || search->word == NULL)) {
            printf("        Not found in current dictionary.\n\n");
            end = 1;
          }
          pound++;
        } else {
          if (search == NULL) {
            printf("        Not found in current dictionary.\n\n");
            end = 1;
          } else {
            int user = (int)userInput[i] - 50;
            search = search->position[user];
          }
        }
      }
      if (pound == 0 && end == 0 && search != NULL && search->word != NULL) {
        word = search->word;
        printf("        \'%s\'\n", search->word->word);
      } else if (end == 0 && (search == NULL || search->word == NULL)) {
        printf("        Not found in current dictionary.\n\n");
      } else if (end == 0 && pound != 0) {
        word = search->word;
        while (pound != 0 && end == 0) {
          word = word->next;
          pound--;
          if (word == NULL) {
            end = 1;
            printf("        There are no more T9onyms\n\n");
          }
        }
          if (pound == 0 && end == 0) {
            printf("        \'%s\'\n", word->word);
        }
      }
    }
  printf("Enter Key Sequence (or \"#\" for next word):\n> ");
  }
}

