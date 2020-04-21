
extern int screenh, screenw;

#include <stdio.h>

#include "ui.h"
#include "systeme.h"
#include "colision.h"

#include <LIBcegdd_ui.h>

void UI_setslidestate (int state, struct UI* ui)
{
    ui->slidestate = state;
    switch(state)
    {
    case SLIDE_CLOSE:
        ui->ListeBouton[7].etat =  B_IMPOSSIBLE;
        ui->ListeBouton[8].etat =  B_IMPOSSIBLE;
        ui->ListeBouton[9].etat =  B_IMPOSSIBLE;
        break;
    case SLIDE_ESPECE:
        ui->ListeBouton[7].etat =  B_NORMAL;
        ui->ListeBouton[8].etat =  B_NORMAL;
        ui->ListeBouton[9].etat =  B_NORMAL;
        break;
    case SLIDE_DETAIL:
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

    if(UI_getslidestate(ui) == SLIDE_ESPECE)
    {
        CEGDD_UI_draw_pict(&ui->fondliste);
        CEGDD_UI_draw_button(&ui->ListeBouton[7]);
        CEGDD_UI_draw_button(&ui->ListeBouton[8]);

        for (index = 0 ; index < systeme->NBespece ; index++)
        {
            CEGDD_UI_draw_button(ESP_getbouton_nom(index, systeme));
            if (systeme->ActiveEspece != -1)
            {
                ESP_drawthumb(systeme->creature[systeme->ActiveEspece].pict.texture, &ui->posthumbcreature);
                CEGDD_UI_draw_button(&ui->ListeBouton[9]);
                CEGDD_UI_draw_button(&ui->ListeBouton[11]);
                CEGDD_UI_draw_button(&ui->ListeBouton[12]);
                CEGDD_UI_draw_button(&ui->ListeBouton[13]);
                CEGDD_UI_draw_button(&ui->ListeBouton[14]);
                CEGDD_UI_draw_button(&ui->ListeBouton[15]);
                CEGDD_UI_draw_button(&ui->ListeBouton[16]);
                CEGDD_UI_draw_button(&ui->ListeBouton[22]);

                CEGDD_UI_draw_pict(&ui->Listetexte[0].img);
                CEGDD_UI_draw_pict(&ui->Listetexte[1].img);
                CEGDD_UI_draw_pict(&ui->Listetexte[2].img);
                CEGDD_UI_draw_pict(&ui->Listetexte[3].img);
                CEGDD_UI_draw_pict(&ui->Listetexte[4].img);
                CEGDD_UI_draw_pict(&ui->Listetexte[11].img);
                CEGDD_UI_draw_pict(&ui->Listetexte[12].img);
                CEGDD_UI_draw_pict(&ui->Listetexte[13].img);

                draw_coche(&ui->aggressif_pos, ui->aggressif_state[systeme->ActiveEspece], ui);
            }
        }
    }
    else if (UI_getslidestate(ui) == SLIDE_DETAIL)
    {
        systeme->ActiveEspece = data->mob[data->mob_selected].ID;

        if (data->mob_selected != -1)
        {
            CEGDD_UI_draw_pict(&ui->fonddetail);
            CEGDD_UI_draw_button(&ui->ListeBouton[7]);
            CEGDD_UI_draw_button(&ui->ListeBouton[9]);
            CEGDD_UI_draw_button(&ui->ListeBouton[17]);
            CEGDD_UI_draw_button(&ui->ListeBouton[18]);
            CEGDD_UI_draw_button(&ui->ListeBouton[19]);
            CEGDD_UI_draw_button(&ui->ListeBouton[20]);
            CEGDD_UI_draw_button(&ui->ListeBouton[21]);

            CEGDD_UI_draw_pict(&ui->Listetexte[5].img);
            CEGDD_UI_draw_pict(&ui->Listetexte[6].img);
            CEGDD_UI_draw_pict(&ui->Listetexte[7].img);
            CEGDD_UI_draw_pict(&ui->Listetexte[8].img);
            CEGDD_UI_draw_pict(&ui->Listetexte[9].img);
            CEGDD_UI_draw_pict(&ui->Listetexte[10].img);

            draw_coche(&ui->fixe_pos, ui->fixe_state[data->mob_selected], ui);
            draw_coche(&ui->loop_pos, ui->loop_state[data->mob_selected], ui);
            ESP_drawthumb(systeme->creature[systeme->ActiveEspece].pict.texture, &ui->posthumbcreature);

            PATH_display(data);
        }
    }
}

void initui (struct UI *ui, struct DIVERSsysteme *systeme)
{
    int i = 0;

    UI_setslidestate(SLIDE_CLOSE, ui);

    CEGDD_UI_setPos4(&ui->fondliste.pos, screenw-400, 110, 400,618);
    CEGDD_UI_setPos4(&ui->fonddetail.pos, screenw-282, 110, 400,618);
	CEGDD_UI_setPos4(&ui->posthumbcreature, screenw-200, 620, 100, 100);
    CEGDD_UI_setPos4(&ui->aggressif_pos, screenw-186, 561, 12, 12);
    CEGDD_UI_setPos4(&ui->fixe_pos, screenw-46, 558, 12, 12);
    CEGDD_UI_setPos4(&ui->loop_pos, screenw-166, 538, 12, 12);

    for (i = 0 ; i < 128 ; i++)
    {
        ui->aggressif_state[i] = false;
    }
    for (i = 0 ; i < 512 ; i++)
    {
        ui->fixe_state[i] = false;
        ui->loop_state[i] = false;
    }

    ui->coche[0] = CEGDD_UI_loadTexture ("rs/ui/coche0.png");
    ui->coche[1] = CEGDD_UI_loadTexture ("rs/ui/coche1.png");

    ui->ListeNb = 0;
    ui->texteNb = 0;

    /*0*/CEGDD_UI_creerbouton("rs/ui/creer.png",         0, screenh-40, 120, 40,             B_NORMAL, 		B_none,		ui->ListeBouton, &ui->ListeNb);
    /*1*/CEGDD_UI_creerbouton("rs/ui/quitter.png",       screenw-120, screenh-40, 120, 40,   B_NORMAL, 		B_none, 	ui->ListeBouton, &ui->ListeNb);
    /*2*/CEGDD_UI_creerbouton("rs/ui/charger.png",       360, screenh-40, 120, 40,           B_NORMAL, 		B_none, 	ui->ListeBouton, &ui->ListeNb);
    /*3*/CEGDD_UI_creerbouton("rs/ui/enregistrer.png",   240, screenh-40, 120, 40,           B_IMPOSSIBLE, 	B_none, 	ui->ListeBouton, &ui->ListeNb);
    /*4*/CEGDD_UI_creerbouton("rs/ui/loadmap.png",       120, screenh-40, 120, 40,           B_IMPOSSIBLE, 	B_none, 	ui->ListeBouton, &ui->ListeNb);
    /*5*/CEGDD_UI_creerbouton("rs/ui/depart.png",        480, screenh-40, 120, 40,           B_IMPOSSIBLE, 	B_none, 	ui->ListeBouton, &ui->ListeNb);
    /*6*/CEGDD_UI_creerbouton("rs/ui/monster.png",       600, screenh-40, 120, 40,           B_IMPOSSIBLE, 	B_none, 	ui->ListeBouton, &ui->ListeNb);
    /*7*/CEGDD_UI_creerbouton("rs/ui/fermer.png",        screenw-44, 684, 40,40,             B_IMPOSSIBLE, 	B_none, 	ui->ListeBouton, &ui->ListeNb);
    /*8*/CEGDD_UI_creerbouton("rs/ui/creer.png",         screenw-260, 122, 120,40,           B_IMPOSSIBLE, 	B_none, 	ui->ListeBouton, &ui->ListeNb); //creer une race de mob
    /*9*/CEGDD_UI_creerbouton("rs/ui/suppr.png",         screenw-130, 122, 120,40,           B_IMPOSSIBLE, 	B_none, 	ui->ListeBouton, &ui->ListeNb);
    /*10*/CEGDD_UI_creerboutontexte("nom",               screenw-396, 698,                   B_NORMAL, 		B_liste,	ui->ListeBouton, &ui->ListeNb, &systeme->blanc, systeme->police1);//nom
    /*11*/CEGDD_UI_creerboutontexte("path",              screenw-200, 598,                   B_NORMAL, 		B_liste,	ui->ListeBouton, &ui->ListeNb, &systeme->blanc, systeme->police1);//chemin image
    /*12*/CEGDD_UI_creerboutontexte("life",              screenw-226, 578,                   B_NORMAL, 		B_liste,	ui->ListeBouton, &ui->ListeNb, &systeme->blanc, systeme->police1);//vie
    /*13*/CEGDD_UI_creerboutontexte("100",               screenw-46, 558,                    B_IMPOSSIBLE, 	B_liste,	ui->ListeBouton, &ui->ListeNb, &systeme->blanc, systeme->police1);//rayon de vision
    /*14*/CEGDD_UI_creerboutontexte("50",                screenw-186, 538,                   B_NORMAL, 		B_liste,	ui->ListeBouton, &ui->ListeNb, &systeme->blanc, systeme->police1);//vitesse
    /*15*/CEGDD_UI_creerboutontexte("5",                 screenw-226, 518,                   B_NORMAL, 		B_liste,	ui->ListeBouton, &ui->ListeNb, &systeme->blanc, systeme->police1);//dps
    /*16*/CEGDD_UI_creerboutontexte("0",                 screenw-66, 518,                    B_NORMAL, 		B_liste,	ui->ListeBouton, &ui->ListeNb, &systeme->blanc, systeme->police1);//rayon d'attaque
    /*17*/CEGDD_UI_creerboutontexte("0",                 screenw-246, 598,                   B_NORMAL, 		B_detail,	ui->ListeBouton, &ui->ListeNb, &systeme->blanc, systeme->police1);//x
    /*18*/CEGDD_UI_creerboutontexte("0",                 screenw-136, 598,                   B_NORMAL, 		B_detail, 	ui->ListeBouton, &ui->ListeNb, &systeme->blanc, systeme->police1);//y
    /*19*/CEGDD_UI_creerboutontexte("1",                 screenw-201, 578,                   B_NORMAL, 		B_detail, 	ui->ListeBouton, &ui->ListeNb, &systeme->blanc, systeme->police1);//echelle
    /*20*/CEGDD_UI_creerboutontexte("0",                 screenw-101, 578,                   B_NORMAL, 		B_detail, 	ui->ListeBouton, &ui->ListeNb, &systeme->blanc, systeme->police1);//angle
    /*21*/CEGDD_UI_creerbouton("rs/ui/path.png",         screenw-250, 558, 60, 20,           B_NORMAL, 		B_liste, 	ui->ListeBouton, &ui->ListeNb);
    /*22*/CEGDD_UI_creerboutontexte("100",               screenw-201, 498,                   B_NORMAL, 		B_liste, 	ui->ListeBouton, &ui->ListeNb, &systeme->blanc, systeme->police1);//dps

    /*0*/CEGDD_UI_creertexte("aggressif:",   screenw-276, 558, ui->Listetexte, &ui->texteNb, &systeme->blanc, systeme->police1);
    /*1*/CEGDD_UI_creertexte("R de vision:", screenw-156, 558, ui->Listetexte, &ui->texteNb, &systeme->blanc, systeme->police1);
    /*2*/CEGDD_UI_creertexte("vitesse:",     screenw-276, 538, ui->Listetexte, &ui->texteNb, &systeme->blanc, systeme->police1);
    /*3*/CEGDD_UI_creertexte("dps:",         screenw-276, 518, ui->Listetexte, &ui->texteNb, &systeme->blanc, systeme->police1);
    /*4*/CEGDD_UI_creertexte("R d'attaque:", screenw-176, 518, ui->Listetexte, &ui->texteNb, &systeme->blanc, systeme->police1);
    /*5*/CEGDD_UI_creertexte("x:",           screenw-276, 598, ui->Listetexte, &ui->texteNb, &systeme->blanc, systeme->police1);
    /*6*/CEGDD_UI_creertexte("y:",           screenw-166, 598, ui->Listetexte, &ui->texteNb, &systeme->blanc, systeme->police1);
    /*7*/CEGDD_UI_creertexte("echelle:",     screenw-276, 578, ui->Listetexte, &ui->texteNb, &systeme->blanc, systeme->police1);
    /*8*/CEGDD_UI_creertexte("angle:",       screenw-166, 578, ui->Listetexte, &ui->texteNb, &systeme->blanc, systeme->police1);
    /*9*/CEGDD_UI_creertexte("fixe:",        screenw-166, 558, ui->Listetexte, &ui->texteNb, &systeme->blanc, systeme->police1);
    /*10*/CEGDD_UI_creertexte("loop:",       screenw-276, 538, ui->Listetexte, &ui->texteNb, &systeme->blanc, systeme->police1);
    /*11*/CEGDD_UI_creertexte("hit laps:",   screenw-276, 498, ui->Listetexte, &ui->texteNb, &systeme->blanc, systeme->police1);
    /*12*/CEGDD_UI_creertexte("vie:",        screenw-276, 578, ui->Listetexte, &ui->texteNb, &systeme->blanc, systeme->police1);
    /*13*/CEGDD_UI_creertexte("image:",      screenw-276, 598, ui->Listetexte, &ui->texteNb, &systeme->blanc, systeme->police1);

    ui->fondliste.texture =		CEGDD_UI_loadTexture ("rs/ui/fondmonstre.png");
    ui->fonddetail.texture =	CEGDD_UI_loadTexture ("rs/ui/fonddetail.png");

    if (glIsTexture(ui->fondliste.texture) == GL_FALSE          ||
        glIsTexture(ui->fonddetail.texture) == GL_FALSE)
    {
        printf("texture not loaded\n");
    }
}

void UI_updateESP(int index, struct DIVERSsysteme *systeme, struct UI *ui)
{
    ESP_refreshmob(systeme);
    CEGDD_UI_setboutontexte(systeme->creature[index].imgpath, 	11, ui->ListeBouton, &systeme->blanc, systeme->police1);
    CEGDD_UI_setboutonnombre(systeme->creature[index].vie, 		12, ui->ListeBouton, &systeme->blanc, systeme->police1);
    CEGDD_UI_setboutonnombre(systeme->creature[index].Rvision, 	13, ui->ListeBouton, &systeme->blanc, systeme->police1);
    CEGDD_UI_setboutonnombre(systeme->creature[index].vitesse, 	14, ui->ListeBouton, &systeme->blanc, systeme->police1);
    CEGDD_UI_setboutonnombre(systeme->creature[index].dps, 		15, ui->ListeBouton, &systeme->blanc, systeme->police1);
    CEGDD_UI_setboutonnombre(systeme->creature[index].hitlaps, 	22, ui->ListeBouton, &systeme->blanc, systeme->police1);
    CEGDD_UI_setboutonnombre(systeme->creature[index].Ratk, 		16, ui->ListeBouton, &systeme->blanc, systeme->police1);
}

void UI_updateMOB(int index, struct DIVERSsysteme *systeme, struct UI *ui, struct DATA *data)
{
    CEGDD_UI_setboutonnombre(data->mob[index].monstre.translation.x, 17, ui->ListeBouton, &systeme->blanc, systeme->police1);
    CEGDD_UI_setboutonnombre(data->mob[index].monstre.translation.y, 18, ui->ListeBouton, &systeme->blanc, systeme->police1);
    CEGDD_UI_setboutonnombre(data->mob[index].scale, 19, 				ui->ListeBouton, &systeme->blanc, systeme->police1);
    CEGDD_UI_setboutonnombre(data->mob[index].angle, 20, 				ui->ListeBouton, &systeme->blanc, systeme->police1);
}

int UI_is_inside(struct UI *ui, struct DIVERSsysteme *systeme, struct CONSOLE *console)
{
    if (UI_getslidestate(ui) == SLIDE_DETAIL && colisionbox(&systeme->pointeur.pos, &ui->fonddetail.pos, true) == true)
    {
       return true;
    }
    else if (UI_getslidestate(ui) == SLIDE_ESPECE && colisionbox(&systeme->pointeur.pos, &ui->fondliste.pos, true) == true)
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
