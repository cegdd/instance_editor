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

struct pict
{
    SDL_Rect pos;
    GLuint texture;
};
struct TEXTE
{
    struct pict img;
	int lenght;
	int high;
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

struct BOUTON
{
	GLuint texture;
	SDL_Rect pos;
	int etat;
};



struct DIVERSsysteme
{

    bool shiftactif;
    bool altactif;
    bool inbattle;
    bool continuer;
    int echap;
    int typeclavier;

    struct pict pointeur;

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

};

struct UI
{
    struct BOUTON creer;
    struct BOUTON quitter;
};

struct CONSOLE
{
    struct pict console;
    struct TEXTE texte[10];
    struct SDL_Rect pos [10];
    int indice[10];
    int actif;
    char string[10][1024];
};

#endif
