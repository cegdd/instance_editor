
#include "struct.h"


int editeur(struct DIVERSsysteme *systeme);
void loadingmap(struct CONSOLE *console, struct DIVERSsysteme *systeme, struct DATA *data);
void createproject (struct CONSOLE *console, struct DIVERSsysteme *systeme, struct DATA *data);
void ecris(char string[50], FILE *fichier);
void uncrypt(char string[4096], char *ret);
void saveproject (struct CONSOLE *console, struct DIVERSsysteme *systeme, struct DATA *data);
void loadproject (struct CONSOLE *console, struct DIVERSsysteme *systeme, struct DATA *data);
void loadingknownmap(struct CONSOLE *console, struct DIVERSsysteme *systeme, struct DATA *data, char *name);
void lis(FILE *fichier, char *buffer);
