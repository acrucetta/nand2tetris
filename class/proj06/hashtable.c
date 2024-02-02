#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define MAX_KEY 256
#define TABLE_SIZE 20
#define DELETED_NODE (item *)(0xFFFFFFFFFFFFFFFFUL)

typedef struct {
  char key[MAX_KEY];
  char *value;
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
      printf("\t%i\t%s\n", i, hash_table[i]->value);
    }
  }
}

bool hash_table_insert(item *p) {
  if (p == NULL) {
    return false;
  }
  int index = hash(p->value);
  for (int i = 0; i < TABLE_SIZE; i++) {
    int try = (i + index) % TABLE_SIZE;
    if (hash_table[try] == NULL || hash_table[try] == DELETED_NODE) {
      hash_table[try] = p;
      return true;
    }
  }
  return false;
}

item *hash_table_get(char *key) {
  int index = hash(key);
  for (int i = 0; i < TABLE_SIZE; i++) {
    int try = (i + index) % TABLE_SIZE;
    if (hash_table[try] == NULL) {
      return false;
    }
    if (hash_table[try] == DELETED_NODE)
      continue;
    if (strcmp(hash_table[try]->key, key) == 0) {
      return hash_table[try];
    }
  }
  return NULL;
}

item *hash_table_remove(char *key) {
  unsigned int index = hash(key);
  for (int i = 0; i < TABLE_SIZE; i++) {
    int try = (i + index) % TABLE_SIZE;
    if (hash_table[try] == NULL) {
      return false;
    }
    if (hash_table[try] == DELETED_NODE)
      continue;
    if (strcmp(hash_table[try]->key, key) == 0) {
      item *tmp = hash_table[try];
      hash_table[try] = DELETED_NODE;
      return tmp;
   }
  }
  return NULL;
}

int main() {
  hash_table_init();

  item jacob = {.key = "jacob", .value = "hairy"};
  item bob = {.key = "bob", .value = "hairy-ish"};
  item tom = {.key = "tom", .value = "not hairy"};

  hash_table_insert(&jacob);
  hash_table_insert(&tom);
  hash_table_insert(&bob);
  remove("jacob");

  item *tmp = hash_table_get("jacob");
  if (tmp == NULL) {
    printf("Not found\n");
  } else {
    printf("Found");
  }

  print_table();

  return 0;
}
