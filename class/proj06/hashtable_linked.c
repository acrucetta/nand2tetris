#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define MAX_KEY 256
#define TABLE_SIZE 20

typedef struct {
  char key[MAX_KEY];
  char *value;
  struct item *next;
} item;

item *hash_table[TABLE_SIZE];

unsigned int hash(char *name) {
  int length = strnlen(name, MAX_KEY);
  unsigned int hash_value = 0;
  for (int i = 0; i < length; i++) {
    hash_value += name[i];
    hash_value = (hash_value * name[i]) % TABLE_SIZE;
  }
  return hash_value;
}

void init_hash_table() {
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
        printf("%s - ", hash_table[i]);
        tmp = tmp->next;
      }
      printf("\n");
    }
  }
}

bool hash_table_insert(item *p) {
  if (p == NULL) {
    return false;
  }
  int idx = hash(p->value);
  p -> next = hash_table[idx];
  hash_table[idx] = p;
  return true;
}

item *hash_table_get(char *key) {
  int idx = hash(key);
  item *tmp = hash_table[idx];
  while (tmp != NULL && strcmp(tmp->key, key) != 0) {
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
  if (tmp == NULL) return NULL;
  if (prev == NULL) { 
    hash_table[idx] = tmp->next;
  } else {
    prev->next = tmp->next;
  }
  return tmp;
}

int main() {
  init_hash_table();

  item jacob = {.key = "jacob", .value = "hairy"};
  item bob = {.key = "bob", .value = "hairy-ish"};
  item tom = {.key = "tom", .value = "not hairy"};

  hash_table_insert(&jacob);
  hash_table_insert(&tom);
  hash_table_insert(&bob);

  print_table();

  return 0;
}
