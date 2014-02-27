#include "Vaisseau.h"


using namespace std;


Vaisseau::Vaisseau() : Etre(), m_energie(100), m_bouclier(100), m_coque(100), m_capteur(100), m_teleporteur(100), m_hypernavigateur(100), m_moteur(100)
{
    m_etat = GAUCHE;
    m_placeBouclier.x = 0;
    m_placeBouclier.y = 0;
    m_placeArme1.x = 100;
    m_placeArme1.y = 100;
    m_mobile = true;
    m_alive = true;
    m_activiteBouclier = false;
    m_bool_explosion = false;
    m_nb_explosion = 0;

    string lien;

    lien = cheminImage + "bouclier.png";
    m_imageBouclier[BOUCLIER_W] = IMG_Load(lien.c_str());

    lien = cheminImage + "bouclierH.png";
    m_imageBouclier[BOUCLIER_H] = IMG_Load(lien.c_str());

    lien = cheminImage + "bouclierDD.png";
    m_imageBouclier[BOUCLIER_DD] = IMG_Load(lien.c_str());

    lien = cheminImage + "bouclierDG.png";
    m_imageBouclier[BOUCLIER_DG] = IMG_Load(lien.c_str());

    lien = cheminImage + "boom.bmp";
    m_image[DETRUIT] = IMG_Load(lien.c_str());

    m_imageBouclier[BOUCLIER] = m_imageBouclier[BOUCLIER_H];

    m_batterie = new Arme("batterie", m_placeArme1);

    lien = cheminImage + "explosion.png";
    m_explosion = SDL_DisplayFormat(IMG_Load(lien.c_str()));
    SDL_SetColorKey(m_explosion, SDL_SRCCOLORKEY, SDL_MapRGB(SDL_GetVideoSurface()->format, 0, 0, 0));
}

Vaisseau::Vaisseau(const Vaisseau &p_VaisseauACopier)
{

}

Vaisseau::~Vaisseau()
{
    for(int i = 0 ; i < 5 ; i++)
    {
        if(i != BOUCLIER)
            SDL_FreeSurface(m_imageBouclier[i]);
    }

    SDL_FreeSurface(m_explosion);
    delete m_batterie;
}

void Vaisseau::attaquer(SDL_Surface* p_ouColler, Input p_in, SDL_Rect p_carton[],int p_listeDeg[])
{
    m_batterie->tirer(m_etat, p_ouColler, p_in, m_joueur, p_carton, p_listeDeg);
}

void Vaisseau::bouclier(SDL_Surface * p_ouColler, Input p_in)
{
    m_placeBouclier.x = m_position.x + (m_image[ACTUELLE]->w / 2) - (m_imageBouclier[BOUCLIER]->w / 2);
    m_placeBouclier.y = m_position.y + (m_image[ACTUELLE]->h / 2) - (m_imageBouclier[BOUCLIER]->h / 2);
    if(m_joueur == 1)
    {
        if (p_in.key[SDLK_RETURN] && m_bouclier > 0)
        {
            SDL_BlitSurface(m_imageBouclier[BOUCLIER], 0, p_ouColler, &m_placeBouclier);
            m_activiteBouclier = true;
            m_bouclier--;
        }
        else
        {
            m_activiteBouclier = false;
        }
    }
    if(m_joueur == 2)
    {
        if (p_in.key[SDLK_KP_ENTER] && m_bouclier > 0)
        {
            SDL_BlitSurface(m_imageBouclier[BOUCLIER], 0, p_ouColler, &m_placeBouclier);
            m_activiteBouclier = true;
            m_bouclier--;
        }
        else
        {
            m_activiteBouclier = false;
        }
    }
}

void Vaisseau::IA(SDL_Surface * p_ouColler, Input p_in, SDL_Rect p_carton[],int p_listeDeg[])
{
    if(m_alive)
    {
        m_placeArme1.y = m_position.y + 117;
        m_placeArme1.x = m_position.x + 68;

        if(m_mobile)
        {
        if (p_in.key[SDLK_KP8])
            moveUp();
        if (p_in.key[SDLK_KP2])
            moveDown();
        if (p_in.key[SDLK_KP4])
            moveLeft();
        if (p_in.key[SDLK_KP6])
            moveRight();
        if (p_in.key[SDLK_KP9])
            moveDiag45();
        if (p_in.key[SDLK_KP3])
            moveDiag135();
        if (p_in.key[SDLK_KP1])
            moveDiag225();
        if (p_in.key[SDLK_KP7])
            moveDiag315();
        }

        m_batterie->actu(m_placeArme1);
        afficher(p_ouColler);
        attaquer(p_ouColler, p_in, p_carton, p_listeDeg);
        bouclier(p_ouColler, p_in);

    }

    if(!m_alive)
    {
        delete this;
    }

}

