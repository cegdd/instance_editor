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


enum{B_NORMAL, B_SURVOLER, B_CLIQUER, B_IMPOSSIBLE, B_INUSE};/*bouton*/
enum{BLANC, ROUGE, GRIS, NOIR, VERT, BLEU};/*text color*/
enum{CREER, QUITTER, CHARGER, ENREGISTRER,MAP , DEPART, MONSTER, CROIXMONSTRE, CREERMOB, DETAIL_IMGPATH, DETAIL_LIFE,
    SUPPRMOB};//monster not used
enum{FERMER, OUVERT};


struct BOUTON
{
	GLuint texture;
	SDL_Rect pos;
	int etat;
};

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
struct BOUTON_TEXTE
{
	struct TEXTE texte;
	struct BOUTON bouton;
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

struct UI
{
    int UIfondmob;

    struct BOUTON creer;
    struct BOUTON quitter;
    struct BOUTON loadmap;
    struct BOUTON enregistrer;
    struct BOUTON charger;
    struct BOUTON depart;
    struct BOUTON monster;

    struct BOUTON fermer;
    struct BOUTON creermob;
    struct BOUTON supprmob;
    struct pict fondmob;

    struct BOUTON *ListeBouton[64];
    int ListeNb;
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
