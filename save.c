#include <stdio.h>
#include <stdlib.h>

#include "struct.h"
#include "systeme.h"
#include "editeur.h"
#include "image.h"
#include "save.h"

/**
SAVE FILE DATA STRUCTURE

-string     map name
-int        number of creature
    *int        ID
    *string     name
    *string     img name
    *int        life
-bool       player set
    -int        player x
    -int        player y
-int        number of mob set
    *int        ID
    *int        mob x
    *int        mob y
**/

void saveproject (struct CONSOLE *console, struct DIVERSsysteme *systeme, struct DATA *data)
{
    char buffer[128];
    FILE *fichier = NULL;
    int i;

    systeme->asked = false;
    console->answered = false;

    sprintf(buffer, "rs/sauvegarde/%s.RSCryptedMap", data->projectname);
    fichier = fopen(buffer, "w+");
    //nom de la map
    ecris(data->projectmap, fichier);

    //number of creature
    sprintf(buffer, "%d", systeme->nbcreature);
    ecris(buffer, fichier);
    for(i=0 ; i < systeme->nbcreature ; i++)
    {
        //ID
        sprintf(buffer, "0");
        ecris(buffer, fichier);
        //name
        sprintf(buffer, "%s", systeme->creature[i].name);
        ecris(buffer, fichier);
        //image name
        sprintf(buffer, "%s", systeme->creature[i].imgpath);
        ecris(buffer, fichier);
        sprintf(buffer, "%d", systeme->creature[i].vie);
        ecris(buffer, fichier);
    }




    //si le joueur est poser
    if (data->joueuractif)
    {
        ecris("1", fichier);
         //translation joueur en x
        sprintf(buffer, "%d", data->joueur.translation.x);
        ecris(buffer, fichier);
        //translation joueur en y
        sprintf(buffer, "%d", data->joueur.translation.y);
        ecris(buffer, fichier);
    }
    else
    {
        ecris("0", fichier);
    }

    //nombre de mobs
    sprintf(buffer, "%d", data->nbmonstre);
    ecris(buffer, fichier);

    for(i=0 ; i < data->nbmonstre ; i++)
    {
        sprintf(buffer, "%d", data->mob[i].ID);
        ecris(buffer, fichier);
        sprintf(buffer, "%d", data->mob[i].monstre.translation.x);
        ecris(buffer, fichier);
        sprintf(buffer, "%d", data->mob[i].monstre.translation.y);
        ecris(buffer, fichier);
    }

    fclose(fichier);
    say("projet enregistre avec succes", console, systeme);
}

void loadproject (struct CONSOLE *console, struct DIVERSsysteme *systeme, struct DATA *data)
{
    if (console->answered)
    {
        char temp[128];
        char buffer[4096] = {'\0'};
        FILE *fichier = NULL;
        int i;

        systeme->asked = false;
        console->answered = false;

        sprintf(data->projectname, "%s", console->lastanswer);
        sprintf(temp, "rs/sauvegarde/%s.RSCryptedMap", console->lastanswer);
        fichier = fopen(temp, "r");

        if (fichier != NULL)
        {
            sprintf(temp, "projet %s en cours d'ouverture ...", console->lastanswer);
            say(temp, console, systeme);

            //nom de la map
            lis(fichier, buffer);

            loadingknownmap(console, systeme, data, buffer);
            sprintf(temp, "map %s chargee", buffer);
            say(temp, console, systeme);

            lis(fichier, buffer);

            systeme->nbcreature = atoi(buffer);
            for(i = 0 ; i < systeme->nbcreature ; i++)
            {
                lis(fichier, buffer);
                lis(fichier, buffer);
                sprintf(systeme->creature[i].name, buffer);
                lis(fichier, buffer);
                sprintf(systeme->creature[i].imgpath, buffer);
                lis(fichier, buffer);
                systeme->creature[i].vie = atoi(buffer);
            }
            sprintf(temp, "%d monstre en memoire", systeme->nbcreature);
            say(temp, console, systeme);

            //si le joueur est poser
            lis(fichier, buffer);
            if (buffer[0] == '1')
            {
                //translation joueur en x
                lis(fichier, buffer);
                data->joueur.translation.x = atoi(buffer);
                //translation joueur en y
                lis(fichier, buffer);
                data->joueur.translation.y = atoi(buffer);
                sprintf(temp, "joueur positione en x:%d y:%d", data->joueur.translation.x, data->joueur.translation.y);
                say(temp, console, systeme);
                data->joueuractif = true;
            }
            else
            {
                data->joueuractif = false;
            }

            //nombre de mobs
            listmob(systeme);

            lis(fichier, buffer);
            data->nbmonstre = atoi(buffer);

            for(i=0 ; i<data->nbmonstre ; i++)
            {
                //ID des mobs
                lis(fichier, buffer);
                data->mob[i].ID = atoi(buffer);
                //translation mob en x
                lis(fichier, buffer);
                data->mob[i].monstre.translation.x = atoi(buffer);
                //translation mob en x
                lis(fichier, buffer);
                data->mob[i].monstre.translation.y = atoi(buffer);
                data->mob[i].actif = true;
                data->mob[i].monstre.pict.texture = systeme->creature[data->mob[i].ID].pict.texture;
                setPos4(&data->mob[i].monstre.pict.pos, 0, 0, systeme->creature[data->mob[i].ID].pict.pos.w, systeme->creature[data->mob[i].ID].pict.pos.h);
            }
            sprintf(temp, "%d monstre poser", data->nbmonstre);
            say(temp, console, systeme);

            systeme->projetouvert = true;
            fclose(fichier);
        }
        else
        {
            say("no project founded", console, systeme);
        }
    }
}


void ecris(char string[50], FILE *fichier)
{
	int i = 0, index;
	int valeur = 0;

	while(string[i] != '\0')
	{
	    if (i >= 4096)
        {
            printf("index overflow in func ecris");
            break;
        }
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
    uncrypt(buffer, buffer);
}