void Vaisseau::update(SDL_Surface* p_ou, SDL_Surface* p_ecran, Input p_in, SDL_Rect p_carton[],int p_listeDeg[])
{
    if(m_coque <= 0)
    {
        m_alive = false;
    }

    if(m_alive)
    {
        if(m_joueur == 1)
        {
            if(m_mobile)
            {
            if (p_in.key[SDLK_UP] && !p_in.key[SDLK_RIGHT] && !p_in.key[SDLK_LEFT])
            {
                moveUp();
            }
            if (p_in.key[SDLK_DOWN] && !p_in.key[SDLK_RIGHT] && !p_in.key[SDLK_LEFT])
            {
                moveDown();
            }
            if (p_in.key[SDLK_RIGHT] && !p_in.key[SDLK_UP] && !p_in.key[SDLK_DOWN])
            {
                moveRight();
            }
            if (p_in.key[SDLK_LEFT] && !p_in.key[SDLK_UP] && !p_in.key[SDLK_DOWN])
            {
                moveLeft();
            }
            if (p_in.key[SDLK_UP] && p_in.key[SDLK_RIGHT] && !p_in.key[SDLK_DOWN] && !p_in.key[SDLK_LEFT])
            {
                moveDiag45();
            }
            if (p_in.key[SDLK_DOWN] && p_in.key[SDLK_LEFT] && !p_in.key[SDLK_UP] && !p_in.key[SDLK_RIGHT])
            {
                moveDiag225();
            }
            if (p_in.key[SDLK_RIGHT] && p_in.key[SDLK_DOWN] && !p_in.key[SDLK_UP] && !p_in.key[SDLK_LEFT])
            {
                moveDiag135();
            }
            if (p_in.key[SDLK_LEFT] && p_in.key[SDLK_UP] && !p_in.key[SDLK_DOWN] && !p_in.key[SDLK_RIGHT])
            {
                moveDiag315();
            }
            }


            if(m_etat == HAUT)
                {m_placeArme1.y = m_position.y + 44;m_placeArme1.x = m_position.x + 19;m_imageBouclier[BOUCLIER] = m_imageBouclier[BOUCLIER_H];}
            if(m_etat == BAS)
                {m_placeArme1.y = m_position.y + 31;m_placeArme1.x = m_position.x + 19;m_imageBouclier[BOUCLIER] = m_imageBouclier[BOUCLIER_H];}
            if(m_etat == GAUCHE)
                {m_placeArme1.y = m_position.y + 19;m_placeArme1.x = m_position.x + 44;m_imageBouclier[BOUCLIER] = m_imageBouclier[BOUCLIER_W];}
            if(m_etat == DROITE)
                {m_placeArme1.y = m_position.y + 19;m_placeArme1.x = m_position.x + 31;m_imageBouclier[BOUCLIER] = m_imageBouclier[BOUCLIER_W];}
            if(m_etat == HD)
                {m_placeArme1.y = m_position.y + 45;m_placeArme1.x = m_position.x + 36;m_imageBouclier[BOUCLIER] = m_imageBouclier[BOUCLIER_DD];}
            if(m_etat == BD)
                {m_placeArme1.y = m_position.y + 36;m_placeArme1.x = m_position.x + 36;m_imageBouclier[BOUCLIER] = m_imageBouclier[BOUCLIER_DG];}
            if(m_etat == BG)
                {m_placeArme1.y = m_position.y + 36;m_placeArme1.x = m_position.x + 45;m_imageBouclier[BOUCLIER] = m_imageBouclier[BOUCLIER_DD];}
            if(m_etat == HG)
                {m_placeArme1.y = m_position.y + 45;m_placeArme1.x = m_position.x + 45;m_imageBouclier[BOUCLIER] = m_imageBouclier[BOUCLIER_DG];}
            if(p_in.key[SDLK_F1])
                {m_alive = false;}

            m_batterie->actu(m_placeArme1);
            SDL_BlitSurface(m_image[ACTUELLE], 0, p_ou, &m_position);
            if(m_bool_explosion){anim_explosion(p_ou);}
            attaquer(p_ou, p_in,p_carton, p_listeDeg);
            bouclier(p_ou, p_in);

        }

        if(m_joueur == 2)
        {
            IA(p_ou, p_in, p_carton, p_listeDeg);
        }
    }
}

void Vaisseau::anim_explosion(SDL_Surface * p_ou)
{
    if(m_nb_explosion > 17)
    {
        m_nb_explosion = 0;
        m_bool_explosion = false;
    }
    else
    {
        SDL_Rect selection = {m_nb_explosion*36,0,36,50};
        SDL_BlitSurface(m_explosion,&selection, p_ou, &m_placeArme1);
        m_nb_explosion++;
    }
}


Projectile Vaisseau::getTirs(int p_i)
{
    return m_batterie->getTir(p_i);
}

int Vaisseau::getActiviteArme()
{
    return m_batterie->getActiviteTir();
}

SDL_Rect Vaisseau::getPos()
{
    return m_position;
}

int Vaisseau::modCoque(int mod)
{
    if(this->m_activiteBouclier == false)
    {
        m_coque -= mod;
        if(mod > 0){m_bool_explosion = true;}
    }
    return m_coque;
}

int Vaisseau::getParametre(int x)
{
    int acc;
    if(x==0){acc = m_coque;}
    if(x==1){acc = m_bouclier;}
    return acc;
}
