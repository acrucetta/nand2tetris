#include <stdbool.h>

// Enums
typedef struct {
  char *key;
  int *value;
} item;

// Hash table operations
void print_table();
bool hash_table_insert(char *key, char *value);
item *hash_table_get(char *key);
item *hash_table_remove(char *key);
void hash_table_init();
