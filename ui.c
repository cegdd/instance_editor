
extern int screenh, screenw;

#include <stdio.h>

#include "ui.h"
#include "systeme.h"
#include "colision.h"

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
                draw_button(&ui->ListeBouton[13]);
                draw_button(&ui->ListeBouton[14]);
                draw_button(&ui->ListeBouton[15]);
                draw_button(&ui->ListeBouton[16]);

                draw_pict(&ui->Listetexte[0].img);
                draw_pict(&ui->Listetexte[1].img);
                draw_pict(&ui->Listetexte[2].img);
                draw_pict(&ui->Listetexte[3].img);
                draw_pict(&ui->Listetexte[4].img);

                draw_coche(&ui->aggressif_pos, ui->aggressif_state[systeme->activecreature], ui);
            }
        }
    }
    else if (UI_getslidestate(ui) == UI_detail)
    {
        systeme->activecreature = data->mob[data->mob_selected].ID;

        if (data->mob_selected != -1)
        {
            draw_pict(&ui->fonddetail);
            draw_button(&ui->ListeBouton[7]);
            draw_button(&ui->ListeBouton[9]);
            draw_button(&ui->ListeBouton[17]);
            draw_button(&ui->ListeBouton[18]);
            draw_button(&ui->ListeBouton[19]);
            draw_button(&ui->ListeBouton[20]);
            draw_button(&ui->ListeBouton[21]);

            draw_pict(&ui->Listetexte[5].img);
            draw_pict(&ui->Listetexte[6].img);
            draw_pict(&ui->Listetexte[7].img);
            draw_pict(&ui->Listetexte[8].img);
            draw_pict(&ui->Listetexte[9].img);
            draw_pict(&ui->Listetexte[10].img);

            draw_coche(&ui->fixe_pos, ui->fixe_state[data->mob_selected], ui);
            draw_coche(&ui->loop_pos, ui->loop_state[data->mob_selected], ui);
            ESP_drawthumb(systeme);

            PATH_display(data);
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


void setboutontexte(char *buffer, int index, struct UI *ui, struct DIVERSsysteme *systeme)
{
    ui->ListeBouton[index].texture = imprime(buffer, screenw, BLANC, systeme, &ui->ListeBouton[index].pos.w, &ui->ListeBouton[index].pos.h);

}

void setboutonnombre(int nombre, int index, struct UI *ui, struct DIVERSsysteme *systeme)
{
    char buffer[32];
    sprintf(buffer, "%d", nombre);
    ui->ListeBouton[index].texture = imprime(buffer, screenw, BLANC, systeme, &ui->ListeBouton[index].pos.w, &ui->ListeBouton[index].pos.h);

}

void initui (struct UI *ui, struct DIVERSsysteme *systeme)
{
    int i = 0;

    UI_setslidestate(UI_close, ui);

    setPos4(&ui->fondliste.pos, screenw-400, 110, 400,618);
    setPos4(&ui->fonddetail.pos, screenw-282, 110, 400,618);
    setPos4(&ui->aggressif_pos, 1180, screenh-207, 12, 12);
    setPos4(&ui->fixe_pos, 1320, screenh-210, 12, 12);
    setPos4(&ui->loop_pos, 1200, screenh-230, 12, 12);

    for (i = 0 ; i < 128 ; i++)
    {
        ui->aggressif_state[i] = false;
    }
    for (i = 0 ; i < 512 ; i++)
    {
        ui->fixe_state[i] = false;
        ui->loop_state[i] = false;
    }

    ui->coche[0] = loadTexture ("rs/ui/coche0.png");
    ui->coche[1] = loadTexture ("rs/ui/coche1.png");

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
    /*10*/creerboutontexte("nom", screenw-396, screenh-70, B_NORMAL, ui, systeme);//nom
    /*11*/creerboutontexte("path", 1090, screenh-170, B_NORMAL, ui, systeme);//chemin image
    /*12*/creerboutontexte("life", 1090, screenh-190, B_NORMAL, ui, systeme);//vie
    /*13*/creerboutontexte("100", 1320, screenh-210, B_IMPOSSIBLE, ui, systeme);//rayon de vision
    /*14*/creerboutontexte("50", 1180, screenh-230, B_NORMAL, ui, systeme);//vitesse
    /*15*/creerboutontexte("5", 1140, screenh-250, B_NORMAL, ui, systeme);//dps
    /*16*/creerboutontexte("0", 1300, screenh-250, B_NORMAL, ui, systeme);//rayon d'attaque
    /*17*/creerboutontexte("0", 1120, screenh-170, B_NORMAL, ui, systeme);//x
    /*18*/creerboutontexte("0", 1230, screenh-170, B_NORMAL, ui, systeme);//y
    /*19*/creerboutontexte("1", 1165, screenh-190, B_NORMAL, ui, systeme);//echelle
    /*20*/creerboutontexte("0", 1265, screenh-190, B_NORMAL, ui, systeme);//angle
    /*21*/creerbouton("rs/ui/path.png", screenw-250, screenh-210, 60,20, B_NORMAL, ui);

    /*0*/creertexte("aggressif:", 1090, screenh-210, ui, systeme);
    /*1*/creertexte("R de vision:", 1210, screenh-210, ui, systeme);
    /*2*/creertexte("vitesse:", 1090, screenh-230, ui, systeme);
    /*3*/creertexte("dps:", 1090, screenh-250, ui, systeme);
    /*4*/creertexte("R d'attaque:", 1190, screenh-250, ui, systeme);
    /*5*/creertexte("x:", 1090, screenh-170, ui, systeme);
    /*6*/creertexte("y:", 1200, screenh-170, ui, systeme);
    /*7*/creertexte("echelle:", 1090, screenh-190, ui, systeme);
    /*8*/creertexte("angle:", 1200, screenh-190, ui, systeme);
    /*9*/creertexte("fixe:", 1200, screenh-210, ui, systeme);
    /*10*/creertexte("loop:", 1090, screenh-230, ui, systeme);

    ui->fondliste.texture =       loadTexture ("rs/ui/fondmonstre.png");
    ui->fonddetail.texture =       loadTexture ("rs/ui/fonddetail.png");

    if (glIsTexture(ui->fondliste.texture) == GL_FALSE          ||
        glIsTexture(ui->fonddetail.texture) == GL_FALSE)
    {
        printf("texture not loaded\n");
    }
}

void UI_updateESP(int index, struct DIVERSsysteme *systeme, struct UI *ui)
{
    ESP_refreshmob(systeme);
    setboutontexte(systeme->creature[index].imgpath, 11, ui, systeme);
    setboutonnombre(systeme->creature[index].vie, 12, ui, systeme);
    setboutonnombre(systeme->creature[index].Rvision, 13, ui, systeme);
    setboutonnombre(systeme->creature[index].vitesse, 14, ui, systeme);
    setboutonnombre(systeme->creature[index].dps, 15, ui, systeme);
    setboutonnombre(systeme->creature[index].Ratk, 16, ui, systeme);
}

void UI_updateMOB(int index, struct DIVERSsysteme *systeme, struct UI *ui, struct DATA *data)
{
    setboutonnombre(data->mob[index].monstre.translation.x, 17, ui, systeme);
    setboutonnombre(data->mob[index].monstre.translation.y, 18, ui, systeme);
    setboutonnombre(data->mob[index].scale, 19, ui, systeme);
    setboutonnombre(data->mob[index].angle, 20, ui, systeme);
}

int UI_is_inside(struct UI *ui, struct DIVERSsysteme *systeme, struct CONSOLE *console)
{
    if (UI_getslidestate(ui) == UI_detail && colisionbox(&systeme->pointeur.pos, &ui->fonddetail.pos, true) == true)
    {
       return true;
    }
    else if (UI_getslidestate(ui) == UI_listmob && colisionbox(&systeme->pointeur.pos, &ui->fondliste.pos, true) == true)
    {
       return true;
    }
    else if (colisionbox(&systeme->pointeur.pos, &console->console.pos, true) == true)
    {
       return true;
    }
    else if (colisionbox(&systeme->pointeur.pos, &console->shootoff.pos, true) == true)
    {
       return true;
    }
    else if (systeme->pointeur.pos.y >= screenh-70)
    {
        return true;
    }
    return false;
}
