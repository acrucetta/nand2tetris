#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define LINE_LENGTH 1024

void remove_whitespace_and_comments(FILE *file, char *buffer,
                                    size_t buffer_size) {
  int ch, next_ch;
  bool in_block_comment = false;
  size_t i = 0;

  while ((ch = fgetc(file)) != EOF && i < buffer_size - 1) {
    if (in_block_comment) {
      if (ch == '*' && (next_ch = fgetc(file)) == '/') {
        in_block_comment = false;
      }
      continue;
    }

    if (ch == '/') {
      next_ch = fgetc(file);
      if (next_ch == '*') {
        in_block_comment = true;
        continue;
      } else if (next_ch == '/') {
        // Skip the rest of the line for line comment
        while ((ch = fgetc(file)) != '\n' && ch != EOF) {
        }
        continue;
      } else {
        // If it's not a comment, put back the next character and fall through
        ungetc(next_ch, file);
      }
    }

    if (ch != ' ' && ch != '\t' && ch != '\r') {
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
  fclose(file);
  return buffer;
}
