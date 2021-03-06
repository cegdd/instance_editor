#include <stdio.h>

#include "path.h"
#include "data.h"
#include "systeme.h"

int PATH_add(struct PATH *path, int x, int y, struct DATA *data)
{
    int i = 0;
    while (path->used[i] == true)
    {
        i++;
    }
    if (i < PATH_dots)
    {
        path->x[i] = x;
        path->y[i] = y;
        path->nb[i].translation.x = path->x[i] - path->nb[i].pict.pos.w/2 - data->map.pos.x;
        path->nb[i].translation.y = path->y[i] + path->nb[i].pict.pos.h/2 - data->map.pos.y;
        path->used[i] = true;
        path->counter++;
    }
    else{return -1;}

    return i;
}

int PATH_remove(struct PATH *path)
{
    int i = 0;
    while (path->used[i] == true)
    {
        i++;
    }
    if (i > 0)
    {
        path->used[i-1] = false;
        path->counter--;
    }
    else{return -1;}

    return i-1;
}

void PATH_init(struct PATH *path, struct DIVERSsysteme *systeme)
{
    int i;
    char buffer[8];
    for (i = 0 ; i < PATH_dots ; i++)
    {
        path->x[i] = 0;
        path->y[i] = 0;
        path->used[i] = false;
        path->loop = false;
        sprintf(buffer, "%d",i);
        path->nb[i].pict.texture = CEGDD_UI_imprime(buffer, 100, &systeme->rouge, systeme->police1, &path->nb[i].pict.pos.w, &path->nb[i].pict.pos.h);
    }
}
void PATH_write (struct PATH *path)
{
    int i = 0;
    while (path->used[i] == true)
    {
        printf("%d en %d %d\n", i, path->x[i], path->y[i]);
        i++;
    }
}

void PATH_display (struct DATA *data)
{
    int i = 0;

    while (data->mob[data->mob_selected].path.used[i] == true)
    {
        CEGDD_UI_draw_hookpict(&data->mob[data->mob_selected].path.nb[i], &data->map.pos);
        i++;
    }
}
