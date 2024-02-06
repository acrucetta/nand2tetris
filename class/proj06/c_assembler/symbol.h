
void symbol_table_init();
void add_entry(char *symbol, int address);
bool symbol_table_contains(char *symbol);
int get_address(char *symbol);
