#include "ui.h"
#include "image.h"
#include "core.h"

extern int screenh, screenw;

void UI_setslidestate (int state, struct UI* ui)
{
    ui->slidestate = state;
    switch(state)
    {
    case UI_close:
        ui->ListeBouton[7].etat =  B_IMPOSSIBLE;
        ui->ListeBouton[8].etat =  B_IMPOSSIBLE;
        ui->ListeBouton[9].etat =  B_IMPOSSIBLE;
        break;
    case UI_listmob:
        ui->ListeBouton[7].etat =  B_NORMAL;
        ui->ListeBouton[8].etat =  B_NORMAL;
        ui->ListeBouton[9].etat =  B_NORMAL;
        break;
    case UI_detail:
        ui->ListeBouton[7].etat =  B_NORMAL;
        ui->ListeBouton[8].etat =  B_IMPOSSIBLE;
        ui->ListeBouton[9].etat =  B_NORMAL;
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
        draw_button(&ui->ListeBouton[7]);
        draw_button(&ui->ListeBouton[8]);

        for (index = 0 ; index < systeme->nbcreature ; index++)
        {
            draw_button(ESP_getbouton_nom(index, systeme));
            if (systeme->activecreature != -1)
            {
                ESP_drawthumb(systeme);
                draw_button(&ui->ListeBouton[9]);
                draw_button(&ui->ListeBouton[11]);
                draw_button(&ui->ListeBouton[12]);
                draw_pict(&ui->Listetexte[0].img);
                if (ui->aggressif.state == false)
                {
                    draw(ui->coche0, &ui->aggressif.pos);
                }
                else
                {
                    draw(ui->coche1, &ui->aggressif.pos);
                }
            }
        }
    }
    else if (UI_getslidestate(ui) == UI_detail)
    {
        systeme->activecreature = data->mob[data->mob_selected].ID;

        draw_pict(&ui->fonddetail);
        draw_button(&ui->ListeBouton[7]);
        draw_button(&ui->ListeBouton[9]);
        if (data->mob_selected != -1)
        {
            ESP_drawthumb(systeme);
        }
    }
}

void creerbouton(char *path, int x, int y, int w, int h, int state, struct UI *ui)
{
    ui->ListeBouton[ui->ListeNb].etat = state;
    setPos4(&ui->ListeBouton[ui->ListeNb].pos, x, y, w, h);
    ui->ListeBouton[ui->ListeNb].texture = loadTexture (path);
    if (glIsTexture(ui->ListeBouton[ui->ListeNb].texture) == GL_FALSE)
    {
        printf("texture not loaded\n");
    }

    ui->ListeNb++;
}

void creerboutontexte(char *path, int x, int y, int state, struct UI *ui, struct DIVERSsysteme *systeme)
{
    ui->ListeBouton[ui->ListeNb].etat = state;
    ui->ListeBouton[ui->ListeNb].texture = imprime(path, screenw, BLANC, systeme, &ui->ListeBouton[ui->ListeNb].pos.w, &ui->ListeBouton[ui->ListeNb].pos.h);

    setPos2(&ui->ListeBouton[ui->ListeNb].pos, x, y);

    if (glIsTexture(ui->ListeBouton[ui->ListeNb].texture) == GL_FALSE)
    {
        printf("texture not loaded\n");
    }

    ui->ListeNb++;
}

void creertexte(char *path, int x, int y, struct UI *ui, struct DIVERSsysteme *systeme)
{
    ui->Listetexte[ui->texteNb].img.texture = imprime(path, screenw, GRIS, systeme, &ui->Listetexte[ui->texteNb].img.pos.w, &ui->Listetexte[ui->texteNb].img.pos.h);

    setPos2(&ui->Listetexte[ui->texteNb].img.pos, x, y);

    if (glIsTexture(ui->Listetexte[ui->texteNb].img.texture) == GL_FALSE)
    {
        printf("texture of texte n: %d not loaded\n", ui->texteNb);
    }

    ui->texteNb++;
}


void setboutontexte(char *path, int index, struct UI *ui, struct DIVERSsysteme *systeme)
{
    ui->ListeBouton[index].texture = imprime(path, screenw, BLANC, systeme, &ui->ListeBouton[index].pos.w, &ui->ListeBouton[index].pos.h);

}

void setboutonnombre(int nombre, int index, struct UI *ui, struct DIVERSsysteme *systeme)
{
    char buffer[32];
    sprintf(buffer, "%d", nombre);
    ui->ListeBouton[index].texture = imprime(buffer, screenw, BLANC, systeme, &ui->ListeBouton[index].pos.w, &ui->ListeBouton[index].pos.h);

}

void initui (struct UI *ui, struct DIVERSsysteme *systeme)
{
    UI_setslidestate(UI_close, ui);

    setPos4(&ui->fondliste.pos, screenw-400, 110, 400,618);
    setPos4(&ui->fonddetail.pos, screenw-282, 110, 400,618);
    setPos4(&ui->aggressif.pos, 1210, screenh-207, 12, 12);

    ui->coche0 = loadTexture ("rs/ui/coche0.png");
    ui->coche1 = loadTexture ("rs/ui/coche1.png");

    ui->ListeNb = 0;
    ui->texteNb = 0;

    /*0*/creerbouton("rs/ui/creer.png", 0, screenh-40, 120, 40, B_NORMAL, ui);
    /*1*/creerbouton("rs/ui/quitter.png", screenw-120, screenh-40, 120, 40, B_NORMAL, ui);
    /*2*/creerbouton("rs/ui/charger.png", 360, screenh-40, 120, 40, B_NORMAL, ui);
    /*3*/creerbouton("rs/ui/enregistrer.png", 240, screenh-40, 120, 40, B_IMPOSSIBLE, ui);
    /*4*/creerbouton("rs/ui/loadmap.png", 120, screenh-40, 120, 40, B_IMPOSSIBLE, ui);
    /*5*/creerbouton("rs/ui/depart.png", 480, screenh-40, 120, 40, B_IMPOSSIBLE, ui);
    /*6*/creerbouton("rs/ui/monster.png", 600, screenh-40, 120, 40, B_IMPOSSIBLE, ui);
    /*7*/creerbouton("rs/ui/fermer.png", screenw-44, screenh-84, 40,40, B_IMPOSSIBLE, ui);
    /*8*/creerbouton("rs/ui/creer.png", screenw-260, 122, 120,40, B_IMPOSSIBLE, ui);
    /*9*/creerbouton("rs/ui/suppr.png", screenw-130, 122, 120,40, B_IMPOSSIBLE, ui);
    /*10*/creerboutontexte("nom", screenw-396, screenh-70, B_NORMAL, ui, systeme);
    /*11*/creerboutontexte("path", 1100, screenh-170, B_NORMAL, ui, systeme);
    /*12*/creerboutontexte("life", 1100, screenh-190, B_NORMAL, ui, systeme);

    /*0*/creertexte("aggressif :", 1100, screenh-210, ui, systeme);

    ui->fondliste.texture =       loadTexture ("rs/ui/fondmonstre.png");
    ui->fonddetail.texture =       loadTexture ("rs/ui/fonddetail.png");

    if (glIsTexture(ui->fondliste.texture) == GL_FALSE          ||
        glIsTexture(ui->fonddetail.texture) == GL_FALSE)
    {
        printf("texture not loaded\n");
    }
}

