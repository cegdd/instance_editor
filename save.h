#include "struct.h"

void lis(FILE *fichier, char *buffer);
void ecris(char string[50], FILE *fichier);
void uncrypt(char string[4096], char *ret);
void saveproject (struct CONSOLE *console, struct DIVERSsysteme *systeme, struct DATA *data);
void loadproject (struct CONSOLE *console, struct DIVERSsysteme *systeme, struct DATA *data);