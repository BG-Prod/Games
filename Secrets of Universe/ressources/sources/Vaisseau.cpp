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


Vaisseau::Vaisseau(int x, int y) : Vaisseau(STARSHIP1,x,y)
{
    joueur = 1;
}

Vaisseau::Vaisseau(int _type, int x, int y) : Vaisseau(100, 100, 1000, 800, 15, random(2,16), _type,
                 1000, 100, 100, 100, random(1,999999999), 5, Coordonnees(x,y,128,128,x,y,128,128),
                 TOP, NULL, "", NULL)
{
    batterie = new Weapon(this);
    if(batterie != NULL)
    {
        sons.push_back(batterie);
    }
}

Vaisseau::Vaisseau(int _energie, int _bouclier, int _coque, int _capteur, int _vitesse, int _joueur, int _type,
                 int _masse, int _teleporteur, int _hypernavigateur, int _moteur, int _id, int _pib, Coordonnees _position,
                 states _etat, Weapon * _arme, string _displayDetails, Object * _ancestor) : Object()
{
    energie = _energie;
    bouclier =  _bouclier;
    coque =  _coque;
    capteur =  _capteur;
    vitesse =  _vitesse;
    joueur =  _joueur;
    type[0] = _type;
    masse = _masse;
    teleporteur =  _teleporteur;
    hypernavigateur =  _hypernavigateur;
    moteur =  _moteur;
    id =  _id;
    position = _position;
    etat[0] = _etat;
    ancestor = _ancestor;
    alive = true;
    activiteBouclier = false;
    touched = false;
    pib = _pib;
    displayDetails = _displayDetails;
    /// armes
    batterie = _arme;
    if(batterie != NULL)
    {
        sons.push_back(batterie);
    }
    weaponTarget = 0;
}

Vaisseau::~Vaisseau()
{
    delete batterie;
}

void Vaisseau::move()
{
    /**
    *** On déplace proportionnellement à la distance à parcourir le vaisseau sur les deux axes.
    *** Ensuite on signale si on a bougé
    **/
    Coordonnees pos = Coordonnees(position.x()+position.w()/2, position.y()+position.h()/2, position.w(), position.h());
    int vecX = cible.x()-pos.x();
    int vecY = cible.y()-pos.y();
    int base = abs(vecX)+abs(vecY);
    if(base > vitesse) {
        int movX = vitesse*vecX/base;
        int movY = vitesse*vecY/base;
        position.x(position.x()+movX);
        position.y(position.y()+movY);
        etat[0] = (abs(movX)>abs(movY)) ? (movX>0 ? RIGHT : LEFT) : (movY>0 ? BOTTOM : TOP);
        hasMoved = true;
    }
    else
    {
        hasMoved = false;
    }
}

void Vaisseau::shoot()
{
    if(weaponTarget<radar.size())
    {
        batterie->use(radar[weaponTarget]);
    }
    else
    {
        batterie->use(cible);
    }
}

void Vaisseau::update(Input * in)
{
    /// màj des éléments
    move();
    batterie->update();
    /// vérification de la viabilité du vaisseau
    if(coque<=0)
    {
        alive = false;
    }
    if(activiteBouclier)
    {
        energie = energie<0 ? 0 : energie-2;
    }
}

void Vaisseau::destroy()
{
    alive = false;
}

DisplayDatas Vaisseau::transitoryEvents()
{
    DisplayDatas dt = DisplayDatas(-1,-1,Coordonnees(0,0,0,0));
    if(!alive)
    {
        dt = DisplayDatas(EXPLOSION0,1,position,"animation");
    }
    else if(activiteBouclier)
    {
        dt = DisplayDatas(SHIELD1,1,position);
    }

    return dt;
}

void Vaisseau::bot()
{
    if(joueur != 1)
    {
        /// vérification de la viabilité du vaisseau
        if(coque<=0)
        {
            alive = false;
        }
        /// choix aléatoire de la cible
        if(!hasMoved)
        {
            /// attention utilisation absolue de la taille de la map
            cible = Coordonnees(random(0,4095),random(0,4095),0,0);
        }
        /// màj des éléments
        move();
        batterie->update();
    }
}

void Vaisseau::collided(int perte)
{
    coque += (activiteBouclier)? (bouclier-perte>0 ? 0 : bouclier-perte) : -perte;
    touched = true;
}

int Vaisseau::collisionPoints()
{
    return 20;
}

void Vaisseau::switchShield()
{
    activiteBouclier = !activiteBouclier;
}

void Vaisseau::clearRadar()
{
    radar.clear();
}

void Vaisseau::addEchoRadar(Coordonnees c)
{
    radar.push_back(c);
}

int Vaisseau::getCapteur()
{
    return capteur;
}

