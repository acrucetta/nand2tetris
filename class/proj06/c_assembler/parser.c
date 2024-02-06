#include "cleaner.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

enum INSTRUCTION { A_INSTRUCTION, C_INSTRUCTION, L_INSTRUCTION };

enum INSTRUCTION command_type(char *command) {
  if (command[0] == '@') {
    return A_INSTRUCTION;
  }
  if (strpbrk(command, "=;") != NULL) {
    return C_INSTRUCTION;
  }
  return L_INSTRUCTION;
}

char *get_symbol(char *command) {
  char *symbol = NULL;
  if (command[0] == '@') {
    return command + 1;
  } else if (command[0] == '(') {
    char *symbol = strdup(command);
    symbol++;
    symbol[strlen(symbol) - 1] = '\0';
    return symbol;
  }
  return command;
}

char *get_dest(char *command) {
  const char *equals = strchr(command, '=');
  if (equals) {
    size_t len = equals - command;
    char *dest = malloc(len-1);
    strncpy(dest, command, len);
    dest[len] = '\0';
    return dest;
  }
  return NULL;
}

char *get_jump(char *command) {
  const char *has_jump = strchr(command, ';');
  if (has_jump) {
    char *jump = strdup(has_jump + 1);
    return jump;
  }
  return NULL;
}

char *get_comp(char *command) {
  const char *equals = strchr(command, '=');
  const char *semicolon = strchr(command, ';');
  if (equals) {
    char *comp = strdup(equals + 1);
    return comp;
  } else if (semicolon) {
    char *comp = malloc(semicolon - command);
    strncpy(comp, command, semicolon - command);
    comp[semicolon - command] = '\0';
    return comp;
  }
  return NULL;
}

