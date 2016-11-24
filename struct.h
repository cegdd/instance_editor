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


enum{B_NORMAL, B_SURVOLER, B_CLIQUER, B_IMPOSSIBLE};/*bouton*/
enum{BLANC, ROUGE, GRIS, NOIR, VERT, BLEU};/*text color*/
enum{CREER, QUITTER, CHARGER, ENREGISTRER,MAP , DEPART, MONSTER, CROIXMONSTRE};
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


struct CREATURE
{
    bool actif;

    int vie;

    char filename[64];
    char name[64];
    char path[128];

    struct pict pict;
    struct BOUTON bouton;
    struct TEXTE tvie;
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

struct DIVERSsysteme
{

    bool shiftactif;
    bool altactif;
    bool moletteactif;
    bool projetouvert;

    bool asked;
    int askID;

    bool continuer;
    int echap;
    int typeclavier;
    int nbcreature;

    struct pict pointeur;
    struct CREATURE creature[128];

    SDL_Texture *BGmort;
    GLuint BG;
    SDL_Texture *BGblanc;


    SDL_Event evenement;

    SDL_Window *screen;

    TTF_Font *police;
    TTF_Font *police1;

	SDL_Rect pecran;
	SDL_Rect oldpp;
	SDL_Rect ppobj;
	SDL_Rect origine;

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
    struct pict fondmob;

    struct BOUTON *ListeBouton[64];
    int ListeNb;
};

struct CONSOLE
{
    struct pict shooton;
    struct pict shootoff;
    struct pict console;
    struct TEXTE texte[10];
    struct TEXTE ecris;
    struct SDL_Rect pos [10];
    int indice[10];
    int actif;
    char string[10][1024];
    char tampon[1024];
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
    struct hookpict monstre [512];
    int nbmonstre;

    char projectname [64];
    char projectmap [64];
};

#endif
