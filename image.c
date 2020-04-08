#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_image.h"

#include <GL/gl.h>
#include <GL/glu.h>

#include "systeme.h"
#include "ui.h"

#include <LIBcegdd_ui.h>

void draw_pict_selected(struct pict *image)
{
    glBindTexture(GL_TEXTURE_2D, image->texture);
    glColor3ub(150, 150, 255);
    glBegin(GL_QUADS);
        glTexCoord2d(0,0);          glVertex2d(image->pos.x,image->pos.y);
        glTexCoord2d(0,1);          glVertex2d(image->pos.x,image->pos.y+image->pos.h);
        glTexCoord2d(1,1);          glVertex2d(image->pos.x+image->pos.w,image->pos.y+image->pos.h);
        glTexCoord2d(1,0);          glVertex2d(image->pos.x+image->pos.w,image->pos.y);
    glEnd();
    glColor3ub(255, 255, 255);
}

void draw_hookpict_selected(struct hookpict *image, SDL_Rect *support)
{
    image->pict.pos.x = support->x + image->translation.x;
    image->pict.pos.y = support->y + image->translation.y;

    glBindTexture(GL_TEXTURE_2D, image->pict.texture);
    glColor3ub(150, 150, 255);
    glBegin(GL_QUADS);
        glTexCoord2d(0,0);          glVertex2d(image->pict.pos.x,image->pict.pos.y);
        glTexCoord2d(0,1);          glVertex2d(image->pict.pos.x,image->pict.pos.y+image->pict.pos.h);
        glTexCoord2d(1,1);          glVertex2d(image->pict.pos.x+image->pict.pos.w,image->pict.pos.y+image->pict.pos.h);
        glTexCoord2d(1,0);          glVertex2d(image->pict.pos.x+image->pict.pos.w,image->pict.pos.y);
    glEnd();
    glColor3ub(255, 255, 255);
}

void draw_color_black(SDL_Rect *pos)
{
    glColor3ub(0, 0, 0);
        glBegin(GL_QUADS);
            glVertex2d(pos->x,pos->y);
            glVertex2d(pos->x,pos->y+pos->h);
            glVertex2d(pos->x+pos->w,pos->y+pos->h);
            glVertex2d(pos->x+pos->w,pos->y);
        glEnd();
    glColor3ub(255, 255, 255);
}

void turn_draw_hookpict_selected(int angle, struct hookpict *image, SDL_Rect *support)
{
    glPushMatrix();
    glColor3ub(150, 150, 255);
    image->pict.pos.x = support->x + image->translation.x;
    image->pict.pos.y = support->y + image->translation.y;

    CEGDD_UI_Turn_And_Draw(&image->pict, angle);
    glColor3ub(255, 255, 255);

    glPopMatrix();
}

void draw_coche(struct SDL_Rect *pos, bool state, struct UI *ui)
{
    if (state == false)
    {
        CEGDD_UI_draw(ui->coche[0], pos);
    }
    else
    {
        CEGDD_UI_draw(ui->coche[1], pos);
    }
}
