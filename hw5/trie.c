/* trie implements a trie, made of trieNodes. This includes
   code to build, search, and delete a trie
   CSE374, HW5, 22wi 
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "trienode.h"

/* You'll want to prototype any helper functions you need here */

trieNode* newNode();

int toNum(char ch);

/* You'll need to implement the functions declare in trienode.h */
/* As well as the helpfer functions you prototype above. */

trieNode* newNode() {
  trieNode* result = (trieNode*) malloc(sizeof(trieNode));
  result -> word = NULL;
  result -> branches = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};
  return result;
}

int toNum(char ch) {
  char codes[26] = {2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5, 6, 6, 6, 
    7, 7, 7, 7, 8, 8, 8, 9, 9, 9, 9};
  return codes[(int)(ch - 'a')];
}

trieNode* build_tree(FILE *dict) {
  char word[MAXLEN];
  int branch_index;
  trieNode* root;
  trieNode* curr;

  if(dict == NULL) { return NULL; }

  root = newNode();
  while(fgets(word, MAXLEN, dict)) {
    curr = root;
    for(int i = 0; i < strlen(word); i++) {
      branch_index = toNum(word[i]) - BRANCH_OFFSET;
      if(curr -> branches[branch_index] == NULL) { curr -> branches[branch_index] = newNode(); }
      curr = curr -> branches[branch_index];
    }
    while(curr -> word != NULL) {
      if(curr -> branches[BRANCHES] == NULL) { curr -> branches[BRANCHES] = newNode(); }
      curr = curr -> branches[BRANCHES];
    }
    curr -> word = word;
  }

  return root;
}

char* get_word(trieNode* root, char* pattern) {
  trieNode* result;
  char ch;
  result = root;
  for(int i = 0; i < strlen(pattern); i++) {
    ch = pattern[i];
    if((int)(ch) >= BRANCH_OFFSET && (int)(ch) <= BRANCHES) {
      result = result -> branches[(int)(ch) - BRANCH_OFFSET];
      if(result == NULL) { return "Not found in current dictionary."; }
    } else if(ch == '#') {
      result = result -> branches[BRANCHES];
      if(result == NULL) { return "There are no more T9onyms."; }
    } else {
      return "Illegal input character: %c", ch;
    }
  }
  return result -> word;
}

void free_tree(trieNode* root) {
  
}
