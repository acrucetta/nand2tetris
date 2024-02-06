#include "hashtable_linked.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void symbol_table_init()
{
    hash_table_init();

    // Add predefined symbols
    hash_table_insert("SP", "0");
    hash_table_insert("LCL", "1");
    hash_table_insert("ARG", "2");
    hash_table_insert("THIS", "3");
    hash_table_insert("THAT", "4");
    hash_table_insert("SCREEN", "16384");
    hash_table_insert("KBD", "24576");

    // R0-R15
    for (int i = 0; i < 16; i++)
    {
        char key[4];
        sprintf(key, "R%d", i);
        char value[4];
        sprintf(value, "%d", i);
        hash_table_insert(key, value);
    }
}

bool symbol_table_contains(char *symbol)
{
    item *temp_item = hash_table_get(symbol);
    if (temp_item != NULL)
    {
        return true;
    }
    return false;
}  
 

void add_entry(char *symbol, int address)
{
    static int next_available_memory = 16;
    if (!symbol_table_contains(symbol))
    {
        char value[6];
        sprintf(value, "%d", address);
        hash_table_insert(symbol, value);
    }
}

int get_address(char *symbol)
{
    item *temp_item = hash_table_get(symbol);
    if (temp_item == NULL || temp_item->value == NULL) {
        return -1; // Or handle the error as appropriate
    }
    int address;
    sscanf(temp_item->value, "%d", &address);
    return address;
}

