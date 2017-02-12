
#ifndef SLIDEH
#define SLIDEH

enum{SLIDE_close, SLIDE_listemob, SLIDE_detailmob};

struct SLIDE
{
    int state;

    struct BOUTON fermer;
    struct BOUTON creermob;
    struct BOUTON supprmob;
    struct pict fondmob;

    struct BOUTON *ListeBouton[64];
    int ListeNb;
};

#endif
