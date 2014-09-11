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

#include "Application.h"

using namespace std;

Application::Application()
{
    /// initialisation son & image
    /// initialisation FMOD
    FMOD_System_Create(&system);

    /// verification de la date
	time(&maintenant);
	Today = *localtime(&maintenant);
    /// initialisation de l'aléatoire
    srand(time(NULL));

    NOMBRE_IMAGE = 22;
    NOMBRE_ANIM = 1;
    NOMBRE_MUSIQUE = 1;
    NOMBRE_POLICE = 0;

	/// create new screen
	screen = new Screen;
	cam = new Camera;

	/// username
    DWORD StrLen = 256;
    TCHAR SysInfoStr[256];
    GetComputerName(SysInfoStr, &StrLen);
    nameComputeur = SysInfoStr;
    GetUserName(SysInfoStr, &StrLen);
    nameUser = SysInfoStr;

    /// Control
    in = new Input();

    /// initialisation image & son
    initialisation();

    /// gestionnaire d'animations
    animationManager = new AnimationManager(screen->buffer());

    /// set window attributes
    this->windowAttributes();

    /// time
    tempsActuel = 0, tempsPrecedent = 0, screen_refresh = SCREEN_REFRESH;

    /// application states
    state = MENU;
}

Application::~Application()
{
    /// free loaded bitmap and created surface
    delete screen;
    delete cam;
    delete in;
    delete animationManager;
    fermeture();
}

void Application::windowAttributes()
{
    /// Icone
    //images["0"]->setAsIcon();
    /// titre
    SDL_WM_SetCaption("Application", NULL);
}

void Application::initialisation()
{
    /// initialise SDL video
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
    }

    /// initialise SDL TTF
    TTF_Init();

    /// make sure SDL cleans up before exit
    atexit(SDL_Quit);
    atexit(TTF_Quit);

    /// initialisation de FMOD
    FMOD_System_Init(system, 32, FMOD_INIT_NORMAL, NULL);

    /// initialisation et chargement des ressources
    loadRessources(); /// juste images pour l'instant
    /// sons
    loadMusics();
    /// polices
    loadFonts();
}

void Application::fermeture()
{
    /// libération des données
    freeImages();
    freeFonts();
    freeMusics();
    freeObjects();

    /// fermeture propre de fmodex
    FMOD_System_Close(system);
    FMOD_System_Release(system);
}

void Application::loadRessources()  /// new school with sqlite
{
    /// on commence par ouvrir labase de données
    string link = cheminData + "ressources.db";
    BDD * baseDeDonnees = new BDD((char*)link.c_str());

    /// on recherche les informations
    vector< vector< string > > result = baseDeDonnees->request("select link, details from image");

    NOMBRE_IMAGE = result.size();

    for(unsigned int i = 0 ; i < result.size() ; i++)
    {
        if(result[i][1]=="animation")
        {
            //images.push_back(new Animation(result[i][0]));
            images[itos(i)] = new Animation(result[i][0]);
        }
        else
        {
       //     images.push_back(new Image(result[i][0]));
            images[itos(i)] = new Image(result[i][0]);
        }
        images[itos(i)]->resize((double)(100.0*(SDL_GetVideoSurface()->h)/1080.0));
    }

    /// on finit en fermant la base de données
    delete baseDeDonnees;
}

void Application::loadImages()  /// old school
{/**
    string lien;
    char a[2];
    for(unsigned int i = 0 ; i < NOMBRE_IMAGE ; i++)
    {
        itoa(i,a,10);
        if(i < 10)
        {
            lien = cheminImage + "image0" + a + ".png";
        }
        else
        {
            lien = cheminImage + "image" + a + ".png";
        }

        images.push_back(new Image(lien));
        images[i]->resize((double)(100.0*(SDL_GetVideoSurface()->h)/1080.0));
    }
    for(unsigned int i = 0 ; i < NOMBRE_ANIM ; i++)
    {
        itoa(i,a,10);
        if(i < 10)
        {
            lien = cheminImage + "anim0" + a + ".png";
        }
        else
        {
            lien = cheminImage + "anim" + a + ".png";
        }

        images.push_back(new Animation(lien));
        images[i]->resize((double)(100.0*(SDL_GetVideoSurface()->h)/1080.0));
    }**/
}

