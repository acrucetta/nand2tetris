#include <stdio.h>
#include <stdlib.h>

// Parser module
//
// Parses input into instructions and instructions into fields
//
// E.g., if we have @17 or @sum it returns the string "17" or "sum"
// E.g., if we have D=D+1;JLE the calls to dest(), comp() and jump() return D,
// D+1, and JLE

int hasMoreLines();
void advance();
void instrucntion_type();
char *symbol();
char *dest();
char *comp();
char *jump();

enum INSTRUCTIONS { A_INSTRUCTION, C_INSTRUNCTION, L_INSTRUCTION };


