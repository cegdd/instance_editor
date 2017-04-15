
#ifndef DATAH
#define DATAH

#include "mob.h"


struct DATA
{
    bool joueuractif;

    struct pict map;
    struct hookpict joueur;
    struct MOB mob[512];
    int nbmonstre;
    int mob_selected;

    char projectname [64];
    char projectmap [64];
};

void initdata(struct DATA *data, struct DIVERSsysteme *systeme);

#endif
