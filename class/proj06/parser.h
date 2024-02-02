
// Parsing Functions

char *get_dest(char *command);
char *get_jump(char *command);
char *get_comp(char *command);
char *get_symbol(char *command);

// Command Type

enum INSTRUCTION { A_INSTRUCTION, C_INSTRUCTION, L_INSTRUCTION };
enum INSTRUCTION command_type(char *command);
