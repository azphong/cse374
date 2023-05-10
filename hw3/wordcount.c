// Copyright 2023 <Aaron Hong>
// This program counts words, lines, and characters in the given files.
// It takes the options -w, -l, and -c to filter output.
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXLINE 500

void process_file(FILE* fp, char *opt, char *filename, int *total_lines);

int main(int argc, char *argv[]) {
  char *opt;
  int argstart, total_lines;
  total_lines = 0;
  if (argc < 2) {
    fprintf(stderr, "Usage: %s requires an input file.\n", argv[0]);
    return 1;
  }
  if (strcmp(argv[1], "-l")==0 ||
      strcmp(argv[1], "-w")==0 ||
      strcmp(argv[1], "-c")==0) {
    opt = argv[1];
    argstart = 2;
    if (argc == 2) {
      fprintf(stderr, "Usage: %s requires an input file.\n", argv[0]);
      return 1;
    }
  } else {
    opt = " ";
    argstart = 1;
  }
  for (int i = argstart; i < argc; i++) {
    FILE* fp = fopen(argv[i], "r");
    process_file(fp, opt, argv[i], &total_lines);
  }
  if (argstart == 1) {
    printf("Total Lines = %d\n", total_lines);
  }
  return 0;
}

// This method counts words, lines, and characters in one file and outputs
// the appropriate output for the given option.
void process_file(FILE* fp, char *opt, char *filename, int *total_lines) {
  int l, w, c;
  char text[MAXLINE];
  char ch;
  bool in_word = false;
  l = 0;
  w = 0;
  c = 0;
  if (fp != NULL) {
    while (fgets(text, MAXLINE, fp)) {
      l++;
      for (int i = 0; i < strlen(text); i++) {
        ch = text[i];
        if ((ch == ' ' || ch == '\n') && in_word) {
          w++;
          in_word = false;
        }
        if (ch != ' ' && ch != '\n') {
          in_word = true;
        }
      c++;
      }
    }
    switch (opt[1]) {
      case 'l':
        printf("%d\n", l);
        break;
      case 'w':
        printf("%d\n", w);
        break;
      case 'c':
        printf("%d\n", c);
        break;
      default:
        printf("%d %d %d %s\n", l, w, c, filename);
    }
  } else {
    fprintf(stderr, "%s will not open. Skipping.\n", filename);
  }
  *total_lines += l;
}
