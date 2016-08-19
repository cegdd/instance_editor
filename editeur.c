#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

#include <GL/gl.h>
#include <GL/glu.h>

#include "struct.h"
#include "tableau.h"
#include "evenement.h"
#include "image.h"
#include "systeme.h"
#include "clavier.h"
#include "editeur.h"

extern int screenh, screenw;

int editeur(struct DIVERSsysteme *systeme)
{
    int index;
    struct UI ui;
    struct CONSOLE console;
    struct DATA data;
    initui(&ui);
    initconsole(&console, systeme);
    initdata(&data);

    while(systeme->continuer)
    {
        /*effacage de l'�cran*/
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT) ;
        SDL_GetMouseState(&systeme->pointeur.pos.x, &systeme->pointeur.pos.y);
        /*reverse for OpenGL*/
        systeme->pointeur.pos.y = (systeme->pointeur.pos.y - screenh + systeme->pointeur.pos.h) * -1;

        boucleevent(systeme, &ui, &console, &data);
        pointeur(systeme, &ui);

        if (systeme->asked)
        {
            if(systeme->askID == MAP)
            {
                loadingmap(&console, systeme, &data);
            }
            else if(systeme->askID == CREER)
            {
                createproject(&console, systeme, &data);
            }
            else if(systeme->askID == ENREGISTRER)
            {
                saveproject(&console, systeme, &data);
            }
            else if(systeme->askID == CHARGER)
            {
                loadproject(&console, systeme, &data);
            }
        }

        if (glIsTexture(data.map.texture))
        {
            data.map.pos.x = data.map.x + systeme->origine.x;
            data.map.pos.y = data.map.y + systeme->origine.y;
            draw_pict(&data.map);
        }
        if (data.joueuractif)
        {
            draw_hookpict(&data.joueur, &data.map.pos);
        }

        //   ui

        if (systeme->projetouvert == true && ui.loadmap.etat == B_IMPOSSIBLE)
        {
            ui.loadmap.etat = B_NORMAL;
            ui.enregistrer.etat = B_NORMAL;
        }

        draw_button(&ui.creer);
        draw_button(&ui.quitter);
        draw_button(&ui.enregistrer);
        draw_button(&ui.loadmap);
        draw_button(&ui.charger);
        draw_button(&ui.depart);

        draw_pict(&console.console);
        if (console.active)
        {
            draw_pict(&console.shooton);
        }
        else
        {
            draw_pict(&console.shootoff);
        }
        for(index = 0 ; index < 10 ; index++)
        {
            draw_pict(&console.texte[index].img);
        }
        console.ecris.img.texture = imprime (console.tampon, screenw, BLANC, systeme, &console.ecris.lenght, &console.ecris.high);
        console.ecris.img.pos.w = console.ecris.lenght;

        draw_pict(&console.ecris.img);

        glFlush();
        SDL_GL_SwapWindow(systeme->screen);

        SDL_Delay(10);
    }
    return EXIT_SUCCESS;
}

void loadingmap(struct CONSOLE *console, struct DIVERSsysteme *systeme, struct DATA *data)
{
    if (console->answered)
    {
        systeme->asked = false;
        char temp[128];
        console->answered = false;
        systeme->asked = false;

        sprintf(data->projectmap, "%s", console->lastanswer);
        sprintf(temp, "rs/map/%s.png", console->lastanswer);
        data->map.texture = loadTextureandsize(temp, &data->map.pos);
        data->map.x = data->map.pos.x;
        data->map.y = data->map.pos.y;


        if(glIsTexture(data->map.texture))
        {
            sprintf(temp, "texture successfuly loaded %d x %d", data->map.pos.w, data->map.pos.h);
            say (temp, console, systeme);
        }
        else
        {
            say("ERROR : texture not successfuly loaded", console, systeme);
        }
    }
}

void loadingknownmap(struct CONSOLE *console, struct DIVERSsysteme *systeme, struct DATA *data, char *name)
{
    systeme->asked = false;
    char temp[128];
    console->answered = false;
    systeme->asked = false;

    sprintf(data->projectmap, "%s", name);
    sprintf(temp, "rs/map/%s.png", name);
    data->map.texture = loadTextureandsize(temp, &data->map.pos);
    data->map.x = data->map.pos.x;
    data->map.y = data->map.pos.y;


    if(glIsTexture(data->map.texture))
    {
        sprintf(temp, "texture successfuly loaded %d x %d", data->map.pos.w, data->map.pos.h);
        say (temp, console, systeme);
    }
    else
    {
        say("ERROR : texture not successfuly loaded", console, systeme);
    }
}

