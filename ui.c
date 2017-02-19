#include "ui.h"
#include "image.h"
#include "core.h"

void UI_setslidestate (int state, struct UI* ui)
{
    ui->slidestate = state;
    switch(state)
    {
    case UI_close:
        ui->fermer.etat =  B_IMPOSSIBLE;
        ui->creermob.etat =  B_IMPOSSIBLE;
        ui->supprmob.etat =  B_IMPOSSIBLE;
        break;
    case UI_listmob:
        ui->fermer.etat =  B_NORMAL;
        ui->creermob.etat =  B_NORMAL;
        ui->supprmob.etat =  B_NORMAL;
        break;
    case UI_detail:
        ui->fermer.etat =  B_NORMAL;
        ui->creermob.etat =  B_IMPOSSIBLE;
        ui->supprmob.etat =  B_IMPOSSIBLE;
        break;
    }
}

int UI_getslidestate(struct UI* ui)
{
    return ui->slidestate;
}

void UI_drawslide(struct UI* ui, struct DIVERSsysteme *systeme, struct DATA *data)
{
    int index;

    if(UI_getslidestate(ui) == UI_listmob)
    {
        draw_pict(&ui->fondliste);
        draw_button(&ui->fermer);
        draw_button(&ui->creermob);

        for (index = 0 ; index < systeme->nbcreature ; index++)
        {
            draw_button(ESP_getbouton_nom(index, systeme));
            if (systeme->activecreature != -1)
            {
                ESP_drawthumb(systeme);
                draw_button(ESP_getbouton_vie(systeme->activecreature, systeme));
                draw_button(ESP_getbouton_imgpath(systeme->activecreature, systeme));
                draw_button(&ui->supprmob);
            }
        }
    }
    else if (UI_getslidestate(ui) == UI_detail)
    {
        draw_pict(&ui->fonddetail);
        draw_button(&ui->fermer);

        if (data->mob_selected != -1)
        {
            printf("%d\n", data->mob[data->mob_selected].ID);
        }
    }
}
