#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_KEY 256
#define TABLE_SIZE 10

typedef struct
{
  char key[MAX_KEY];
  char *value;
} item;

item *hash_table[TABLE_SIZE];

unsigned int hash(char *name)
{
  int length = strnlen(name, MAX_KEY);
  unsigned int hash_value = 0;
  for (int i = 0; i < length; i++)
  {
    hash_value += name[i];
    hash_value = (hash_value * name[i]) % TABLE_SIZE;
  }
  return hash_value;
}

void init_hash_table()
{
  for (int i = 0; i < TABLE_SIZE; i++)
  {
    hash_table[i] = NULL;
  }
}

void print_table()
{
  for (int i = 0; i < TABLE_SIZE; i++)
  {
    if (hash_table[i] == NULL)
    {
      printf("\t%i\t--\n", i);
    }
    else
    {
      printf("\t%i\t%s\n", i, hash_table[i]->value);
    }
  }
}

bool insert(item *p)
{
  if (p == NULL)
  {
    return false;
  }
  int index = hash(p->value);
  if (hash_table[index] != NULL)
  {
    return false;
  }
  hash_table[index] = p;
  return true;
}

/**
 * Retrieves an item from the hash table based on the given key.
 *
 * @param key The key of the item to retrieve.
 * @return A pointer to the item if found, or NULL if not found.
 */
item *get(char *key) {
  int index = hash(&key);
  if (hash_table[index] != NULL &&
    strcmp(hash_table[index]->key, key) == 0) {
      return hash_table[index];
    }
    else {
      return NULL;
    }
}

/**
 * Remoes an item from the hash table based on the given key.
 *
 * @param key The key of the item to retrieve.
 * @return A pointer to the item if found, or NULL if not found.
 */
item *remove(char *key) {
  int index = hash(&key);
  if (hash_table[index] != NULL &&
    strcmp(hash_table[index]->key, key) == 0) {
      item *tmp = hash_table[index];
      hash_table[index] = NULL;
      return tmp;
    }
    else {
      return NULL;
    }
}

int main()
{
  init_hash_table();
  print_table();

  item jacob = {.key = "jacob", .value = "hairy"};
  item bob = {.key = "bob", .value = "hairy-ish"};
  item tom = {.key = "tom", .value = "not hairy"};

  insert(&jacob);
  insert(&bob);
  insert(&tom);

  item *tmp = get("tom");
  if (tmp == NULL) {
    printf("Not found\n");
  } else {
    printf("Found");
  }

  print_table();

  return 0;
}
