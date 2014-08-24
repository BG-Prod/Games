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

#include "SoUApp.h"

using namespace std;

SoUApp::SoUApp() : Application()
{
    SDL_WM_SetCaption("Secrets of Universe", NULL);
}

SoUApp::~SoUApp()
{
    for(unsigned int i = 0 ; i < players.size() ; i++)
    {
        delete players[i];
    }
    players.clear();
}

void SoUApp::menu()
{
    if(state == GOMENU)
    {
        interfaces.push_back(new Interface(WALLPAPER0));
        addButton(new Button(BUTTON1, Coordonnees(2*screen->getWidth()/4,3*screen->getHeigth()/4,128,64), "CONTINUE"));
        addButton(new Button(BUTTON1, Coordonnees(2*screen->getWidth()/4+140,3*screen->getHeigth()/4,128,64), "NEW GAME"));
        addButton(new Button(BUTTON1, Coordonnees(2*screen->getWidth()/4+280,3*screen->getHeigth()/4,128,64), "KINECT MODE"));
        addButton(new Button(BUTTON1, Coordonnees(2*screen->getWidth()/4+420,3*screen->getHeigth()/4,128,64), "OPTIONS"));
        addButton(new Button(BUTTON1, Coordonnees(2*screen->getWidth()/4+560,3*screen->getHeigth()/4,128,64), "EXIT"));
        buttons[0]->setState(DISABLED);
        buttons[2]->setState(DISABLED);
        buttons[3]->setState(DISABLED);
        state = MENU;
    }
    if(buttons[0]->pressed(in))
    {
        state = LOADGAME;
    }
    if(buttons[1]->pressed(in))
    {
        state = NEWGAME;
    }
    if(buttons[2]->pressed(in))
    {
        state = KINECTMODE;
    }
    if(buttons[3]->pressed(in))
    {
        state = OPTIONS;
    }
    if(buttons[4]->pressed(in))
    {
        state = EXIT;
    }
    if(state != MENU)
    {
        while( buttons.size() > 0 )
        {
            pullButton(0);
        }
        delete interfaces[0];
        interfaces.erase(interfaces.begin());
    }
}

void SoUApp::init()
{
    /// on joue la musique de fond
    FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, musiques[0], 0, NULL);

    /// génération du terrain
    /// génération des étoiles
    for(int i = 0 ; i < 500 ; i++)
    {
        images[itos(7)]->setPixel(random(0,images[itos(7)]->width()), random(0,images[itos(7)]->height()), color(random(200,255),random(200,255),random(180,200)));
    }

    /// création de la carte
    objects.push_back(new Map());

    /// création des joueurs
    addHuman(new Player(1103, 0 , 0, 1, 1000, true, "Ben", new Crew(), new Vaisseau(0,0)));

    for(int i = 0 ; i < 15 ; i++)
    {
        addBot(new Player(random(0,999999), 0, 0, random(1,16), random(1000, 10000), false, "Computer " + i, new Crew(), new Vaisseau(STARSHIP2, random(0,(int)(objects[0]->getPosition()).w()) , random(0,(int)(objects[0]->getPosition()).h()))));
    }

    /// ajout des vaisseaux
    for(unsigned int i = 0 ; i < players.size() ; i++)
    {
        objects.push_back( players[i]->getStarship() );
    }

    /// détermination de la cible du joueur
    objects[1]->setCible(Coordonnees(0,0,1,1));

    /// mise en place de l'interface utilisateur
    interfaces.push_back(new Interface(BOARD1));
    addButton(new Button(BUTTON1, Coordonnees(1500,10,128,64), "INFO"));
    addButton(new Button(BUTTON1, Coordonnees(1630,10,128,64), "MENU"));
    addButton(new Button(BUTTON1, Coordonnees(1760,10,128,64), "EXIT"));
    addButton(new Button(BUTTON3, Coordonnees(1016,10,128+96,64), you->getName()));
    addButton(new Button(BUTTON4, Coordonnees(1176,10,128+96,64), "Level X"));
    addButton(new Button(BUTTON5, Coordonnees(1336,10,128+96,64), "000,000,000"));
    addButton(new Button(BUTTON2, Coordonnees(0,0,128+96,64), ((Today.tm_hour<10)?"0"+itos(Today.tm_hour):itos(Today.tm_hour))+":"
                         +((Today.tm_min<10)?"0"+itos(Today.tm_min):itos(Today.tm_min))+":"
                         +((Today.tm_sec<10)?"0"+itos(Today.tm_sec):itos(Today.tm_sec))));
}