void Application::loadMusics()  /// old school
{
    string lien;

    for(unsigned int i = 0 ; i < NOMBRE_MUSIQUE ; i++)
    {
        lien = cheminSon + "son01.mid";
        musiques.push_back(NULL);
        FMOD_System_CreateSound(system, lien.c_str(), FMOD_SOFTWARE | FMOD_2D | FMOD_LOOP_NORMAL | FMOD_CREATESTREAM, 0, &musiques[i]);
        FMOD_Sound_SetLoopCount(musiques[i], -1);
    }
}

void Application::loadFonts()   /// old school
{
    string lien;

    for(unsigned int i = 0 ; i < NOMBRE_POLICE ; i++)
    {
        lien = cheminPolice + "calibri.ttf";
        polices.push_back(TTF_OpenFont(lien.c_str(), 20));
    }
}


void Application::freeImages()
{
    for(unsigned int i = 0 ; i < images.size() ; i++)
    {
        delete images[itos(i)];
    }
    images.clear();
}

void Application::freeObjects()
{
    for(unsigned int i = 0 ; i < objects.size() ; i++)
    {
        delete objects[i];
    }
    objects.clear();
    for(unsigned int i = 0 ; i < interfaces.size() ; i++)
    {
        delete interfaces[i];
    }
    interfaces.clear();
}

void Application::freeMusics()
{
    for(unsigned int i = 0 ; i < musiques.size() ; i++)
    {
        FMOD_Sound_Release(musiques[i]);
    }
    musiques.clear();
}

void Application::freeFonts()
{
    for(int i = 0 ; i < polices.size() ; i++)
    {
        TTF_CloseFont(polices[i]);
    }
    polices.clear();
}

/// Pour copier une SDL_Surface
SDL_Surface* Application::copieSurface(SDL_Surface *src)
{
    if(src != NULL)
    {
        return SDL_ConvertSurface(src, src->format, SDL_SWSURFACE);
    }
    else
    {
        return NULL;
    }
}

void Application::fps()
{
    tempsActuel = SDL_GetTicks();

    if(tempsActuel - tempsPrecedent >= screen_refresh)
    {
        tempsPrecedent = tempsActuel;
    }
    else if (tempsActuel - tempsPrecedent < screen_refresh)
    {
        SDL_Delay(tempsActuel - tempsPrecedent);
        tempsPrecedent = tempsActuel;
    }
	time(&maintenant);
	Today = *localtime(&maintenant);
}

void Application::init()
{

}

void Application::run()
{
    this->intro();
    while(!in->get_touche(SDLK_ESCAPE) && !in->get_exit() && state != EXIT)
    {
        state = GOMENU;
        while(!in->get_touche(SDLK_ESCAPE) && !in->get_exit() && (state == MENU || state == GOMENU))
        {
            this->fps();
            in->update();
            this->menu();
            this->draw();
        }

        /// permet de rentrer dans le bloc principal
        if(state!=EXIT)
        {
            init();
            state = MAIN;
        }

        /** TEST TIMING **/// int compteurDeTour = 0;
        /** TEST TIMING **/// int timeMemory = SDL_GetTicks();
        while(!in->get_touche(SDLK_ESCAPE) && !in->get_exit() && state == MAIN)
        {
            this->fps();
            in->update();
            this->app();
            this->draw();

        /** TEST TIMING **///     if(SDL_GetTicks()-timeMemory>=1000){cout << "Nombre d'exécution en 1 seconde : " << compteurDeTour+1 << endl; compteurDeTour=0; timeMemory = SDL_GetTicks();}
        /** TEST TIMING **///     else{compteurDeTour++;}
        }
    }
}

void Application::app()
{

}

void Application::menu()
{
    state = MAIN;
}

void Application::intro()
{

}

