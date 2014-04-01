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
    outOf = -1;
    touched = false;

    /// position du centre du vaisseau
    position = Coordonnees(500,500,350,350,500,500,350,350);

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
    outOf = -1;
    touched = false;

    /// position du centre du vaisseau
    position = Coordonnees(x,y,350,350,x,y,350,350);

    /// armes
    batterie = new Weapon(this);
}

Vaisseau::Vaisseau(int _energie, int _bouclier, int _coque, int _capteur, int _vitesse, int _joueur, int _type,
                 int _masse, int _teleporteur, int _hypernavigateur, int _moteur, int _id, Coordonnees _position,
                 direction _etat, Object * _ancestor)
{
    energie = _energie;
    bouclier =  _bouclier;
    coque =  _coque;
    capteur =  _capteur;
    vitesse =  _vitesse;
    joueur =  _joueur;
    type =  _type,
    masse = _masse;
    teleporteur =  _teleporteur;
    hypernavigateur =  _hypernavigateur;
    moteur =  _moteur;
    id =  _id;
    position = _position;
    etat = _etat;
    ancestor = _ancestor;
    outOf = -1;
    touched = false;
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

    batterie->update();
}

void Vaisseau::destroy()
{

}

void Vaisseau::bot()
{
    if(-1==outOf)
    {
        int change = random(0,100);
        if(change==1){move((direction)random(0,3));}
        else{move(etat);}
    }
    else
    {
        if(outOf==BAS)
            move(HAUT);
        else if(outOf==HAUT)
            move(BAS);
        else if(outOf==GAUCHE)
            move(DROITE);
        else if(outOf==DROITE)
            move(GAUCHE);
        outOf = -1;
    }
    if(touched)
    {
        if(etat==BAS)
            move(HAUT);
        else if(etat==HAUT)
            move(BAS);
        else if(etat==GAUCHE)
            move(DROITE);
        else if(etat==DROITE)
            move(GAUCHE);

        touched = false;
    }
    if(coque<=0)
    {
        alive = false;
    }

    batterie->update();
}

void Vaisseau::collided(int perte)
{
    coque -= perte;
    touched = true;
}

int Vaisseau::collisionPoints()
{
    return 20;
}


