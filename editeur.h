#ifndef EDITEURH
#define EDITEURH

int editeur(struct DIVERSsysteme *systeme);
void affichage(struct CONSOLE *console, struct DIVERSsysteme *systeme, struct UI *ui, struct DATA *data);

void loadingmap(struct CONSOLE *console, struct DIVERSsysteme *systeme, struct DATA *data);
void createproject (struct CONSOLE *console, struct DIVERSsysteme *systeme, struct DATA *data);
void loadingknownmap(struct CONSOLE *console, struct DIVERSsysteme *systeme, struct DATA *data, char *name);
void depart(struct DIVERSsysteme *systeme, struct DATA *data, struct CONSOLE *console);
void add(struct DIVERSsysteme *systeme, struct DATA *data, struct CONSOLE *console);


#endif
