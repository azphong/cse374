/* trie implements a trie, made of trieNodes. This includes
   code to build, search, and delete a trie
   Aaron Hong, 5/17/23
   CSE374, HW5, 22wi 
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "trienode.h"

// creates and allocates memory for a new trieNode object with
// all NULL fields. returns a pointer to the new trieNode.
trieNode* makeNode();

// given one alphabetical character, return its corresponding t9 digit.
int toNum(char ch);

trieNode* makeNode() {
  trieNode* result = (trieNode*) malloc(sizeof(trieNode));
  if(result == NULL) {
    fprintf(stderr, "Memory allocation failed.");
    exit(1);
  }
  result -> word = NULL;
  for(int i = 0; i < BRANCHES; i++) {
    result -> branches[i] = NULL;
  }
  return result;
}

int toNum(char ch) {
  char codes[26] = {2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5, 6, 6, 6, 
    7, 7, 7, 7, 8, 8, 8, 9, 9, 9, 9};
  return codes[(int)(ch - 'a')];
}

trieNode* build_tree(FILE *dict) {
  char word[MAXLEN];
  char* temp;
  int branch_index;
  int length;
  trieNode* root;
  trieNode* curr;

  if(dict == NULL) { 
    fprintf(stderr, "Dictionary not found.");
    exit(1);
  }
  root = makeNode();
  while(fgets(word, MAXLEN, dict)) {
    length = strlen(word);
    curr = root;
    while(isalpha(word[length - 1]) == 0) { length--; } // trim non-alphabet chars 
    temp = (char*) malloc(length + 1); // (extra byte for null char)
    if(temp == NULL) { 
      fprintf(stderr, "Memory allocation failed.");
      exit(1); 
    }
    strncpy(temp, word, length); // write word to memory
    temp[length] = '\0'; // set null char
    for(int i = 0; i < length; i++) {
      branch_index = toNum(word[i]) - BRANCH_OFFSET;
      if(curr -> branches[branch_index] == NULL) { 
        curr -> branches[branch_index] = makeNode(); 
      }
      curr = curr -> branches[branch_index];
    }
    while((curr -> word) != NULL) {
      if(curr -> branches[BRANCHES - 1] == NULL) { 
        curr -> branches[BRANCHES - 1] = makeNode(); 
      }
      curr = curr -> branches[BRANCHES - 1];
    }
    curr -> word = temp; // point trieNode to word
  }
  return root;
}

char* get_word(trieNode* root, char* pattern) {
  trieNode* result;
  char ch;
  int ch_int;

  result = root;
  for(int i = 0; i < strlen(pattern); i++) {
    ch = pattern[i];
    ch_int = atoi(&ch); 
    if(ch_int >= 2 && ch_int <= 9) {
      if(result -> branches[ch_int - BRANCH_OFFSET] == NULL) {
        return "Not found in current dictionary.";
      }
      result = result -> branches[ch_int - BRANCH_OFFSET];
    } else if(ch == '#') {
      if(result -> branches[BRANCHES - 1] == NULL) { 
        return "There are no more T9onyms."; 
      } else {
        result = result -> branches[BRANCHES - 1];
      }
    } else {
      return "Illegal input character.";
    }
  }
  if(result -> word == NULL) {
    return "Not found in current dictionary.";
  }
  return result -> word;
}

void free_tree(trieNode* root) {
  for(int i = 0; i < BRANCHES; i++) {
    if(root -> branches[i] != NULL) {
      free_tree(root -> branches[i]);
    }
  }
  free(root -> word);
  free(root); 
}
