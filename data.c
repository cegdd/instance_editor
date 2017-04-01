
#include "data.h"
#include "bouton.h"

void initdata(struct DATA *data)
{
    int i;

    data->joueuractif = false;

    data->map.texture = -1;
    setPos4(&data->map.pos, 0, 0, 0, 0);
    data->map.x = 0;
    data->map.y = 0;

    setPos4(&data->joueur.pict.pos, 0, 0, 68, 51);

    data->joueur.pict.texture = loadTexture ("rs/images/perso0.png");

    data->nbmonstre = 0;
    data->mob_selected = -1;
    data->mob[0].monstre.pict.texture = loadTexture ("rs/images/mob0.0.png");
    for (i=0 ; i < 512 ; i++)
    {
        data->mob[i].state = B_NORMAL;
        data->mob[i].selected = false;
        data->mob[i].ID = 0;
        data->mob[i].scale = 1;
        data->mob[i].angle = 0;
        data->mob[i].monstre.pict.texture = 0;
        setPos4(&data->mob[i].monstre.pict.pos, 0, 0, 0, 0);
        setPos4(&data->mob[i].old, 0, 0, 0, 0);
    }
}
