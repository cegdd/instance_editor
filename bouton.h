#ifndef BOUTONH
#define BOUTONH

#include "struct.h"

enum{B_NORMAL, B_SURVOLER, B_CLIQUER, B_IMPOSSIBLE, B_INUSE};/*bouton*/

struct UI;
struct DIVERSsysteme;


struct BOUTON
{
	GLuint texture;
	SDL_Rect pos;
	int etat;
};

struct BOUTON_TEXTE
{
	struct TEXTE texte;
	struct BOUTON bouton;
};

void BT_pointeur(struct DIVERSsysteme *systeme, struct UI *ui);
int BT_up(struct DIVERSsysteme *systeme, struct UI *ui);
void BT_down(struct UI *ui);
void BT_event(int i, struct CONSOLE *console, struct DIVERSsysteme *systeme, struct UI *ui, struct DATA *data);
void BT_update_loop(struct CONSOLE *console, struct DIVERSsysteme *systeme, struct UI *ui, struct DATA *data);
#endif
