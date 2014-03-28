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


Vaisseau::Vaisseau() : Object(), energie(100), bouclier(100), coque(100), capteur(100), teleporteur(100), hypernavigateur(100), moteur(100)
{
    etat = GAUCHE;
    vitesse = 15;
    type = 1;
    alive = true;
    activiteBouclier = false;

    /// position du centre du vaisseau
    position = Coordonnees(500,500,0,0,500,500,0,0);

    /// armes
    batterie = new Weapon(this);
}

Vaisseau::Vaisseau(int x, int y) : Object(), energie(100), bouclier(100), coque(100), capteur(100), teleporteur(100), hypernavigateur(100), moteur(100)
{
    etat = GAUCHE;
    vitesse = 15;
    type = 1;
    alive = true;
    activiteBouclier = false;

    /// position du centre du vaisseau
    position = Coordonnees(x,y,0,0,x,y,0,0);

    /// armes
    batterie = new Weapon(this);
}

Vaisseau::Vaisseau(int _energie, int _bouclier, int _coque, int _capteur, int _vitesse, int _joueur, int _type,
                 int _masse, int _teleporteur, int _hypernavigateur, int _moteur, int _id, Coordonnees _position,
                 direction _etat, Object * _ancestor)
{

}

Vaisseau::~Vaisseau()
{
    delete batterie;
}

void Vaisseau::move(direction d)
{
    switch(d)
    {
        case BAS:
            position.y(position.y()+(moteur*vitesse/100));
            break;
        case HAUT:
            position.y(position.y()-(moteur*vitesse/100));
            break;
        case DROITE:
            position.x(position.x()+(moteur*vitesse/100));
            break;
        case GAUCHE:
            position.x(position.x()-(moteur*vitesse/100));
            break;
    }
    etat = d;
}

void Vaisseau::shoot()
{
    batterie->use();
}

void Vaisseau::update(Input * in)
{
    if(in->get_touche(SDLK_UP))
    {
        move(HAUT);
    }
    else if(in->get_touche(SDLK_DOWN))
    {
        move(BAS);
    }
    else if(in->get_touche(SDLK_LEFT))
    {
        move(GAUCHE);
    }
    else if(in->get_touche(SDLK_RIGHT))
    {
        move(DROITE);
    }
    else if(in->get_touche(SDLK_SPACE))
    {
        destroy();
        in->set_touche(SDLK_SPACE,0);
    }
    else if(in->get_touche(SDLK_RETURN))
    {
        shoot();
        in->set_touche(SDLK_SPACE,0);
    }

    batterie->update();
}

void Vaisseau::destroy()
{

}

void Vaisseau::bot()
{
    if(position.x() < 0)
    {
        move(DROITE);
    }
    else if(position.x() > SDL_GetVideoSurface()->w)
    {
        move(GAUCHE);
    }
    else if(position.y() < 0)
    {
        move(BAS);
    }
    else if(position.y() > SDL_GetVideoSurface()->h)
    {
        move(HAUT);
    }
    else
    {
        move(etat);
    }

    batterie->update();
}



