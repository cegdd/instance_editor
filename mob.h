#ifndef MOBH
#define MOBH

#include <stdio.h>
#include <stdlib.h>

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <stdbool.h>

#include "image.h"
#include "path.h"

struct MOB
{
    struct PATH path;
    struct SDL_Rect old;
    bool actif;
    bool selected;
    int state;
    struct hookpict monstre;
    int vie;
    int angle;
    double scale;
    int ID;
    char name[128];
};

#endif
