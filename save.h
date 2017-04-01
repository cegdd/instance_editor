#ifndef SAVEH
#define SAVEH

#include "data.h"

#include "systeme.h"

void lis(FILE *fichier, char *buffer);
void ecris(char buffer[50], FILE *fichier);
void uncrypt(char buffer[4096], char *ret);
void saveproject (struct CONSOLE *console, struct DIVERSsysteme *systeme, struct DATA *data);
void loadproject (struct CONSOLE *console, struct DIVERSsysteme *systeme, struct DATA *data);

#endif
