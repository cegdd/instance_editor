#include <stdio.h>
#include <stdlib.h>

#include "struct.h"
#include "systeme.h"
#include "editeur.h"
#include "save.h"

void saveproject (struct CONSOLE *console, struct DIVERSsysteme *systeme, struct DATA *data)
{
    char buffer[128];
    FILE *fichier = NULL;
    int i;

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
    //translation joueur en y
    sprintf(buffer, "%d", data->joueur.translation.y);
    ecris(buffer, fichier);

    //nombre de mobs
    sprintf(buffer, "%d", data->nbmonstre);
    ecris(buffer, fichier);

    for(i=0 ; i<data->nbmonstre ; i++)
    {
        sprintf(buffer, "%d", data->monstre[i].translation.x);
        ecris(buffer, fichier);
        sprintf(buffer, "%d", data->monstre[i].translation.y);
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
        char ret[50] = {'\0'};
        FILE *fichier = NULL;
        int i;

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

            //nom de la map
            lis(fichier, buffer);
            uncrypt(buffer, ret);

            loadingknownmap(console, systeme, data, ret);
            sprintf(temp, "map %s chargee", ret);
            say(temp, console, systeme);

            //si le joueur est poser
            lis(fichier, buffer);
            uncrypt(buffer, ret);
            if (ret[0] == '1')
            {
                //translation joueur en x
                lis(fichier, buffer);
                uncrypt(buffer, ret);
                data->joueur.translation.x = atoi(ret);
                //translation joueur en y
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

            //nombre de mobs
            lis(fichier, buffer);
            uncrypt(buffer, ret);
            data->nbmonstre = atoi(ret);

            for(i=0 ; i<data->nbmonstre ; i++)
            {
                //translation mob en x
                lis(fichier, buffer);
                uncrypt(buffer, ret);
                data->monstre[i].translation.x = atoi(ret);
                //translation mob en x
                lis(fichier, buffer);
                uncrypt(buffer, ret);
                data->monstre[i].translation.y = atoi(ret);
            }
            sprintf(temp, "%d monstres chargé", data->nbmonstre);
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
