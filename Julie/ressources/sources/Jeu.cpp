/*
    Julie
    Copyright (C) 2013  BG Prod

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

#include "jeu.h"

using namespace std;


Jeu::Jeu(SDL_Surface ** p_images)
{
    m_in = new Input;
    m_tempsPrecedent = 0, m_tempsActuel = 0, m_screen_refresh = SCREEN_REFRESH;
    note = 0;
    question = new Texte();
    reponse = new Texte();
    m_images = p_images;

    for(int i = 0 ; i < 40 ; i++)
    {
        data[i] = 0;
    }
    for(int i = 0 ; i < 100 ; i++)
    {
        data2[i] = "";
    }
}

Jeu::~Jeu()
{
    delete m_in;
    delete question;
    delete reponse;
}

void Jeu::game()    /// boucle principale du jeu
{
    srand(SDL_GetTicks());
    m_in->activerSaisie();

    for(int i = 0 ; i < 40 ; i++)
    {
        data[i] = rand()%(101-0) + 0;
    }

    while(!m_in->get_touche(SDLK_ESCAPE) && !m_in->get_exit())
    {
        /// met à jour les evenements d'entree
        m_in->update();
        /// régule le fps
        timer();
        /// resize taille écran
        resizeScreen();

        /// mécanique du jeu
        mecanique();
        /// affichage du jeu
        affichage();
    }
}


void Jeu::conjugaison()    /// boucle principale du jeu
{
    srand(SDL_GetTicks());
    m_in->activerSaisie();

    BDD * dico = new BDD("ressources/datas/database.db");

    for(int i = 0 ; i < 20 ; i++)
    {
        std::vector<std::vector<std::string> > dataC;
        int hazard = rand()%(10-1) + 1;
        string temp = "SELECT nom,pluralite,personne FROM pronom WHERE id = " + toString(hazard);
        dataC = dico->request((char*)temp.c_str());
        data2[i*5+0] = dataC[0][0];
        data2[i*5+2] = dataC[0][1];
        data2[i*5+3] = dataC[0][2];
        hazard = rand()%(4-1) + 1;
        temp = "SELECT infinitif FROM verbe WHERE id = " + toString(hazard);
        dataC = dico->request((char*)temp.c_str());
        data2[i*5+4] = dataC[0][0];
        temp = "SELECT " + data2[i*5+3] + "_" + data2[i*5+2] + " FROM indicatif_present WHERE id = " + toString(hazard);
        dataC = dico->request((char*)temp.c_str());
        data2[i*5+1] = dataC[0][0];

        cout << data2[i*5+0] << " " << data2[i*5+1] << " " << data2[i*5+2] << " " << data2[i*5+3] << " " << data2[i*5+4] << endl;
    }

    delete dico;

    while(!m_in->get_touche(SDLK_ESCAPE) && !m_in->get_exit())
    {
        /// met à jour les evenements d'entree
        m_in->update();
        /// régule le fps
        timer();
        /// resize taille écran
        resizeScreen();

        /// mécanique du jeu
        mecanique2();
        /// affichage du jeu
        affichage2();
    }
}

void Jeu::mecanique()
{
    if(note < 20)
    {
        if(!(m_in->modeSaisie()))
        {
            if(toInt((char*)m_in->str().c_str()) == data[note*2]+data[note*2+1])
            {
                note++;
            }
            m_in->activerSaisie();
        }
    }
    else
    {
        m_in->set_exit(1);
    }
}

void Jeu::mecanique2()
{
    if(note < 20)
    {
        if(!(m_in->modeSaisie()))
        {
            if(m_in->str() == data2[note*5] + " " + data2[note*5+1])
            {
                note++;
            }
            else if(data2[note*5+3]=="troisieme")
            {
                if(data2[note*5+2]=="singulier")
                {
                    if(m_in->str() == "il " + data2[note*5+1] ||
                       m_in->str() == "elle " + data2[note*5+1] ||
                       m_in->str() == "on " + data2[note*5+1])
                       {
                           note++;
                       }
                }
                else if(data2[note*5+2]=="pluriel")
                {
                    if(m_in->str() == "ils " + data2[note*5+1] ||
                       m_in->str() == "elles " + data2[note*5+1])
                    {
                       note ++;
                    }
                }
            }
            else if(data2[note*5]=="je" && data2[note*5+1]=="ai")
            {
                if(m_in->str() == "j'ai")
                {
                   note ++;
                }
            }
            m_in->activerSaisie();
        }
    }
    else
    {
        m_in->set_exit(1);
    }
}

void Jeu::affichage()
{
    SDL_Rect place = {0,0,0,0};
    SDL_Color couleur = {255,255,255};
    string texte = "Error";
    SDL_FillRect(SDL_GetVideoSurface(), 0, SDL_MapRGB(SDL_GetVideoSurface()->format, 240, 0, 50));
    SDL_BlitSurface(m_images[5],NULL,SDL_GetVideoSurface(),&place);

    texte = toString(data[note*2]) + " + " + toString(data[note*2+1]) + " = ?";
    question->print(texte, "arial", 60, couleur, 400*RESIZE, 400*RESIZE);

    reponse->print(m_in->str(), "arial", 60, couleur, 400*RESIZE, 540*RESIZE);
    SDL_Flip(SDL_GetVideoSurface());
}

void Jeu::affichage2()
{
    SDL_Rect place = {0,0,0,0};
    SDL_Color couleur = {255,255,255};
    string texte = "Error";
    SDL_FillRect(SDL_GetVideoSurface(), 0, SDL_MapRGB(SDL_GetVideoSurface()->format, 240, 0, 50));
    SDL_BlitSurface(m_images[4],NULL,SDL_GetVideoSurface(),&place);

    texte = "Conjuge le verbe " + data2[note*5+4];
    question->print(texte, "arial", 40, couleur, 1050*RESIZE, 150*RESIZE);

    texte = "à la " + data2[note*5+3] + " personne du " + data2[note*5+2] + " :";
    question->print(texte, "arial", 40, couleur, 1050*RESIZE, 200*RESIZE);

    reponse->print(m_in->str(), "arial", 60, couleur, 1050*RESIZE, 540*RESIZE);
    SDL_Flip(SDL_GetVideoSurface());
}

void Jeu::explosion(SDL_Surface ** p_images, Animation * animation)
{
    if(animation->temps != -1)
    {
        if(!animation->temps)
        {
            animation->place.x = (animation->place.x * p_images[5]->w) + p_images[5]->w/2 - p_images[12]->w/8;
            animation->place.y = (p_images[5]->h * animation->place.y) + p_images[5]->h/2 - p_images[12]->h/10;
        }
        if(animation->temps < 20)
        {
            /// faire les calculs de l'image
            SDL_Rect place;
            place.x = (animation->temps%4) * p_images[12]->w/4;
            place.y = (animation->temps/4) * p_images[12]->h/5;
            place.w = p_images[12]->w / 4;
            place.h = p_images[12]->h / 5;
            SDL_BlitSurface(p_images[12], &place, SDL_GetVideoSurface(), &(animation->place));
            animation->temps = animation->temps + 1;
        }
        else
        {
            animation->temps = -1;
        }
    }
}

void Jeu::timer()
{
    fps(&m_tempsPrecedent, &m_tempsActuel, m_screen_refresh);
}

void Jeu::resizeScreen()
{
    resize_screen(*m_in);
}