void SoUApp::app()
{
    /// gestion des events
    eventsManager();

    /// recentrage de la caméra
    cam->keepIn(objects[0]);

    /// sont-ils morts ?
    for(unsigned int i = 0 ; i < objects.size() ; i++)
    {
        if(!objects[i]->isAlive())
        {
            if(objects[i]==you->getStarship())
            {
                delete objects[i];
                objects[i] = NULL;
                you->setStarship(NULL);
            }
            else
            {
                delete objects[i];
                objects[i] = NULL;
            }
            objects.erase(objects.begin()+i);
        }
    }
    /// objets sur les bords ?
        /// se détermine par le fait qu'ils se déplacent dans l'intervalle [0 ; 4095]

    /// collision objets ?
    for(unsigned int i = 1 ; i < objects.size() ; i++)
    {
        for(unsigned int j = i+1 ; j < objects.size() ; j++)
        {
            objects[i]->collision(objects[j]);
        }
    }

    /// màj des capteurs
    radarManager();

    /// màj des objets
    for(unsigned int i = 1 ; i < objects.size() ; i++)
    {
        objects[i]->bot();
    }

    /// màj des interfaces
    for(unsigned int i = 0 ; i < interfaces.size() ; i++)
    {
        interfaces[i]->update(in);
    }

    /// màj du joueur
    if(you->getStarship()!=NULL)
    {
        you->getStarship()->update(in);
    }

    /// màj visuel cagnotte joueur
    buttons[5]->setName(itos(you->getCoins()));
    buttons[4]->setName(itos(you->getLevel()));
    buttons[6]->setName(((Today.tm_hour<10)?"0"+itos(Today.tm_hour):itos(Today.tm_hour))+":"
                         +((Today.tm_min<10)?"0"+itos(Today.tm_min):itos(Today.tm_min))+":"
                         +((Today.tm_sec<10)?"0"+itos(Today.tm_sec):itos(Today.tm_sec)));
}

void SoUApp::intro()    /// affichage du logo
{
    int clign = 0;

    while(clign<256)
    {
        SDL_FillRect(SDL_GetVideoSurface(), 0, SDL_MapRGBA(SDL_GetVideoSurface()->format, 0, 0, 0, 0));
        images[itos(0)]->setAlpha(clign);
        images[itos(0)]->print(SDL_GetVideoSurface()->w/2 - images[itos(0)]->width()/2,SDL_GetVideoSurface()->h/2 - images[itos(0)]->height()/2);
        clign+=5;
        fps();
        SDL_Flip(SDL_GetVideoSurface());
    }

    while(clign<512)
    {
        SDL_FillRect(SDL_GetVideoSurface(), 0, SDL_MapRGBA(SDL_GetVideoSurface()->format, 0, 0, 0, 0));
        images[itos(1)]->setAlpha(clign);
        images[itos(1)]->print(SDL_GetVideoSurface()->w/2 - images[itos(1)]->width()/2,SDL_GetVideoSurface()->h/2 - images[itos(1)]->height()/2);
        clign+=10;
        fps();
        SDL_Flip(SDL_GetVideoSurface());
    }
}

