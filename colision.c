#include "SDL2/SDL.h"
#include <math.h>
#include <stdio.h>
#include <stdbool.h>


extern int screenh, screenw;


bool colisionbox(SDL_Rect *A, SDL_Rect *B, bool pointeur)
{
	/*if cursor of the mouse(A) is inside zone B
	test on the upleft of zone A*/
	if (pointeur == true &&
    A->x >= B->x && A->x <= B->x+B->w && A->y+A->h >= B->y && A->y+A->h <= B->y+B->h)
	{
		return true;
	}
	/*else if zone A is inside B*/
	else if (pointeur == false &&
		A->x+A->w >= B->x && A->x <= B->x+B->w && A->y+A->h >= B->y && A->y <= B->y+B->h)
	{
		return true;
	}
	return false;
}
