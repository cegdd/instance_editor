#ifndef UIH
#define UIH

#include <stdbool.h>

#include "image.h"
#include "bouton.h"

enum{UI_close, UI_listmob, UI_detail};


struct UI
{
    int slidestate;

    struct pict fondliste;
    struct pict fonddetail;
    GLuint coche[2];

    struct  SDL_Rect    aggressif_pos;
    bool                aggressif_state[128];
    struct  SDL_Rect    fixe_pos;
    bool                fixe_state[512];
    struct  SDL_Rect    loop_pos;
    bool                loop_state[512];

    struct BOUTON ListeBouton[64];
    int ListeNb;
    struct TEXTE Listetexte[64];
    int texteNb;
};

void initui (struct UI *ui, struct DIVERSsysteme *systeme);

void UI_setslidestate (int state, struct UI* ui);
int UI_getslidestate(struct UI* ui);

void UI_drawslide(struct UI* ui, struct DIVERSsysteme *systeme, struct DATA *data);
void creerbouton(char *path, int x, int y, int w, int h, int state, struct UI *ui);
void creerboutontexte(char *path, int x, int y, int state, struct UI *ui, struct DIVERSsysteme *systeme);
void creertexte(char *path, int x, int y, struct UI *ui, struct DIVERSsysteme *systeme);
void setboutontexte(char *path, int index, struct UI *ui, struct DIVERSsysteme *systeme);
void setboutonnombre(int nombre, int index, struct UI *ui, struct DIVERSsysteme *systeme);
void UI_updateESP(int index, struct DIVERSsysteme *systeme, struct UI *ui);
void UI_updateMOB(int index, struct DIVERSsysteme *systeme, struct UI *ui, struct DATA *data);

int UI_is_inside(struct UI *ui, struct DIVERSsysteme *systeme, struct CONSOLE *console);


#endif
