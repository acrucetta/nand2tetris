#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_KEY 256
#define TABLE_SIZE 100

typedef struct {
  char key[MAX_KEY];
  char *value;
  struct item *next;
} item;

item *hash_table[TABLE_SIZE];

unsigned int hash(char *name) {
  unsigned hashval;
  for (hashval = 0; *name != '\0'; name++) {
    hashval = *name + 31 * hashval;
  }
  return hashval % TABLE_SIZE;
}

void hash_table_init() {
  for (int i = 0; i < TABLE_SIZE; i++) {
    hash_table[i] = NULL;
  }
}

void print_table() {
  for (int i = 0; i < TABLE_SIZE; i++) {
    if (hash_table[i] == NULL) {
      printf("\t%i\t--\n", i);
    } else {
      printf("\t%i\t ", i);
      item *tmp = hash_table[i];
      while (tmp != NULL) {
        printf("%s - ", tmp->key);
        tmp = tmp->next;
      }
      printf("\n");
    }
  }
}

bool hash_table_insert(char *key, char *value) {
  item *new_item = (item *)malloc(sizeof(item));
  if (new_item == NULL) {
    return false;
  }
  strncpy(new_item->key, key, MAX_KEY);
  new_item->value = strdup(value);
  if (new_item->value == NULL) {
    free(new_item);
    return false;
  }
  int idx = hash(new_item->key);
  new_item->next = hash_table[idx];
  hash_table[idx] = new_item;
  return true;
}

item *hash_table_get(char *key) {
  int idx = hash(key);
  item *tmp = hash_table[idx];
  while (tmp != NULL && strncmp(tmp->key, key, MAX_KEY) != 0) {
    tmp = tmp->next;
  }
  return tmp;
}

item *hash_table_remove(char *key) {
  int idx = hash(key);
  item *tmp = hash_table[idx];
  item *prev = NULL;
  while (tmp != NULL && strcmp(tmp->key, key) != 0) {
    prev = tmp;
    tmp = tmp->next;
  }
  if (tmp == NULL)
    return NULL;
  if (prev == NULL) {
    hash_table[idx] = tmp->next;
  } else {
    prev->next = tmp->next;
  }
  return tmp;
}
