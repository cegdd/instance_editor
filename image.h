#ifndef IMAGEH
#define IMAGEH

#include "SDL2/SDL_ttf.h"
#include <GL/gl.h>
#include <GL/glu.h>

#include "LIBcegdd_ui.h"

struct BOUTON;
struct DIVERSsysteme;
struct UI;

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

GLuint loadTextureandsize(const char *filename, struct SDL_Rect *pos);

void draw_pict_selected(struct pict *image);
void draw(GLuint texture, SDL_Rect *pos);
void draw_button(struct BOUTON *bouton);
void draw_color_black(SDL_Rect *pos);
void copypos(SDL_Rect *source, SDL_Rect *target);
void Turn_And_Draw (struct pict *img, float angle);
void Sync_Moving_Pict(int time, struct moving_pict *m_pict);

void draw_hookpict(struct hookpict *image, SDL_Rect *support);
void draw_hookpict_selected(struct hookpict *image, SDL_Rect *support);

void turn_draw_hookpict(int angle, struct hookpict *image, SDL_Rect *support);

void turn_draw_hookpict_selected(int angle, struct hookpict *image, SDL_Rect *support);
void draw_coche(struct SDL_Rect *pos, bool state, struct UI *ui);
#endif
