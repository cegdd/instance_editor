#ifndef EDITEURH
#define EDITEURH
#include "core.h"

int editeur(struct DIVERSsysteme *systeme);
void loadingmap(struct CONSOLE *console, struct DIVERSsysteme *systeme, struct DATA *data);
void createproject (struct CONSOLE *console, struct DIVERSsysteme *systeme, struct DATA *data);
void loadingknownmap(struct CONSOLE *console, struct DIVERSsysteme *systeme, struct DATA *data, char *name);
void depart(struct DIVERSsysteme *systeme, struct DATA *data, struct CONSOLE *console);
void add(struct DIVERSsysteme *systeme, struct DATA *data, struct CONSOLE *console);


#endif
