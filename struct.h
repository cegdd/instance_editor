#ifndef LOGINH
#define LOGINH

#include <stdio.h>
#include <stdbool.h>
#include <SDL_ttf.h>
#include <GL/gl.h>
#include <GL/glu.h>



/*####     OS     ######*/
#define WINDOWS 1
/*####logging rapide ####*/

#define TAILLE_POLICE 18



enum{BLANC, ROUGE, GRIS, NOIR, VERT, BLEU};/*text color*/

struct pict
{
    SDL_Rect pos;
    int x;
    int y;
    GLuint texture;
};

struct TEXTE
{
    struct pict img;
	int lenght;
	int high;
};

struct hookpict
{
    struct pict pict;
    SDL_Point translation;
};

struct moving_pict
{
    struct pict pict;
    GLuint texture[16];
    int frame;
    int current;
    int delay;
    int time;
};

struct MOB
{
    bool actif;
    bool selected;
    int state;
    struct hookpict monstre;
    int vie;
    int ID;
    char name[128];
};

struct CONSOLE
{
    struct pict shooton;
    struct pict cursor;
    struct pict shootoff;
    struct pict console;
    struct TEXTE texte[10];
    struct TEXTE ecris;
    struct SDL_Rect pos [10];
    int indice[10];
    int LenToCursor;
    int actif;
    char string[10][1024];
    char tampon[1024];
    char TamponToCursor[1024];
    char lastanswer[1024];
    short curseur;
    bool answered;
    bool active;
};

struct DATA
{
    bool joueuractif;

    struct pict map;
    struct hookpict joueur;
    struct MOB mob[512];
    int nbmonstre;
    int mob_selected;

    char projectname [64];
    char projectmap [64];
};
#endif
