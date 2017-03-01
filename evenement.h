#ifndef EVENEMENTH
#define EVENEMENTH

#include <stdbool.h>
#include "main.h"

void boucleevent (struct DIVERSsysteme *systeme, struct UI *ui, struct CONSOLE *console, struct DATA *data);
void pointeur(struct DIVERSsysteme *systeme, struct UI *ui, struct DATA *data);
void clic_UP_L(struct DIVERSsysteme *systeme, struct UI *ui, struct CONSOLE *console, struct DATA *data);
void clic_DOWN_L(struct UI *ui, struct DIVERSsysteme *systeme, struct DATA *data, struct CONSOLE *console);
#endif
