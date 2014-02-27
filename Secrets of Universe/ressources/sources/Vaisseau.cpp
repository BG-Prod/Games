/*
    Secrets of Universe
    Copyright (C) 2014  BG Prod

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

    Contact me : bgprod@outlook.com
*/

#include "Vaisseau.h"


using namespace std;


Vaisseau::Vaisseau() : energie(100), bouclier(100), coque(100), capteur(100), teleporteur(100), hypernavigateur(100), moteur(100)
{
    etat = GAUCHE;
    placeBouclier.x = 0;
    placeBouclier.y = 0;
    placeArme1.x = 100;
    placeArme1.y = 100;
    vitesse = 15;
    mobile = true;
    alive = true;
    activiteBouclier = false;
    bool_explosion = false;
    nb_explosion = 0;

    /// position du centre du vaisseau
    position.x = 500;
    position.y = 500;
}
/**
Vaisseau::Vaisseau(const Vaisseau &p_VaisseauACopier)
{

}
**/

Vaisseau::~Vaisseau()
{
    for(int i = 0; i<image.size(); ++i)
    {
        delete image[i];
    }
}

void Vaisseau::init(SDL_Surface** pic)
{
    image.push_back(new Image(cheminImage+"image02.png"));
    image[0]->resize(50);
    image.push_back(new Image(cheminImage+"image03.png"));
    image[1]->resize(50);
    image.push_back(new Image(cheminImage+"image05.png"));
    image[2]->resize(50);
    image.push_back(new Image(cheminImage+"image04.png"));
    image[3]->resize(50);
}

/**
void Vaisseau::attaquer(SDL_Surface* p_ouColler, Input p_in, SDL_Rect p_carton[],int p_listeDeg[])
{
    batterie->tirer(etat, p_ouColler, p_in, joueur, p_carton, p_listeDeg);
}

void Vaisseau::bouclier(SDL_Surface * p_ouColler, Input p_in)
{
    placeBouclier.x = position.x + (image[ACTUELLE]->w / 2) - (imageBouclier[BOUCLIER]->w / 2);
    placeBouclier.y = position.y + (image[ACTUELLE]->h / 2) - (imageBouclier[BOUCLIER]->h / 2);
    if(joueur == 1)
    {
        if (p_in.key[SDLK_RETURN] && bouclier > 0)
        {
            SDL_BlitSurface(imageBouclier[BOUCLIER], 0, p_ouColler, &placeBouclier);
            activiteBouclier = true;
            bouclier--;
        }
        else
        {
            activiteBouclier = false;
        }
    }
    if(joueur == 2)
    {
        if (p_in.key[SDLK_KP_ENTER] && bouclier > 0)
        {
            SDL_BlitSurface(imageBouclier[BOUCLIER], 0, p_ouColler, &placeBouclier);
            activiteBouclier = true;
            bouclier--;
        }
        else
        {
            activiteBouclier = false;
        }
    }
}

void Vaisseau::IA(SDL_Surface * p_ouColler, Input p_in, SDL_Rect p_carton[],int p_listeDeg[])
{
    if(alive)
    {
        placeArme1.y = position.y + 117;
        placeArme1.x = position.x + 68;

        if(mobile)
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

        batterie->actu(placeArme1);
        afficher(p_ouColler);
        attaquer(p_ouColler, p_in, p_carton, p_listeDeg);
        bouclier(p_ouColler, p_in);

    }

    if(!alive)
    {
        delete this;
    }

}

void Vaisseau::update(SDL_Surface* p_ou, SDL_Surface* p_ecran, Input p_in, SDL_Rect p_carton[],int p_listeDeg[])
{
    if(coque <= 0)
    {
        alive = false;
    }

    if(alive)
    {
        if(joueur == 1)
        {
            if(mobile)
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


            if(etat == HAUT)
                {placeArme1.y = position.y + 44;placeArme1.x = position.x + 19;imageBouclier[BOUCLIER] = imageBouclier[BOUCLIER_H];}
            if(etat == BAS)
                {placeArme1.y = position.y + 31;placeArme1.x = position.x + 19;imageBouclier[BOUCLIER] = imageBouclier[BOUCLIER_H];}
            if(etat == GAUCHE)
                {placeArme1.y = position.y + 19;placeArme1.x = position.x + 44;imageBouclier[BOUCLIER] = imageBouclier[BOUCLIER_W];}
            if(etat == DROITE)
                {placeArme1.y = position.y + 19;placeArme1.x = position.x + 31;imageBouclier[BOUCLIER] = imageBouclier[BOUCLIER_W];}
            if(etat == HD)
                {placeArme1.y = position.y + 45;placeArme1.x = position.x + 36;imageBouclier[BOUCLIER] = imageBouclier[BOUCLIER_DD];}
            if(etat == BD)
                {placeArme1.y = position.y + 36;placeArme1.x = position.x + 36;imageBouclier[BOUCLIER] = imageBouclier[BOUCLIER_DG];}
            if(etat == BG)
                {placeArme1.y = position.y + 36;placeArme1.x = position.x + 45;imageBouclier[BOUCLIER] = imageBouclier[BOUCLIER_DD];}
            if(etat == HG)
                {placeArme1.y = position.y + 45;placeArme1.x = position.x + 45;imageBouclier[BOUCLIER] = imageBouclier[BOUCLIER_DG];}
            if(p_in.key[SDLK_F1])
                {alive = false;}

            batterie->actu(placeArme1);
            SDL_BlitSurface(image[ACTUELLE], 0, p_ou, &position);
            if(bool_explosion){aniexplosion(p_ou);}
            attaquer(p_ou, p_in,p_carton, p_listeDeg);
            bouclier(p_ou, p_in);

        }

        if(joueur == 2)
        {
            IA(p_ou, p_in, p_carton, p_listeDeg);
        }
    }
}

void Vaisseau::aniexplosion(SDL_Surface * p_ou)
{
    if(nb_explosion > 17)
    {
        nb_explosion = 0;
        bool_explosion = false;
    }
    else
    {
        SDL_Rect selection = {nb_explosion*36,0,36,50};
        SDL_BlitSurface(explosion,&selection, p_ou, &placeArme1);
        nb_explosion++;
    }
}


Projectile Vaisseau::getTirs(int p_i)
{
    return batterie->getTir(p_i);
}

int Vaisseau::getActiviteArme()
{
    return batterie->getActiviteTir();
}

SDL_Rect Vaisseau::getPos()
{
    return position;
}

int Vaisseau::modCoque(int mod)
{
    if(this->activiteBouclier == false)
    {
        coque -= mod;
        if(mod > 0){bool_explosion = true;}
    }
    return coque;
}

int Vaisseau::getParametre(int x)
{
    int acc;
    if(x==0){acc = coque;}
    if(x==1){acc = bouclier;}
    return acc;
}
**/


void Vaisseau::move(direction d)
{
    switch(d)
    {
        case BAS:
            position.y += moteur*vitesse/100;
            break;
        case HAUT:
            position.y -= moteur*vitesse/100;
            break;
        case DROITE:
            position.x += moteur*vitesse/100;
            break;
        case GAUCHE:
            position.x -= moteur*vitesse/100;
            break;
    }
    etat = d;
}

void Vaisseau::print()
{
    image[etat]->print(position.x, position.y);
}

void Vaisseau::destroy()
{
    image[0]->rotate(100);
    image[1]->rotate(100);
    image[2]->rotate(100);
    image[3]->rotate(100);
}

void Vaisseau::resize(int a)
{
    image[0]->resize(a);
    image[1]->resize(a);
    image[2]->resize(a);
    image[3]->resize(a);
}
