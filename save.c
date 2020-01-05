#include <stdio.h>
#include <stdlib.h>

#include "save.h"
#include "systeme.h"
#include "editeur.h"
#include "ui.h"
/**
SAVE FILE DATA STRUCTURE

-string     map name
-int        number of espece
    *int        ID
    *string     name
    *string     img name
    *int        life
    *bool       aggressif   -> int  R de vision
    *int        vitesse
    *int        dps
    *int        R d'atk
    *int        hitlaps
-bool       player set
    -int        player x
    -int        player y
-int        number of mob set
    *int        ID
    *int        mob x
    *int        mob y
    *int        scale
    *int        angle
    *bool       fixe    ->  *int[]      path(to see)    ->  *bool   loop
**/

void saveproject (struct CONSOLE *console, struct DIVERSsysteme *systeme, struct DATA *data, struct UI *ui)
{
    char buffer[128];
    FILE *fichier = NULL;
    int i, j = 0, i2;

    systeme->asked = false;
    console->answered = false;

    sprintf(buffer, "rs/sauvegarde/%s.RSCryptedMap", data->projectname);
    fichier = fopen(buffer, "w+");
    //nom de la map
    ecris(data->projectmap, fichier);

    //number of espece
    sprintf(buffer, "%d", systeme->NBespece);
    ecris(buffer, fichier);
    for(i=0 ; i < systeme->NBespece ; i++)
    {
        //ID
        sprintf(buffer, "%d", i);
        ecris(buffer, fichier);
        //name
        sprintf(buffer, "%s", ESP_getname(i, systeme));
        ecris(buffer, fichier);
        //image name
        sprintf(buffer, "%s", ESP_getimgpath(i, systeme));
        ecris(buffer, fichier);
        //life
        sprintf(buffer, "%d", ESP_getlife(i, systeme));
        ecris(buffer, fichier);
        // aggressif
        sprintf(buffer, "%d", ui->aggressif_state[i]);
        ecris(buffer, fichier);
        if (buffer[0] == '1')
        {
            // rayon de vision
            sprintf(buffer, "%d", systeme->creature[i].Rvision);
            ecris(buffer, fichier);
        }
        // vitesse
        sprintf(buffer, "%d", systeme->creature[i].vitesse);
        ecris(buffer, fichier);
        // dps
        sprintf(buffer, "%d", systeme->creature[i].dps);
        ecris(buffer, fichier);
        // Ratk
        sprintf(buffer, "%d", systeme->creature[i].Ratk);
        ecris(buffer, fichier);
        // hitlaps
        sprintf(buffer, "%d", systeme->creature[i].hitlaps);
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
    for(i=0 ; i < data->nbmonstre ; i++)
    {
        if (data->mob[i].actif == true)
        {
            j++;
        }
    }
    sprintf(buffer, "%d", j);
    ecris(buffer, fichier);

    for(i=0 ; i < data->nbmonstre ; i++)
    {
        if(data->mob[i].actif == false)
        {
            i++;
        }
        //ID creature
        sprintf(buffer, "%d", data->mob[i].ID);
        ecris(buffer, fichier);
        //x
        sprintf(buffer, "%d", data->mob[i].monstre.translation.x);
        ecris(buffer, fichier);
        //y
        sprintf(buffer, "%d", data->mob[i].monstre.translation.y);
        ecris(buffer, fichier);
        //scale
        sprintf(buffer, "%f", data->mob[i].scale);
        ecris(buffer, fichier);
        //angle
        sprintf(buffer, "%d", data->mob[i].angle);
        ecris(buffer, fichier);
        //fixe
        sprintf(buffer, "%d", ui->fixe_state[i]);
        ecris(buffer, fichier);
        if(buffer[0] == '0')
        {
            //number
            sprintf(buffer, "%d", data->mob[i].path.counter);
            ecris(buffer, fichier);
            for(i2 = 0 ; i2 < data->mob[i].path.counter ; i2++)
            {
                //x
                sprintf(buffer, "%d", data->mob[i].path.x[i2]);
                ecris(buffer, fichier);
                //y
                sprintf(buffer, "%d", data->mob[i].path.y[i2]);
                ecris(buffer, fichier);
            }
            if (data->mob[i].path.counter > 0)
            {
                //loop
                sprintf(buffer, "%d", ui->loop_state[i]);
                ecris(buffer, fichier);
            }
        }
    }

    fclose(fichier);
    say("projet enregistre avec succes", console, systeme);
}

bool loadproject (struct CONSOLE *console, struct DIVERSsysteme *systeme, struct DATA *data, struct UI *ui)
{
    if (console->answered)
    {
        char temp[128];
        char buffer[4096] = {'\0'};
        FILE *fichier = NULL;
        int i, i2;

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

            //nombre de creature
            lis(fichier, buffer);

            systeme->NBespece = atoi(buffer);
            for(i = 0 ; i < systeme->NBespece ; i++)
            {
                ESP_setboutonstate(B_NORMAL, i, systeme);
                //ID same as i
                lis(fichier, buffer);
                //name
                lis(fichier, buffer);
                ESP_setname(buffer, i, systeme);
                //image
                lis(fichier, buffer);
                ESP_setimgpath(buffer, i, systeme);
                //vie
                lis(fichier, buffer);
                ESP_setlife(atoi(buffer), i, systeme);
                //aggressif
                lis(fichier, buffer);
                ui->aggressif_state[i] = atoi(buffer);
                if(ui->aggressif_state[i] == true)
                {
                    lis(fichier, buffer);
                    systeme->creature[i].Rvision = atoi(buffer);
                }
                lis(fichier, buffer);
                systeme->creature[i].vitesse = atoi(buffer);
                lis(fichier, buffer);
                systeme->creature[i].dps = atoi(buffer);
                lis(fichier, buffer);
                systeme->creature[i].Ratk = atoi(buffer);
                lis(fichier, buffer);
                systeme->creature[i].hitlaps = atoi(buffer);
            }
            sprintf(temp, "%d monstre en memoire", systeme->NBespece);
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
            ESP_refreshmob(systeme);

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
                //translation mob en y
                lis(fichier, buffer);
                data->mob[i].monstre.translation.y = atoi(buffer);
                //echelle
                lis(fichier, buffer);
                data->mob[i].scale = atof(buffer);
                //angle
                lis(fichier, buffer);
                data->mob[i].angle = atoi(buffer);
                //fixe
                lis(fichier, buffer);
                ui->fixe_state[i] = atoi(buffer);
                if (ui->fixe_state[i] == false)
                {
                    //compteur
                    lis(fichier, buffer);
                    data->mob[i].path.counter = atoi(buffer);
                    for (i2 = 0 ; i2 < data->mob[i].path.counter ; i2++)
                    {
                        lis(fichier, buffer);
                        data->mob[i].path.nb[i2].translation.x = atoi(buffer);
                        lis(fichier, buffer);
                        data->mob[i].path.nb[i2].translation.y = atoi(buffer);
                        data->mob[i].path.used[i2] = true;
                    }
                    if (data->mob[i].path.counter > 0)
                    {
                        lis(fichier, buffer);
                        data->mob[i].path.loop = atoi(buffer);
                    }
                }

                data->mob[i].actif = true;
                data->mob[i].monstre.pict.texture = ESP_gettexture(data->mob[i].ID, systeme);
                setPos4(&data->mob[i].monstre.pict.pos, 0, 0, ESP_getwidth(data->mob[i].ID, systeme), ESP_gethight(data->mob[i].ID, systeme));
                setPos4(&data->mob[i].old, 0, 0, ESP_getwidth(data->mob[i].ID, systeme), ESP_gethight(data->mob[i].ID, systeme));
            }
            sprintf(temp, "%d monstre poser", data->nbmonstre);
            say(temp, console, systeme);

            systeme->projetouvert = true;
            fclose(fichier);
            return EXIT_SUCCESS;
        }
        else
        {
            say("no project founded", console, systeme);
        }
    }
    return EXIT_FAILURE;
}


void ecris(char buffer[50], FILE *fichier)
{
	int i = 0, index;
	int valeur = 0;

	while(buffer[i] != '\0')
	{
	    if (i >= 4096)
        {
            printf("index overflow in func ecris");
            break;
        }
		valeur = (int)buffer[i];
		for(index = 0 ; index < valeur ; index++)
		{
			fputc('O', fichier);
		}
		fputc('0', fichier);
		i++;
	}
    fputc('#', fichier);
}


void uncrypt(char buffer[4096], char *ret)
{
	int i = 0, index = 0;
	int compteur = 0;

	while(buffer[i] != '\0')
	{
		while(buffer[i] == 'O')
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
