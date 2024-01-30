#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Program
//
// The program assumes the assembly code contains no symbolic references.
// It gets the name of the input source file from the cl argument. It
// consturcts a Parser for parsing the input file "Prog.asm" and
// creates and output file Prog.hack with the binary instructions.:wq

// First pass:
// 1. Clear out white space
// 2. Remove comments
//
// Second pass:
// 1. Find labels
// 2. Parse for "(" label name ")"
// 3. Put in symbol table with the addess of line number (for jumping the PC)
// Remove line; this will affect subsequeny symbols
//
// Third pass:
// Translate each line
// - If C instruction do some lookups (dest, comp, jump)
// - If @xx, where xx is a number, simple
// - If the line is @xx where xx is a symbol, look it up in the symbol table
//      - If found, replace with the numeric meaning and complete
//      - If the symbol is not found; its a new variable. Add the pair <xxx,n>
//      to the symbol table.
// - Write code to machine language

#define LINE_LENGTH 1024

void remove_whitespace_and_comments(FILE *file, char *buffer,
                                    size_t buffer_size) {
  int ch;
  bool is_comment = false;
  size_t i = 0;

  while ((ch = fgetc(file)) != EOF && i < buffer_size - 1) {
    if (is_comment) {
      if (ch == '*' && (ch = fgetc(file)) == '/') {
        is_comment = false;
      }
      continue;
    }

    switch (ch) {
    case '/':
      if ((ch = fgetc(file)) == '*') {
        is_comment = true;
        continue;
      } else if (ch == '/') {
        while ((ch = fgetc(file)) != '\n' && ch != EOF)
          ;
      }
      break;
    case ' ':
    case '\t':
    case '\r':
      // Skip whitespace
      continue;
    default:
      buffer[i++] = ch;
    }
  }
  buffer[i] = '\0';
}

char *clean_file(const char *filename) {
  FILE *file = fopen(filename, "r");
  if (!file) {
    perror("Error opening file");
    return NULL;
  }

  size_t buffer_size = 1024;
  char *buffer = malloc(buffer_size);
  if (!buffer) {
    perror("Memory allocation failed");
    fclose(file);
    return EXIT_FAILURE;
  }
  remove_whitespace_and_comments(file, buffer, buffer_size);
  printf("%s\n", buffer);

  return "abc";
}

int main(int argc, char *argv[]) {
  // Load file
  if (argc < 1) {
    printf("No file provided.");
    return 1;
  }
  char *file_name = argv[1];
  char *cleansed_file = clean_file(file_name);
}
