#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>


#include <GL/gl.h>
#include <GL/glu.h>

#include "main.h"
#include "editeur.h"
#include "tableau.h"
#include "image.h"
#include "systeme.h"

int screenh, screenw;

int main (int argc, char *argv[])
{
    struct DIVERSsysteme systeme;
    SDL_GLContext contexteOpenGL;

	if (argc == *argv[0]){}/*just for warnings*/
	srand(2); /*define a random*/

    SDL_Init (SDL_INIT_VIDEO);
    atexit(SDL_Quit);
    TTF_Init();
    atexit(TTF_Quit);
    IMG_Init(IMG_INIT_PNG);
    atexit(IMG_Quit);

    initsystem(&systeme);

    systeme.screen = SDL_CreateWindow("Reconquete salvatrice", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 0, 0,SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN_DESKTOP);
    contexteOpenGL = SDL_GL_CreateContext(systeme.screen);
	SDL_GetWindowSize(systeme.screen , &screenw , &screenh);
	printf("OpenGL %s\n\n", glGetString(GL_VERSION));

	glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
	gluOrtho2D(0,screenw,0,screenh);
    glEnable(GL_TEXTURE_2D);
    glAlphaFunc(GL_GREATER,0.5f);
    glEnable(GL_ALPHA_TEST);



	editeur(&systeme);



	TTF_CloseFont(systeme.police1);
	TTF_CloseFont(systeme.police);
	SDL_GL_DeleteContext(contexteOpenGL);
    return EXIT_SUCCESS;
}