void createproject (struct CONSOLE *console, struct DIVERSsysteme *systeme, struct DATA *data)
{
    if (console->answered)
    {
        char temp2[128];

        systeme->asked = false;
        console->answered = false;
        systeme->asked = false;

        sprintf(data->projectname, "%s", console->lastanswer);
        sprintf(temp2, "projet \"%s\" cr�e\n", data->projectname);
        say(temp2, console, systeme);

        systeme->projetouvert = true;
    }
}
void saveproject (struct CONSOLE *console, struct DIVERSsysteme *systeme, struct DATA *data)
{
    char buffer[128];
    FILE *fichier = NULL;

    systeme->asked = false;
    console->answered = false;
    systeme->asked = false;

    sprintf(buffer, "rs/map/%s.RSCryptedMap", data->projectname);
    fichier = fopen(buffer, "w");
    //nom de la map
    ecris(data->projectmap, fichier);
    //si le joueur est poser
    if (data->joueuractif)
    {
        ecris("1\0", fichier);
    }
    else
    {
        ecris("0\0", fichier);
    }
    //translation joueur en x
    sprintf(buffer, "%d", data->joueur.translation.x);
    ecris(buffer, fichier);
    say(buffer, console, systeme);
    //translation joueur en y
    sprintf(buffer, "%d", data->joueur.translation.y);
    ecris(buffer, fichier);
    say(buffer, console, systeme);

    fclose(fichier);
    say("projet enregistre avec succes", console, systeme);
}

void loadproject (struct CONSOLE *console, struct DIVERSsysteme *systeme, struct DATA *data)
{
    if (console->answered)
    {
        char temp[128];
        char buffer[4096] = {'\0'};
        char ret[50] = {'\0'};
        FILE *fichier = NULL;

        systeme->asked = false;
        console->answered = false;
        systeme->asked = false;

        sprintf(data->projectname, "%s", console->lastanswer);
        sprintf(temp, "rs/map/%s.RSCryptedMap", console->lastanswer);
        fichier = fopen(temp, "r");

        if (fichier != NULL)
        {
            sprintf(temp, "projet %s en cours d'ouverture ...", console->lastanswer);
            say(temp, console, systeme);

            lis(fichier, buffer);
            uncrypt(buffer, ret);

            loadingknownmap(console, systeme, data, ret);
            sprintf(temp, "map %s chargee", ret);
            say(temp, console, systeme);

            lis(fichier, buffer);
            uncrypt(buffer, ret);
            if (ret[0] == '1')
            {
                lis(fichier, buffer);
                uncrypt(buffer, ret);
                data->joueur.translation.x = atoi(ret);
                lis(fichier, buffer);
                uncrypt(buffer, ret);
                data->joueur.translation.y = atoi(ret);
                sprintf(temp, "joueur positione en x:%d y:%d", data->joueur.translation.x, data->joueur.translation.y);
                say(temp, console, systeme);
                data->joueuractif = true;
            }
            else
            {
                data->joueuractif = false;
            }

            systeme->projetouvert = true;
            fclose(fichier);
        }
        else
        {
            say("no project founded", console, systeme);
        }
    }
}

void depart(struct DIVERSsysteme *systeme, struct DATA *data, struct CONSOLE *console)
{

    data->joueuractif = true;
    data->joueur.translation.x = (systeme->evenement.motion.x - data->joueur.pict.pos.w/2) - data->map.pos.x;
    data->joueur.translation.y = (screenh - systeme->evenement.motion.y - data->joueur.pict.pos.h/2) - data->map.pos.y;
    say("joueur positioner", console, systeme);

}


void ecris(char string[50], FILE *fichier)
{
	int i = 0, index;
	int valeur = 0;

	while(string[i] != '\0')
	{
		valeur = (int)string[i];
		for(index = 0 ; index < valeur ; index++)
		{
			fputc('O', fichier);
		}
		fputc('0', fichier);
		i++;
	}
    fputc('#', fichier);
}


void uncrypt(char string[4096], char *ret)
{
	int i = 0, index = 0;
	int compteur = 0;

	while(string[i] != '\0')
	{
		while(string[i] == 'O')
		{
			compteur++;
			i++;
		}
		i++;
		ret[index] = compteur;
		compteur = 0;
		index++;
	}
	ret[index] = '\0';
}

void lis(FILE *fichier, char *buffer)
{
    char caractere = '\0';
    int iligne = 0;

    caractere = fgetc(fichier);
    while (caractere != '#')
    {
        buffer[iligne] = caractere;
        iligne++;
        caractere = fgetc(fichier);
    }
    buffer[iligne] = '\0';
}