void Application::draw()
{
    /// on met a jour les animations
    animationManager->update();

    /// on traite les images et enregistre les nouvelles animations
    for(unsigned int i = 0 ; i < objects.size() ; i++)
    {
        vector<DisplayDatas> tmps = objects[i]->print();
        for(unsigned int j = 0 ; j < tmps.size() ; j++)
        {
            DisplayDatas tmp = tmps[j];

            int numImage = whatImage(tmp.type, tmp.etat);

            if(numImage >= 0)
            {
                if(tmp.detail == "animation")
                {
                    Coordonnees relativePlace(tmp.coor);
                    relativePlace.x(relativePlace.x()-cam->view().x());
                    relativePlace.y(relativePlace.y()-cam->view().y());
                    tmp.coor = relativePlace;
                    animationManager->pushAnim(tmp,(Animation*)images[itos(numImage)]);
                }
                else
                {
                    Coordonnees relativePlace(tmp.coor);
                    relativePlace.x(relativePlace.x()-cam->view().x());
                    relativePlace.y(relativePlace.y()-cam->view().y());
                    images[itos(numImage)]->print(screen->getBuffer(), (i==0)?cam->place():relativePlace, (i==0)?cam->view():cam->place());
                }
            }
        }
    }

    /// on joue les animations
    animationManager->displayAnimations();

    /// de même pour les interfaces
    for(unsigned int i = 0 ; i < interfaces.size() ; i++)
    {
        vector<DisplayDatas> tmps = interfaces[i]->print();
        for(unsigned int j = 0 ; j < tmps.size() ; j++)
        {
            DisplayDatas tmp = tmps[j];

            int numImage = whatImage(tmp.type, tmp.etat);

            if(numImage >= 0)
            {
                Coordonnees relativePlace(tmp.coor);
                images[itos(numImage)]->print(screen->getBuffer(), relativePlace);
            }
            else if(numImage == -26)
            {
                Texte * txt = new Texte();
                SDL_Color couleur = {255,255,255};
                vector<Image*> textToPrint = txt->print(tmp.detail,"calibri",20,couleur,tmp.coor.x(),tmp.coor.y());
                for(unsigned int k = 0 ; k < textToPrint.size() ; k++)
                {
                    Coordonnees placeToBlitt(tmp.coor.x()+tmp.coor.w()/2-textToPrint[k]->width()/2,tmp.coor.y()+tmp.coor.h()/2-textToPrint[k]->height()/2, textToPrint[k]->width(), textToPrint[k]->height());
                    textToPrint[k]->print(screen->getBuffer(), placeToBlitt);
                }
                delete txt;
                for(unsigned int incr = 0 ; incr < textToPrint.size() ; incr++)
                {
                    delete textToPrint[incr];
                }
            }
            else if(numImage == -11)
            {
                Image * constructedPicture = new Image(tmp.coor.w(), tmp.coor.h(), 100, 100, 100);
            }
        }
    }

    screen->display();
}

void Application::addButton(Button * b)
{
    interfaces.push_back(b);
    buttons.push_back(b);
}

void Application::pullButton(int index)
{
    for(unsigned int i = 0 ; i < interfaces.size() ; i++)
    {
        if(interfaces[i]==buttons[index])
        {
            interfaces.erase(interfaces.begin()+i);
        }
    }
    delete buttons[index];
    buttons.erase(buttons.begin()+index);
}

int Application::whatImage(int a, int b)
{

}

string Application::itos(long number)
{
    ostringstream retour;
    if(number==0)
    {
        return "0";
    }
    else
    {
        retour << number;
        return string(retour.str());
    }
}

long Application::getTime()
{
    return SDL_GetTicks();
}

DIR * Application::openDirectory(string url)
{
    DIR* retour = NULL;
    retour = opendir(url.c_str());
    if(retour == NULL)
    {
        perror("");
    }
    return retour;
}

void Application::closeDirectory(DIR * directory)
{
    if(closedir(directory) == -1)
    {
        perror("");
    }
}

vector<string> Application::scanDirectory(string url)
{
    DIR * repertoire = openDirectory(url);
    dirent * fichier = NULL;
    vector<string> retour;
    while ((fichier = readdir(repertoire)) != NULL)
    {
        retour.push_back(fichier->d_name);
    }
    closeDirectory(repertoire);
    return retour;
}

double Application::norme(Coordonnees a, Coordonnees b)
{
    double aX = a.x() + a.w()/2,
           bX = b.x() + b.w()/2,
           aY = a.y() + a.h()/2,
           bY = b.y() + b.h()/2;

    return sqrt(pow(aX-bX,2)+pow(aY-bY,2));
}