void SoUApp::eventsManager()    /// gère les évènements
{
    /// resize taille écran
    if(in->get_touche(SDLK_F1))
    {
        screen->resize();
    }
    /// bouger la caméra
    if(in->get_touche(SDLK_UP))
    {
        cam->cameraUp();
    }
    if(in->get_touche(SDLK_DOWN))
    {
        cam->cameraDown();
    }
    if(in->get_touche(SDLK_LEFT))
    {
        cam->cameraLeft();
    }
    if(in->get_touche(SDLK_RIGHT))
    {
        cam->cameraRight();
    }
    /// bouton exit
    if(buttons[2]->pressed(in))
    {
        in->set_exit(true);
    }

    /// pour tirer
    if(in->get_touche(SDLK_SPACE) && you->getStarship() != NULL)
    {
        (you->getStarship())->shoot();
    }
    /// pour bouclier
    if(in->get_touche(SDLK_RETURN) && you->getStarship() != NULL)
    {
        (you->getStarship())->switchShield();
        in->set_touche(SDLK_RETURN, 0);
    }
    /// sur clic on désigne une nouvelle cible
    if(in->get_souris_boutons(SDL_BUTTON_RIGHT) && you->getStarship() != NULL)
    {
        you->getStarship()->setCible(Coordonnees(in->mouse(X)+cam->view().x(), in->mouse(Y)+cam->view().y(), 5, 5));
        in->set_souris_boutons(SDL_BUTTON_RIGHT,0);
    }
}

int SoUApp::whatImage(int a, int b) /// couple les données pour obtenir un rendu
{
    int retour = -1;
    if(a==SPACE_MAP_1)
    {
        retour = 7;
    }
    if(a==STARSHIP1)
    {
        if(b==BOTTOM)
        {
            retour = 2;
        }
        else if(b==TOP)
        {
            retour = 3;
        }
        else if(b==RIGHT)
        {
            retour = 4;
        }
        else if(b==LEFT)
        {
            retour = 5;
        }
    }
    if(a==STARSHIP2)
    {
        if(b==BOTTOM)
        {
            retour = 11;
        }
        else if(b==TOP)
        {
            retour = 12;
        }
        else if(b==RIGHT)
        {
            retour = 13;
        }
        else if(b==LEFT)
        {
            retour = 14;
        }
    }
    if(a==BOARD1)
    {
        retour = 8;
    }
    if(a==WALLPAPER0)
    {
        retour = 1;
    }
    if(a==SHOT1)
    {
        retour = 21;
    }
    if(a==SHOT2)
    {
        retour = 6;
    }
    if(a==SHIELD1)
    {
        retour = 25;
    }
    if(a==BUTTON1)
    {
        if(b==ON)
        {
            retour = 10;
        }
        else if(b==OFF)
        {
            retour = 9;
        }
        else if(b==DISABLED)
        {
            retour = 18;
        }
    }
    if(a==BUTTON3)
    {
        retour = 17;
    }
    if(a==BUTTON4)
    {
        retour = 15;
    }
    if(a==BUTTON5)
    {
        retour = 16;
    }
    if(a==TEXT1)
    {
        retour = -26;
    }
    if(a==POPUP)
    {
        retour = 20;
    }
    if(a==EXPLOSION0)
    {
        retour = 22;
    }

    return retour;
}

void SoUApp::addHuman(Player * p)
{
    players.push_back(p);
    you = p;
}

void SoUApp::addBot(Player * p)
{
    players.push_back(p);
}

void SoUApp::pullPlayer(int pid)
{
    for(unsigned int i = 0 ; i < players.size() ; i++)
    {
        if(players[i]->getId() == pid)
        {
            delete players[i];
            players.erase(players.begin()+i);
        }
    }
    if(you->getId()==pid)
    {
        you = NULL;
    }
}

void SoUApp::radarManager()
{
    for(unsigned int i = 0 ; i < players.size() ; i++)
    {
        if(players[i]->getStarship()!=NULL)
        {
            players[i]->getStarship()->clearRadar();
            for(unsigned int j = 0 ; j < players.size() ; j++)
            {
                if(i != j && players[j]->getStarship()!=NULL)
                {
                    if(norme(players[i]->getStarship()->getPosition(),players[j]->getStarship()->getPosition())<=players[i]->getStarship()->getCapteur())
                    {
                        players[i]->getStarship()->addEchoRadar(players[j]->getStarship()->getPosition());
                    }
                }
            }
        }
    }
}

