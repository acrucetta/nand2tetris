// Translates Hack assembly language mnemonics into binary codes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char *binary_dest(char *mnmemonic) {
    if (strcmp(mnmemonic, "M") == 0) {
        return "001";
    } else if (strcmp(mnmemonic, "D") == 0) {
        return "010";
    } else if (strcmp(mnmemonic, "MD") == 0) {
        return "011";
    } else if (strcmp(mnmemonic, "A") == 0) {
        return "100";
    } else if (strcmp(mnmemonic, "AM") == 0) {
        return "101";
    } else if (strcmp(mnmemonic, "AD") == 0) {
        return "110";
    } else if (strcmp(mnmemonic, "AMD") == 0) {
        return "111";
    } else {
        return "000";
    }
}

char *binary_comp(char *mnmemonic) {
    if (strcmp(mnmemonic, "0") == 0) {
        return "0101010";
    } else if (strcmp(mnmemonic, "1") == 0) {
        return "0111111";
    } else if (strcmp(mnmemonic, "-1") == 0) {
        return "0111010";
    } else if (strcmp(mnmemonic, "D") == 0) {
        return "0001100";
    } else if (strcmp(mnmemonic, "A") == 0) {
        return "0110000";
    } else if (strcmp(mnmemonic, "!D") == 0) {
        return "0001101";
    } else if (strcmp(mnmemonic, "!A") == 0) {
        return "0110001";
    } else if (strcmp(mnmemonic, "-D") == 0) {
        return "0001111";
    } else if (strcmp(mnmemonic, "-A") == 0) {
        return "0110011";
    } else if (strcmp(mnmemonic, "D+1") == 0) {
        return "0011111";
    } else if (strcmp(mnmemonic, "A+1") == 0) {
        return "0110111";
    } else if (strcmp(mnmemonic, "D-1") == 0) {
        return "0001110";
    } else if (strcmp(mnmemonic, "A-1") == 0) {
        return "0110010";
    } else if (strcmp(mnmemonic, "D+A") == 0) {
        return "0000010";
    } else if (strcmp(mnmemonic, "D-A") == 0) {
        return "0010011";
    } else if (strcmp(mnmemonic, "A-D") == 0) {
        return "0000111";
    } else if (strcmp(mnmemonic, "D&A") == 0) {
        return "0000000";
    } else if (strcmp(mnmemonic, "D|A") == 0) {
        return "0010101";
    } else if (strcmp(mnmemonic, "M") == 0) {
        return "1110000";
    } else if (strcmp(mnmemonic, "!M") == 0) {
        return "1110001";
    } else if (strcmp(mnmemonic, "-M") == 0) {
        return "1110011";
    } else if (strcmp(mnmemonic, "M+1") == 0) {
        return "1110111";
    } else if (strcmp(mnmemonic, "M-1") == 0) {
        return "1110010";
    } else if (strcmp(mnmemonic, "D+M") == 0) {
        return "1000010";
    } else if (strcmp(mnmemonic, "D-M") == 0) {
        return "1010011";
    } else if (strcmp(mnmemonic, "M-D") == 0) {
        return "1000111";
    } else if (strcmp(mnmemonic, "D&M") == 0) {
        return "1000000";
    } else if (strcmp(mnmemonic, "D|M") == 0) {
        return "1010101";
    } else {
        return "0000000";
    }
}

char *binary_jump(char *mnmemonic) {
    if (strcmp(mnmemonic, "JGT") == 0) {
        return "001";
    } else if (strcmp(mnmemonic, "JEQ") == 0) {
        return "010";
    } else if (strcmp(mnmemonic, "JGE") == 0) {
        return "011";
    } else if (strcmp(mnmemonic, "JLT") == 0) {
        return "100";
    } else if (strcmp(mnmemonic, "JNE") == 0) {
        return "101";
    } else if (strcmp(mnmemonic, "JLE") == 0) {
        return "110";
    } else if (strcmp(mnmemonic, "JMP") == 0) {
        return "111";
    } else {
        return "000";
    }
}