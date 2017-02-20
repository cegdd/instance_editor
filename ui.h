#ifndef UIH
#define UIH

#include "struct.h"
#include "core.h"
#include "bouton.h"

enum{UI_close, UI_listmob, UI_detail};


struct UI
{
    int slidestate;

    struct pict fondliste;
    struct pict fonddetail;

    struct BOUTON ListeBouton[64];
    int ListeNb;
};

void initui (struct UI *ui, struct DIVERSsysteme *systeme);

void UI_setslidestate (int state, struct UI* ui);
int UI_getslidestate(struct UI* ui);

void UI_drawslide(struct UI* ui, struct DIVERSsysteme *systeme, struct DATA *data);
void creerbouton(char *path, int x, int y, int w, int h, int state, struct UI *ui);
void creerboutontexte(char *path, int x, int y, int state, struct UI *ui, struct DIVERSsysteme *systeme);

#endif
