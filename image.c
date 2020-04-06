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

void draw(GLuint texture, SDL_Rect *pos)
{
    glBindTexture(GL_TEXTURE_2D, texture);
    glBegin(GL_QUADS);
        glTexCoord2d(0,0);          glVertex2d(pos->x,pos->y);
        glTexCoord2d(0,1);          glVertex2d(pos->x,pos->y+pos->h);
        glTexCoord2d(1,1);          glVertex2d(pos->x+pos->w,pos->y+pos->h);
        glTexCoord2d(1,0);          glVertex2d(pos->x+pos->w,pos->y);
    glEnd();
}

void draw_hookpict(struct hookpict *image, SDL_Rect *support)
{
    image->pict.pos.x = support->x + image->translation.x;
    image->pict.pos.y = support->y + image->translation.y;

    glBindTexture(GL_TEXTURE_2D, image->pict.texture);
    glBegin(GL_QUADS);
        glTexCoord2d(0,0);          glVertex2d(image->pict.pos.x,image->pict.pos.y);
        glTexCoord2d(0,1);          glVertex2d(image->pict.pos.x,image->pict.pos.y+image->pict.pos.h);
        glTexCoord2d(1,1);          glVertex2d(image->pict.pos.x+image->pict.pos.w,image->pict.pos.y+image->pict.pos.h);
        glTexCoord2d(1,0);          glVertex2d(image->pict.pos.x+image->pict.pos.w,image->pict.pos.y);
    glEnd();
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

void draw_button(struct BOUTON *bouton)
{
    glBindTexture(GL_TEXTURE_2D, bouton->texture);
    switch(bouton->etat)
    {
        case B_IMPOSSIBLE:
            glColor3ub(255, 0, 0);
            break;
        case B_SURVOLER:
            glColor3ub(150, 150, 255);
            break;
        case B_INUSE:
        case B_CLIQUER:
            glColor3ub(0, 0, 255);
            break;
        default:
            glColor3ub(255, 255, 255);
            break;
    }
    glBegin(GL_QUADS);
        glTexCoord2d(0,0);          glVertex2d(bouton->pos.x,bouton->pos.y);
        glTexCoord2d(0,1);          glVertex2d(bouton->pos.x,bouton->pos.y+bouton->pos.h);
        glTexCoord2d(1,1);          glVertex2d(bouton->pos.x+bouton->pos.w,bouton->pos.y+bouton->pos.h);
        glTexCoord2d(1,0);          glVertex2d(bouton->pos.x+bouton->pos.w,bouton->pos.y);
    glEnd();

    glColor3ub(255, 255, 255);
}

void copypos(SDL_Rect *source, SDL_Rect *target)
{
    target->x = source->x;
    target->y = source->y;
    target->w = source->w;
    target->h = source->h;
}

void Sync_Moving_Pict(int time, struct moving_pict *m_pict)
{
    if (time - m_pict->time >= m_pict->delay)
    {
        m_pict->time = time;
        m_pict->current++;
        if(m_pict->current >= m_pict->frame)
        {
            m_pict->current = 0;
        }
        m_pict->pict.texture = m_pict->texture[m_pict->current];
    }
}

GLuint loadTextureandsize(const char * filename, struct SDL_Rect *pos)
{
    GLuint glID;
    SDL_Surface * picture_surface = NULL;
    SDL_Surface *gl_surface = NULL;
    SDL_Surface * gl_fliped_surface = NULL;
    Uint32 rmask, gmask, bmask, amask;
    SDL_PixelFormat format;

    picture_surface = IMG_Load(filename);
    if (picture_surface == NULL)
        {   printf ("surface not correctly loaded \n");
            return 0;}//0 is an error for opengl

    pos->w = picture_surface->w;
    pos->h = picture_surface->h;

#if SDL_BYTEORDER == SDL_BIG_ENDIAN

    rmask = 0xff000000;
    gmask = 0x00ff0000;
    bmask = 0x0000ff00;
    amask = 0x000000ff;
#else

    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = 0xff000000;
#endif

    format = *(picture_surface->format);
    format.BitsPerPixel = 32;
    format.BytesPerPixel = 4;
    format.Rmask = rmask;
    format.Gmask = gmask;
    format.Bmask = bmask;
    format.Amask = amask;

    gl_surface = SDL_ConvertSurface(picture_surface,&format,SDL_SWSURFACE);

    gl_fliped_surface = CEGDD_UI_flipSurface(gl_surface);

    glGenTextures(1, &glID);

    glBindTexture(GL_TEXTURE_2D, glID);


    glTexImage2D(GL_TEXTURE_2D, 0, 4, gl_fliped_surface->w,
                 gl_fliped_surface->h, 0, GL_RGBA,GL_UNSIGNED_BYTE,
                 gl_fliped_surface->pixels);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);


    SDL_FreeSurface(gl_fliped_surface);
    SDL_FreeSurface(gl_surface);
    SDL_FreeSurface(picture_surface);

    return glID;
}

void Turn_And_Draw (struct pict *img, float angle)
{
    SDL_Point temp;
    temp.x = img->pos.x;
    temp.y = img->pos.y;

    img->pos.x = 0 - (img->pos.w/2);
    img->pos.y = 0 - (img->pos.h/2);

	glTranslatef(temp.x+(img->pos.w/2), temp.y+(img->pos.h/2), 0);
	glRotatef(angle, 0, 0 ,1);

	CEGDD_UI_draw_pict(img);

	img->pos.x = temp.x;
	img->pos.y = temp.y;

    glLoadIdentity();
}

void turn_draw_hookpict(int angle, struct hookpict *image, SDL_Rect *support)
{
    glPushMatrix();

    image->pict.pos.x = support->x + image->translation.x;
    image->pict.pos.y = support->y + image->translation.y;

    Turn_And_Draw(&image->pict, angle);

    glPopMatrix();
}


void turn_draw_hookpict_selected(int angle, struct hookpict *image, SDL_Rect *support)
{
    glPushMatrix();
    glColor3ub(150, 150, 255);
    image->pict.pos.x = support->x + image->translation.x;
    image->pict.pos.y = support->y + image->translation.y;

    Turn_And_Draw(&image->pict, angle);
    glColor3ub(255, 255, 255);

    glPopMatrix();
}

void draw_coche(struct SDL_Rect *pos, bool state, struct UI *ui)
{
    if (state == false)
    {
        draw(ui->coche[0], pos);
    }
    else
    {
        draw(ui->coche[1], pos);
    }
}
