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


Vaisseau::Vaisseau() : Object(), energie(100), bouclier(100), coque(1000), capteur(100), teleporteur(100), hypernavigateur(100), moteur(100), coins(1000), pib(5)
{
    etat[0] = LEFT;
    vitesse = 15;
    type[0] = STARSHIP1;
    alive = true;
    activiteBouclier = false;
    outOf = -1;
    touched = false;

    /// position du centre du vaisseau
    position = Coordonnees(500,500,128,128,500,500,128,128);

    /// armes
    batterie = new Weapon(this);
    sons.push_back(batterie);
}

Vaisseau::Vaisseau(int x, int y) : Vaisseau(STARSHIP1,x,y)
{

}

Vaisseau::Vaisseau(int _type, int x, int y) : Object(), energie(100), bouclier(100), coque(100), capteur(100), teleporteur(100), hypernavigateur(100), moteur(100), coins(1000), pib(5)
{
    etat[0] = LEFT;
    vitesse = 15;
    type[0] = _type;
    alive = true;
    activiteBouclier = false;
    outOf = -1;
    touched = false;

    /// position du centre du vaisseau
    position = Coordonnees(x,y,128,128,x,y,128,128);

    /// armes
    batterie = new Weapon(this);
    sons.push_back(batterie);
}

Vaisseau::Vaisseau(int _energie, int _bouclier, int _coque, int _capteur, int _vitesse, int _joueur, int _type,
                 int _masse, int _teleporteur, int _hypernavigateur, int _moteur, int _id, Coordonnees _position,
                 states _etat, Object * _ancestor)
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
    outOf = -1;
    touched = false;
    sons.push_back(batterie);
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
    int vecX = cible.x()-position.x();
    int vecY = cible.y()-position.y();
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
    batterie->use();
}

void Vaisseau::update(Input * in)
{
    /// màj des éléments
    move();
    batterie->update();
    addCoins(pib);
}

void Vaisseau::destroy()
{

}

void Vaisseau::bot()
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

void Vaisseau::collided(int perte)
{
    coque -= perte;
    touched = true;
}

int Vaisseau::collisionPoints()
{
    return 20;
}

void Vaisseau::setCoins(int v)
{
    coins = v;
}

void Vaisseau::addCoins(int v)
{
    coins += v;
}

int Vaisseau::getCoins()
{
    return coins;
}

