#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "cleaner.h"
#include "parser.h"
#include "symbol.h"

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

int parse(char *buffer) {
  char *str_copy = strdup(buffer);
  char *line = strtok(str_copy, "\n");
  while (line != NULL) {
    enum INSTRUCTION instruction = command_type(line);
    switch (instruction) {
    case A_INSTRUCTION:
      printf("A_INSTRUCTION: %s\n", get_symbol(line));
      break;
    case C_INSTRUCTION:
      printf("C_INSTRUCTION: %s\n", line);
      printf("Dest: %s\n", get_dest(line));
      printf("Comp: %s\n", get_comp(line));
      printf("Jump: %s\n", get_jump(line));
      break;
    case L_INSTRUCTION:
      printf("L_INSTRUCTION: %s\n", line);
      break;
    }
    line = strtok(NULL, "\n");
  }
  return 1;
}

int main(int argc, char *argv[]) {
  // Load file
  if (argc < 2) {
    printf("No file provided.");
    return 1;
  }
  // char *file_name = argv[1];
  // char *cleansed_file = clean_file(file_name);
  symbol_table_init();
  int test = get_address("SP");
  printf("%d", test);
  // int* result = parse(cleansed_file);
}
