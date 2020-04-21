#ifndef IMAGEH
#define IMAGEH

#include "SDL2/SDL_ttf.h"
#include <GL/gl.h>
#include <GL/glu.h>

#include "LIBcegdd_ui.h"

struct BOUTON;
struct DIVERSsysteme;
struct UI;

void draw_pict_selected(struct pict *image);
void draw_color_black(SDL_Rect *pos);

void draw_hookpict_selected(struct hookpict *image, SDL_Rect *support);

void turn_draw_hookpict_selected(int angle, struct hookpict *image, SDL_Rect *support);
void draw_coche(struct SDL_Rect *pos, bool state, struct UI *ui);
#endif
