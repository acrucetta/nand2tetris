#include <stdbool.h>
#include <stdio.h>
#include "cleaner.h"
#include "parser.h"

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

int main(int argc, char *argv[]) {
  // Load file
  if (argc < 1) {
    printf("No file provided.");
    return 1;
  }
  char *file_name = argv[1];
  char *cleansed_file = clean_file(file_name);
  printf("%s",cleansed_file);
}
