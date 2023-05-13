/* trie implements a trie, made of trieNodes. This includes
   code to build, search, and delete a trie
   CSE374, HW5, 22wi 
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "trienode.h"

/* You'll want to prototype any helper functions you need here */

trieNode* newNode(char* word);

int toNum(char ch);

/* You'll need to implement the functions declare in trienode.h */
/* As well as the helpfer functions you prototype above. */

trieNode* newNode() {
  trieNode* result = (trieNode*) malloc(sizeof(trieNode));
  result = { NULL, { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL } };
  return result;
}

int toNum(char ch) {
  char codes[26] = {2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5, 6, 6, 6, 
    7, 7, 7, 7, 8, 8, 8, 9, 9, 9, 9};
  return codes[(int)(ch - 'a')];
}

trieNode* build_tree(FILE *dict) {
  char word[MAXLEN];
  int code;
  *trieNode root;
  *trieNode curr;

  if(fp == NULL) { return NULL; }

  root = newNode();
  while(fgets(word, MAXLEN, fp)) {
    curr = root;
    for(int i = 0; i < strlen(word); i++) {
      code = toNum(word[i]);
      if(curr.branches[code - 2] == NULL) { curr.branches[code - 2] = newNode(); }
      curr = curr.branches[code - 2];
    }
    while(curr.word != NULL) {
      if(curr.branches[BRANCHES] == NULL) { curr.branches[BRANCHES] = newNode(); }
      curr = curr.branches[BRANCHES];
    }
    curr.word = word;
  }

  return root;
}

char* get_word(trieNode* root, char* pattern) {
  *trieNode result;
  result = root;
  for(int i = 0; i < strlen(pattern); i++) {
    if(result == NULL) {
      
    }
  }
}
