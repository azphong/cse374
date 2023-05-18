/* tnine is a program that drives a trie / t9 program.  This code
   will build a trie, according to trienode. It will also run
   an interactive session where the user can retrieve words using
   t9 sequences.
   CSE374, HW5, 22wi 
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "trienode.h"

// run_session run the on-going decoding interaction with the
// user.  It requires a previously build wordTrie to work.
void run_session(trieNode *wordTrie);

int main(int argc, char **argv) {
  FILE *dictionary = NULL;
  trieNode *wordTrie = NULL;

  if (argc < 2) {
    fprintf(stderr, "Usage: %s [DICTIONARY]\n", argv[0]);
    return EXIT_FAILURE;
  } else {
    dictionary = fopen(argv[1], "r");
    if (!dictionary) {
      fprintf(stderr, "Error: Cannot open %s\n", argv[1]);
      return EXIT_FAILURE;
    }
  }

  // build the trie
  wordTrie = build_tree(dictionary);

  // run interactive session
  run_session(wordTrie);

  // clean up
  free_tree(wordTrie);
  
  return(EXIT_SUCCESS);
}

void run_session(trieNode* wordTrie) {
  char input[MAXLEN];
  char* prev_input = NULL;
  int length;
  printf("Enter \"exit\" to quit.\n");
  while(true) {
    printf("Enter Key Sequence (or \"#\" for next word):\n> ");
    if(scanf("%s", input) == EOF) { break; }
    length = strlen(input);
    if(strncmp(input, "exit", length) == 0) { break; }
    if(prev_input == NULL) {
      prev_input = (char*) malloc(length + 1);
      strncpy(prev_input, input, length);
      printf("%s\n", get_word(wordTrie, input));
    } else {
      if (strncmp(input, "#", length) == 0) {
        strncat(prev_input, input, length);
	strncpy(input, prev_input, strlen(prev_input - 1));
      } else {
	prev_input = NULL;
	prev_input = (char*) realloc(prev_input, length);
        strncpy(prev_input, input, length);
      }
      printf("%s\n", get_word(wordTrie, prev_input));
    }
  }
  if(prev_input != NULL) {
    free(prev_input);
  }
}



