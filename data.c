
#include "data.h"
#include "bouton.h"

#include <LIBcegdd_ui.h>

void initdata(struct DATA *data, struct DIVERSsysteme *systeme)
{
    int i;

    data->joueuractif = false;

    data->map.texture = -1;
    CEGDD_UI_setPos4(&data->map.pos, 0, 0, 0, 0);
    data->map.x = 0;
    data->map.y = 0;

    CEGDD_UI_setPos4(&data->joueur.pict.pos, 0, 0, 68, 51);

    data->joueur.pict.texture = CEGDD_UI_loadTexture ("rs/images/perso0.png");

    data->nbmonstre = 0;
    data->mob_selected = -1;
    data->mob[0].monstre.pict.texture = CEGDD_UI_loadTexture ("rs/images/mob0.0.png");
    for (i=0 ; i < 512 ; i++)
    {
        PATH_init(&data->mob[i].path, systeme);
        data->mob[i].state = B_NORMAL;
        data->mob[i].selected = false;
        data->mob[i].ID = 0;
        data->mob[i].scale = 1;
        data->mob[i].angle = 0;
        data->mob[i].monstre.pict.texture = 0;
        CEGDD_UI_setPos4(&data->mob[i].monstre.pict.pos, 0, 0, 0, 0);
        CEGDD_UI_setPos4(&data->mob[i].old, 0, 0, 0, 0);
    }
}
