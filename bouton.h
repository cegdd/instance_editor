#ifndef BOUTONH
#define BOUTONH

#include "data.h"
#include "console.h"

enum{B_NORMAL, B_SURVOLER, B_CLIQUER, B_IMPOSSIBLE, B_INUSE};/*bouton*/
enum{B_detail, B_liste, B_none};
enum{B_NEW_PROJECT, B_QUITTER, B_LOAD_PROJECT, B_SAVE_PROJECT, B_LOAD_MAP, B_PLAYER_START, B_SLIDE_CREATURE, B_SLIDE_CLOSE, B_NEW_CREATURE, B_DELETE_CREATURE_MOB};
struct UI;
struct DIVERSsysteme;


struct BOUTON
{
	GLuint texture;
	SDL_Rect pos;
	int etat;
	int flag;
};

struct BOUTON_TEXTE
{
	struct TEXTE texte;
	struct BOUTON bouton;
};

void BT_pointeur(struct DIVERSsysteme *systeme, struct UI *ui);
int BT_up(struct DIVERSsysteme *systeme, struct UI *ui);
void BT_event(int i, struct CONSOLE *console, struct DIVERSsysteme *systeme, struct UI *ui, struct DATA *data);

void BT_down(struct UI *ui);

void BT_update_loop(struct CONSOLE *console, struct DIVERSsysteme *systeme, struct UI *ui, struct DATA *data);
bool isInTheGoodPanel(struct UI *ui, int index);


#endif
