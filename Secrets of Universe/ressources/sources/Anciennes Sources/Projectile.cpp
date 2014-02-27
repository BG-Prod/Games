#include <SDL.h>
#include <SDL_image.h>
#include <string>

#include "Projectile.h"

using namespace std;

Projectile::Projectile(SDL_Surface ** p_images) : Objet(), m_degats(10), m_dir(-1)
{
    string lien, type;
    type =  "batterie";

    if(type == "batterie")
    {
        m_image[0] = p_images[31];
        m_degats = 5;
    }
    m_image[1] = NULL;
    m_position.x = 0;
    m_position.y = 0;
    m_position.w = m_image[0]->w;
    m_position.h = m_image[0]->h;
    m_tempsCreation = SDL_GetTicks();

    lien = cheminSon + "EXP_DEATH_2.WAV";
    /*FMOD_System_Create(&m_system);
    FMOD_System_Init(m_system, 2, FMOD_INIT_NORMAL, NULL);

    FMOD_System_CreateSound(m_system, lien.c_str(), FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM, 0, &m_musicBoom);
*/}

Projectile::Projectile(string p_type, SDL_Rect p_pos) : Objet(), m_degats(10), m_dir(-1)
{
    string lien;

    if(p_type == "batterie")
    {
        lien = cheminImage + "batterie.bmp";
        m_image[0] = SDL_DisplayFormat(IMG_Load(lien.c_str()));
        SDL_SetColorKey(m_image[0], SDL_SRCCOLORKEY, SDL_MapRGB(m_image[0]->format, 0, 183, 239));
        m_degats = 5;
    }
    m_image[1] = NULL;
    m_position.x = p_pos.x - m_image[0]->w / 2;
    m_position.y = p_pos.y - m_image[0]->h / 2;
    m_position.w = m_image[0]->w;
    m_position.h = m_image[0]->h;
    m_tempsCreation = SDL_GetTicks();

    /*lien = cheminSon + "EXP_DEATH_2.WAV";
    FMOD_System_Create(&m_system);
    FMOD_System_Init(m_system, 32, FMOD_INIT_NORMAL, NULL);

    FMOD_System_CreateSound(m_system, lien.c_str(), FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM, 0, &m_musicBoom);*/
}

Projectile::Projectile(const Projectile &p_projectileACopier) : m_dir(-1)
{
    m_image[0] = p_projectileACopier.m_image[0];
    m_image[1] = p_projectileACopier.m_image[1];
    m_degats = p_projectileACopier.m_degats;
    m_tempsCreation = p_projectileACopier.m_tempsCreation;
    m_tempsActuel = p_projectileACopier.m_tempsActuel;
    m_position = p_projectileACopier.m_position;
    m_alive = p_projectileACopier.m_alive;
}

Projectile::~Projectile()
{
    /*
    FMOD_Sound_Release(m_musicBoom);

    FMOD_System_Close(m_system);
    FMOD_System_Release(m_system);*/
}

void Projectile::afficher(SDL_Surface* p_ouColler)
{
    SDL_BlitSurface(m_image[0], 0, p_ouColler, &m_position);
}

void Projectile::IA(int p_etatVaisseau, SDL_Surface* p_ouColler, SDL_Rect p_carton[],int p_listeDeg[])
{
    m_tempsActuel = SDL_GetTicks();

    if(m_tempsActuel - m_tempsCreation >= 8192)
    {
        m_alive = false;
    }

    if(m_dir == -1)
    {
        m_dir = p_etatVaisseau;
    }

    if(m_alive)
    {
        if(m_dir == HAUT)
        {m_position.y -= 16;}
        if(m_dir == BAS)
        {m_position.y += 16;}
        if(m_dir == GAUCHE)
        {m_position.x -= 16;}
        if(m_dir == DROITE)
        {m_position.x += 16;}
        if(m_dir == HD)
        {m_position.y -= 11;m_position.x += 11;}
        if(m_dir == BD)
        {m_position.y += 11;m_position.x += 11;}
        if(m_dir == BG)
        {m_position.y += 11;m_position.x -= 11;}
        if(m_dir == HG)
        {m_position.y -= 11;m_position.x -= 11;}

        afficher(p_ouColler);
    }

    if(!m_alive)
    {
        //delete this;
    }

    for(int i = 0 ; i < 20 ; i++)
    {

            if(collision(m_position, p_carton[i]) && (m_tempsActuel - m_tempsCreation >= 512))
            {
                p_listeDeg[i] += m_degats;
                //FMOD_System_PlaySound(m_system, FMOD_CHANNEL_FREE, m_musicBoom, 0, NULL);
                m_alive = false;
            }

    }

}

SDL_Rect Projectile::getPosTir()
{
    return m_position;
}

bool Projectile::getBool()
{
    return m_alive;
}
