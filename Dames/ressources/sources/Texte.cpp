#include "Texte.h"


using namespace std;


Texte::Texte()
{
    m_lien = cheminFile + "texte.txt";
    m_place_base = {HAUTEUR_ECRAN+(120./840.)*HAUTEUR_ECRAN,(840./1080.)*HAUTEUR_ECRAN,0,0};
    m_place_var = {0,0,0,0};
    m_nombre = nombreLignes(m_lien.c_str())-1;
    m_id = 0;
    m_taille = 20;
    blanc = {255,255,255};
    gris_clair = {200,200,200};
    gris_fonce = {50,50,50};
    noir = {0,0,0};
    m_couleur = noir;
    m_phrases = new string[m_nombre];
    for(int i = 0 ; i < m_nombre ; i++)
    {
        m_phrases[i] = niemeLigne(m_lien.c_str(), i);
    }
    m_text_image = NULL;
    m_phrase_image = new SDL_Surface*[m_nombre];
    for(int i = 0 ; i < m_nombre ; i++)
    {
        m_phrase_image[i] = NULL;
    }
    m_lien = cheminPolice + "calibri" + ".ttf";
    m_style = TTF_OpenFont(m_lien.c_str(),m_taille);
}

Texte::~Texte()
{
    erase_text();
    TTF_CloseFont(m_style);
}

void Texte::load_text()
{
    for(int i = 0 ; i < m_nombre ; i++)
    {
        m_place_var = m_place_base;
        create_text(m_phrases[i].c_str(), "calibri", m_taille, m_couleur);
        m_phrase_image[i] = copieSurface(m_text_image);
    }
}

void Texte::erase_text()
{
    delete [] m_phrases;
    for(int i = 0 ; i < m_nombre ; i++)
    {
        if(m_phrase_image[i] != NULL)
        {
            SDL_FreeSurface(m_phrase_image[i]);
        }
    }
    delete [] m_phrase_image;
}

void Texte::copy_picture(SDL_Surface * origin, SDL_Surface * destination)
{
    if(destination != NULL)
    {
        SDL_FreeSurface(destination);
    }

    destination = SDL_CreateRGBSurface(SDL_HWSURFACE, origin->w, origin->h,
                                       origin->format->BitsPerPixel,
                                       origin->format->Rmask,
                                       origin->format->Gmask,
                                       origin->format->Bmask,
                                       origin->format->Amask);

    destination = SDL_DisplayFormatAlpha(origin);
}

void Texte::create_text(string p_string, string p_police, int p_taille, SDL_Color p_couleur)
{
    m_taille = p_taille;
    m_couleur = p_couleur;
    m_lien = cheminPolice + p_police + ".ttf";
    TTF_CloseFont(m_style);
    m_style = TTF_OpenFont(m_lien.c_str(), m_taille);
    if(m_text_image != NULL)
    {
        SDL_FreeSurface(m_text_image);
    }
    m_text_image = TTF_RenderText_Blended(m_style, p_string.c_str(), m_couleur);
}

void Texte::create_text(string p_string)
{
    SDL_FreeSurface(m_text_image);
    m_text_image = TTF_RenderText_Blended(m_style, p_string.c_str(), m_couleur);
}

void Texte::print_text(string p_text, std::string p_police, int p_taille, SDL_Color p_couleur, int x, int y)
{
    m_place_var.x = x;
    m_place_var.y = y;
    create_text(p_text, p_police, p_taille, p_couleur);
    SDL_BlitSurface(m_text_image,NULL,SDL_GetVideoSurface(),&m_place_var);
}

void Texte::print_text(int x, int y)
{
    m_place_var.x = x;
    m_place_var.y = y;
    SDL_BlitSurface(m_text_image,NULL,SDL_GetVideoSurface(),&m_place_var);
}

void Texte::print_text()
{
    SDL_BlitSurface(m_text_image,NULL,SDL_GetVideoSurface(),&m_place_var);
}

void Texte::print_text(int k)
{
    SDL_BlitSurface(m_phrase_image[k],NULL,SDL_GetVideoSurface(),&m_place_base);
}

void Texte::print_text(int k, int x, int y)
{
    m_place_var.x = x;
    m_place_var.y = y;
    SDL_BlitSurface(m_phrase_image[k],NULL,SDL_GetVideoSurface(),&m_place_var);
}

void Texte::chose_text(int k)
{
    if(k >= 0 && k < m_nombre)
    {
        m_text_image = m_phrase_image[k];
    }
}

