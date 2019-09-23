#ifndef IMAGEH
#define IMAGEH

#include "C:\Users\antoi\Documents\programation\SDL2\SDL_ttf.h"
#include <GL/gl.h>
#include <GL/glu.h>

struct BOUTON;
struct DIVERSsysteme;
struct UI;

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

SDL_Texture* LoadingImage(char* emplacement, int transparence,struct DIVERSsysteme *systeme);

Uint8 obtenirPixel(SDL_Surface *surface, SDL_Point *pix);

SDL_Surface * flipSurface(SDL_Surface * surface);

GLuint convertTexture(SDL_Surface *surface);
GLuint loadTexture(const char * filename);
GLuint loadTextureandsize(const char *filename, struct SDL_Rect *pos);
GLuint imprime (char s[], int len, int couleur,struct DIVERSsysteme *systeme, int *LenghtReturn, int *HighReturn);

void draw_pict(struct pict *image);
void draw_pict_selected(struct pict *image);
void draw_limitedpict(struct pict *image, SDL_Rect *pos);
void draw(GLuint texture, SDL_Rect *pos);
void draw_button(struct BOUTON *bouton);
void draw_color_black(SDL_Rect *pos);

void setPos4(SDL_Rect *pos, int x, int y, int w, int h);
void setPos2(SDL_Rect *pos, int x, int y);
void copypos(SDL_Rect *source, SDL_Rect *target);
void Turn_And_Draw (struct pict *img, float angle);
void Sync_Moving_Pict(int time, struct moving_pict *m_pict);

void draw_hookpict(struct hookpict *image, SDL_Rect *support);
void draw_hookpict_selected(struct hookpict *image, SDL_Rect *support);

void turn_draw_hookpict(int angle, struct hookpict *image, SDL_Rect *support);

void turn_draw_hookpict_selected(int angle, struct hookpict *image, SDL_Rect *support);
void draw_coche(struct SDL_Rect *pos, bool state, struct UI *ui);
#endif
