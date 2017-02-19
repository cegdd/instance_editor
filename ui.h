#ifndef UIH
#define UIH

#include "struct.h"
#include "core.h"
#include "bouton.h"

enum{UI_close, UI_listmob, UI_detail};


struct UI
{
    int slidestate;

    struct BOUTON creer;
    struct BOUTON quitter;
    struct BOUTON loadmap;
    struct BOUTON enregistrer;
    struct BOUTON charger;
    struct BOUTON depart;
    struct BOUTON monster;

    struct BOUTON fermer;
    struct BOUTON creermob;
    struct BOUTON supprmob;
    struct pict fondliste;
    struct pict fonddetail;

    struct BOUTON *ListeBouton[64];
    int ListeNb;
};

void UI_setslidestate (int state, struct UI* ui);
int UI_getslidestate(struct UI* ui);

void UI_drawslide(struct UI* ui, struct DIVERSsysteme *systeme, struct DATA *data);

#endif
