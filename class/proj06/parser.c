#include <stdio.h>

// Parser module
//
// Parses input into instructions and instructions into fields
//
// E.g., if we have @17 or @sum it returns the string "17" or "sum"
// E.g., if we have D=D+1;JLE the calls to dest(), comp() and jump() return D,
// D+1, and JLE

// Example File:

// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/06/add/Add.asm

// Computes R0 = 2 + 3  (R0 refers to RAM[0])

// @2
// D=A
// @3
// D=D+A
// @0
// M=D


int hasMoreLines();
void advance();
void instrucntion_type();
char *symbol();
char *dest();
char *comp(); 
char *jump();

enum INSTRUCTIONS { A_INSTRUCTION, C_INSTRUNCTION, L_INSTRUCTION };

// General Logic:
// Open a file 
// Iterate over all the lines of code in the file
// Read each instruction; return the type of symbol



int main(int argc, char *argv[]) {
  // Load file
  if (argc < 1) {
    printf("No file provided.");
    return 1;
  }
  char *file_name = argv[1];
  FILE *file = fopen(file_name,"r");
  char line[1024];
  while (fgets(line, sizeof(line), file)) {
    printf("%s", line);
  }
  fclose(file);
  return 0;
}
