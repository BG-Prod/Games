/*
    The Arvernes - The Card Game
    Copyright (C) 2013  Garçon Benoît

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

    Contact me : benoit.garconbesson@gmail.com
*/


#include <SDL.h>
#include <cstdlib>
#include <stdlib.h>
#include <stdio.h>
#include <FMOD/fmod.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <math.h>
#include <string>
#include <fstream>
#include <iostream>
#include <windows.h>
#include <sstream>
#include <WinSock.h>
#include <cassert>
#include <exception>

#include "bouton.h"
#include "utile.h"
#include "jeu.h"
#include "affichage.h"



int main ( int argc, char** argv )
{
    // initialize SDL video
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
        return 1;
    }

    TTF_Init();

    // make sure SDL cleans up before exit
    atexit(SDL_Quit);
    atexit(TTF_Quit);

    // pour le son
    FMOD_SYSTEM *system;
    FMOD_System_Create(&system);
    FMOD_System_Init(system, 32, FMOD_INIT_NORMAL, NULL);


    // déclaration des ressources
    std::string lien;
    SDL_Surface** imageinterface = NULL;
    imageinterface = (SDL_Surface **) malloc (sizeof(SDL_Surface*)*NB_IMAGE_INTERFACE);
    for(int i = 0 ; i < NB_IMAGE_INTERFACE ; i++)
    {
        imageinterface[i] = NULL;
    }

    SDL_Surface** imageMenu = NULL;
    imageMenu = (SDL_Surface **) malloc (sizeof(SDL_Surface*)*NB_IMAGE_MENU);
    for(int i = 0 ; i < NB_IMAGE_MENU ; i++)
    {
        imageMenu[i] = NULL;
    }

    SDL_Surface ** imageEditeur = NULL;
    imageEditeur = (SDL_Surface **) malloc (sizeof(SDL_Surface*)*NB_IMAGE_EDITEUR);
    for(int i = 0 ; i < NB_IMAGE_EDITEUR ; i++)
    {
        imageEditeur[i] = NULL;
    }


    FMOD_SOUND * monTabZic[NOMBRE_MUSIQUE];
    for(int i = 0 ; i < NOMBRE_MUSIQUE ; i++)
    {
        monTabZic[i] = NULL;
    }
    lien = cheminSon + "punch.mp3";
    FMOD_System_CreateSound(system, lien.c_str(), FMOD_CREATESAMPLE, 0, &monTabZic[0]);
    lien = cheminSon + "tonnerre.mp3";
    FMOD_System_CreateSound(system, lien.c_str(), FMOD_CREATESAMPLE, 0, &monTabZic[1]);
    lien = cheminSon + "er.mp3";
    FMOD_System_CreateSound(system, lien.c_str(), FMOD_CREATESAMPLE, 0, &monTabZic[2]);
    lien = cheminSon + "The Arvernes.mp3";
    FMOD_System_CreateSound(system, lien.c_str(), FMOD_LOOP_NORMAL | FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM, 0, &monTabZic[3]);
    FMOD_Sound_SetLoopCount(monTabZic[3], -1);
    lien = cheminSon + "merde.mp3";
    FMOD_System_CreateSound(system, lien.c_str(), FMOD_LOOP_NORMAL | FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM, 0, &monTabZic[4]);

    // Icone
    lien = cheminImage + "logo_bgprod.png";
    imageinterface[0] = IMG_Load(lien.c_str());
    lien = cheminImage + "logo_arvernes_giga.png";
    imageinterface[15] = IMG_Load(lien.c_str());
    SDL_SetColorKey(imageinterface[15], SDL_SRCCOLORKEY, SDL_MapRGB(imageinterface[15]->format, 255, 255, 255));
    SDL_WM_SetIcon(imageinterface[0], NULL);

    // create a new window
    SDL_Surface* screen = SDL_SetVideoMode(LARGEUR_ECRAN, HAUTEUR_ECRAN, 32, SDL_HWSURFACE|SDL_DOUBLEBUF);
    if ( !screen )
    {
        printf("Unable to set 640x480 video: %s\n", SDL_GetError());
        return 1;
    }


    // icon and title
    SDL_WM_SetCaption("The Arvernes : The Card Game", NULL);

    // username
    DWORD StrLen = 256;
    TCHAR SysInfoStr[256];
    GetComputerName(SysInfoStr, &StrLen);
    std::string nameComputeur = SysInfoStr;
    GetUserName(SysInfoStr, &StrLen);
    std::string nameUser = SysInfoStr;

    std::string way;
    way = cheminFile + "card.txt";
    /*int nombreCartes = 0;
    std::ifstream fichier(way.c_str(), std::ios::in);  // on ouvre le fichier en lecture
    if(fichier)  // si l'ouverture a réussi
    {
        nombreCartes = nombreLignes(way.c_str()) - 2; // on enlève la première ligne
        //std::cerr << 1 << std::endl;
    }
    fichier.close();*/


    SDL_Rect position = {0,0,0,0};
    SDL_BlitSurface(imageinterface[0], 0, screen, &position);
        SDL_Flip(screen);

    // load images and create colored surfaces
    SDL_Surface ** monTabImage = NULL;
    monTabImage = (SDL_Surface **) malloc(sizeof(SDL_Surface *)*(NOMBRE_CARTE+1));
    for(int i = 0 ; i < NOMBRE_CARTE+1 ; i++)
    {
        monTabImage[i] = NULL;
    }

    load_png(monTabImage, imageMenu, imageEditeur);

    // load text
    TTF_Font ** police = NULL;
    police = (TTF_Font **) malloc(sizeof(TTF_Font*) * NOMBRE_POLICE);
    for(int i = 0 ; i < NOMBRE_POLICE ; i++)
    {
        police[i] = NULL;
    }
    lien = cheminPolice + "Optimus.ttf";
    police[0] = TTF_OpenFont(lien.c_str(), 30);
    lien = cheminPolice + "Monkirta_Pursuit_NC.ttf";
    police[1] = TTF_OpenFont(lien.c_str(), 20);
    lien = cheminPolice + "sofachrome_rg.ttf";
    police[2] = TTF_OpenFont(lien.c_str(), 50);
    lien = cheminPolice + "Alice_in_Wonderland_3.ttf";
    police[3] = TTF_OpenFont(lien.c_str(), 20);
    lien = cheminPolice + "OptimusPrinceps.ttf";
    police[4] = TTF_OpenFont(lien.c_str(), 20);
    lien = cheminPolice + "calibri.ttf";
    police[5] = TTF_OpenFont(lien.c_str(), 20);

    SDL_Color gris = {200,200,200};
    SDL_Color blanc = {255,255,255};
    SDL_Color vert = {20,150,20};
    imageinterface[10] = TTF_RenderText_Blended(police[2], "VICTOIRE", gris);
    imageinterface[11] = TTF_RenderText_Blended(police[2], "DEFAITE", gris);
    imageinterface[8] = TTF_RenderText_Blended(police[0], "Life", vert);
    imageinterface[9] = TTF_RenderText_Blended(police[2], "VS", gris);
    imageinterface[6] = TTF_RenderText_Blended(police[5], "F1 : MODE PLEIN ECRAN", blanc);
    imageinterface[7] = TTF_RenderText_Blended(police[5], "F2 : MODE FENETRE", blanc);
    imageinterface[13] = TTF_RenderText_Blended(police[1], "PRESSEZ ENTREE POUR COMMENCER UNE NOUVELLE PARTIE", blanc);
    imageinterface[14] = TTF_RenderText_Blended(police[2], "MATCH NUL", gris);

    lien = cheminImage + "cadre_info.png";
    imageinterface[12] = SDL_DisplayFormat(IMG_Load(lien.c_str()));


    lien = cheminImage + "logo_arvernes.png";
    imageinterface[1] = SDL_DisplayFormat(IMG_Load(lien.c_str()));
    lien = cheminImage + "font_back.png";
    imageinterface[2] = SDL_DisplayFormat(IMG_Load(lien.c_str()));
    lien = cheminImage + "font_zone.png";
    imageinterface[3] = SDL_DisplayFormat(IMG_Load(lien.c_str()));
    lien = cheminImage + "font_text.png";
    imageinterface[4] = SDL_DisplayFormat(IMG_Load(lien.c_str()));
    lien = cheminImage + "font_combat.png";
    imageinterface[5] = SDL_DisplayFormat(IMG_Load(lien.c_str()));


    // program main loop
    Input in;
    memset(&in,0,sizeof(in));
    int tempsPrecedent = 0, tempsActuel = 0;

    int * score = (int *) malloc(sizeof(int));
    *score = 0;

    int *** monTabCarte = (int***) malloc(3*sizeof(int***));
    for(int i=0;i<3;i++)
    {
        monTabCarte[i] = (int**) malloc(40*sizeof(int**));
        for(int j = 0;j<40;j++)
        {
            monTabCarte[i][j] = (int*) malloc(5*sizeof(int*));
            monTabCarte[i][j][0] = 0;
            monTabCarte[i][j][1] = 0;
            monTabCarte[i][j][2] = 0;
            monTabCarte[i][j][3] = 0;
            monTabCarte[i][j][4] = 0;
        }
    }

    for(int i=0;i<40;i++)
    {
        for(int j=0;j<5;j++)
        {
            monTabCarte[0][i][j] = 0;
            monTabCarte[1][i][j] = 0;
            monTabCarte[2][i][j] = 0;
        }
    }

    int * numeroDeck = (int *) malloc(sizeof(int));
    *numeroDeck = 1;

    SDL_Delay(1000);
    int * menu = new int;
    *menu = -1;

    while(!in.key[SDLK_ESCAPE] && !in.quit && !in.key[SDLK_RETURN] && !in.mousebuttons[SDL_BUTTON_LEFT])
    {
        updateEvents(&in);
        if(in.key[SDLK_F1])
        {
            SDL_SetVideoMode(LARGEUR_ECRAN, HAUTEUR_ECRAN, 32, SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_RESIZABLE|SDL_FULLSCREEN);
        }
        if(in.key[SDLK_F2])
        {
            SDL_SetVideoMode(LARGEUR_ECRAN, HAUTEUR_ECRAN, 32, SDL_HWSURFACE|SDL_DOUBLEBUF);
        }
        position = {0,0};
        SDL_BlitSurface(imageinterface[1], 0, screen, &position);
        position.x = LARGEUR_ECRAN/2 - imageinterface[13]->w/2;
        position.y = 3*HAUTEUR_ECRAN/4 - imageinterface[13]->h/2;
        SDL_BlitSurface(imageinterface[13], 0, screen, &position);

        position = {0,0};
        SDL_BlitSurface(imageinterface[6], 0, screen, &position);
        position = {0 , imageinterface[6]->h};
        SDL_BlitSurface(imageinterface[7], 0, screen, &position);

        SDL_Flip(screen);
    }

    in.key[SDLK_RETURN] = 0;
    in.mousebuttons[SDL_BUTTON_LEFT] = 0;

    //on joue la musique de fond
    FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, monTabZic[3], 0, NULL);

    while(!in.key[SDLK_ESCAPE] && !in.quit)         // boucle principale
    {
        // mise à jour des events
        updateEvents(&in);



        // gestion du frame
        tempsActuel = SDL_GetTicks();

        if(tempsActuel - tempsPrecedent >= SCREEN_REFRESH)
        {
            tempsPrecedent = tempsActuel;
        }
        else if (tempsActuel - tempsPrecedent < SCREEN_REFRESH)
        {
            SDL_Delay(tempsActuel - tempsPrecedent);
            tempsPrecedent = tempsActuel;
        }



        // resize taille écran
        if(in.key[SDLK_F1])
        {
            SDL_SetVideoMode(LARGEUR_ECRAN, HAUTEUR_ECRAN, 32, SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_RESIZABLE|SDL_FULLSCREEN);
        }
        if(in.key[SDLK_F2])
        {
            SDL_SetVideoMode(LARGEUR_ECRAN, HAUTEUR_ECRAN, 32, SDL_HWSURFACE|SDL_DOUBLEBUF);
        }





        if(*menu == 1) // jouer
        {
            SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));
            SDL_Flip(screen);
            in.key[SDLK_RETURN] = 0;
            cardGame(monTabCarte, in, monTabImage, imageinterface, screen, police, score, VAR_MUSIC, numeroDeck);
            bool sortiedeboucle = false;
            in.mousebuttons[SDL_BUTTON_LEFT] = 0;
            while(!in.key[SDLK_ESCAPE] && !in.quit && !in.key[SDLK_RETURN] && !sortiedeboucle)
            {
                updateEvents(&in);
                int temp = 5;
                if(testCurseur2(in)>=3){temp = testCurseur2(in)+3;}else{temp = 5;}
                SDL_BlitSurface(imageMenu[temp], 0, screen, 0);
                afficherScore(imageinterface, screen, score, "SCORE", police);
                SDL_Flip(screen);
                if(in.key[SDLK_RETURN] || (temp==6 && in.mousebuttons[SDL_BUTTON_LEFT])){*menu = 1; sortiedeboucle = true;}
                if(in.key[SDLK_ESCAPE] || (temp==7 && in.mousebuttons[SDL_BUTTON_LEFT])){*menu = -1; sortiedeboucle = true;}
            }
            in.key[SDLK_RETURN] = 0;
            in.key[SDLK_ESCAPE] = 0;
            in.mousebuttons[SDL_BUTTON_LEFT] = 0;
            updateEvents(&in);
        }

        if(*menu == 2) // editeur
        {
            int deck[NOMBRE_DECK_PERSO][40] = {};

            std::string * cardsName = new std::string[NOMBRE_CARTE];

            const int dim1 = NOMBRE_CARTE+1; // taille de la dimension 1
            const int dim2 = 5; // taille de la dimension 2
            int dim_allouee = 0; // nombre d'éléments alloués avec succès sur la dimension 2
            int * * index = NULL;
            index = (int **) malloc(sizeof(int*)*dim1);
            for(int i=0; i< dim1 ; i++)
            {
                index[i] = (int*) malloc(sizeof(int)*dim2);
            }


            int * b = new int;
            *b = 0;

            initIndex(index);

            chargerDeckEditeur(deck, cardsName);

            bool sortiedeboucle = false;
            in.mousebuttons[SDL_BUTTON_LEFT] = 0;


            while(!in.key[SDLK_ESCAPE] && !in.quit && !in.key[SDLK_RETURN] && !sortiedeboucle)
            {
                updateEvents(&in);

                tempsActuel = SDL_GetTicks();

                if(tempsActuel - tempsPrecedent >= SCREEN_REFRESH)
                {
                    tempsPrecedent = tempsActuel;
                }
                else if (tempsActuel - tempsPrecedent < SCREEN_REFRESH)
                {
                    SDL_Delay(tempsActuel - tempsPrecedent);
                    tempsPrecedent = tempsActuel;
                }

                editeurDeck(deck,imageEditeur,in,screen, numeroDeck, index, police, cardsName, b);


                SDL_Rect temp = {in.mousex,in.mousey-320,320,320};
                int y = 0;
                if(temp.x >=0 && temp.x < 320 && temp.y >=0 && temp.x < 320)
                {
                    y = (temp.x / 32) + 10*(temp.y / 32);
                    if(y<=NOMBRE_CARTE){*b = y;}
                    else{*b = 0;}
                    if(in.mousebuttons[SDL_BUTTON_LEFT] == SDL_PRESSED )
                    {
                        in.mousebuttons[SDL_BUTTON_LEFT] = SDL_RELEASED;
                        int i = 0;
                        bool stop = false;
                        while(i < 40 && deck[*numeroDeck-1][i] != 0)
                            {
                                i++;
                                if(i>=40){stop = true;}
                            }
                        if(!stop)
                        {deck[*numeroDeck-1][i] = *b;}

                        in.mousebuttons[SDL_BUTTON_LEFT] = SDL_RELEASED;
                    }
                }
                else if(in.mousex < 320 && in.mousey >=160 && in.mousey < 288)
                {
                    temp = {in.mousex, in.mousey - 160};
                    y = (temp.x / 32) + 10*(temp.y / 32);
                    *b = deck[(*numeroDeck)-1][y];
                    if(in.mousebuttons[SDL_BUTTON_LEFT] == SDL_PRESSED)
                    {
                        in.mousebuttons[SDL_BUTTON_LEFT] = SDL_RELEASED;
                        deck[*numeroDeck-1][y] = 0;
                    }
                }
                else{*b = 0;}

                in.mousebuttons[SDL_BUTTON_LEFT] = SDL_RELEASED;
            }

            DEBUG "We are going in !";

            sauvegarderDeckEditeur(deck);

            DEBUG "We are out !";

            //dechargerDeckEditeur(deck);

            delete b;
            delete [] cardsName;

            DEBUG "We have deleted !";

            for(int i=0; i<dim1; ++i)
            {free(index[i]);}
            free(index);

            DEBUG "We have deleted again !";

            in.key[SDLK_RETURN] = 0;
            in.key[SDLK_ESCAPE] = 0;
            in.mousebuttons[SDL_BUTTON_LEFT] = 0;
            updateEvents(&in);
            *menu = -1;

            DEBUG "We are going to leave the editor !";
        }

        if(*menu == 3) // classement
        {
            //highscore(imageMenu,in,score,imageinterface,screen,police,&menu);
            bool sortiedeboucle = false;
            int classement = 0;
            int points[3] = {0};
            std::string pointeurs[3];

                chargerHighscores(points,pointeurs);

            in.mousebuttons[SDL_BUTTON_LEFT] = 0;
            while(!in.key[SDLK_ESCAPE] && !in.quit && !in.key[SDLK_RETURN] && !sortiedeboucle && classement<3)
            {
                updateEvents(&in);
                int temp = 5;
                if(testCurseur2(in)>=3){temp = testCurseur2(in)+3;}else{temp = 5;}
                SDL_BlitSurface(imageMenu[temp], 0, screen, 0);
                int * pointeur_sur_point = &points[classement];
                afficherScore(imageinterface,screen,pointeur_sur_point,pointeurs[classement],police);
                SDL_Flip(screen);
                if(in.key[SDLK_RETURN] || (temp==6 && in.mousebuttons[SDL_BUTTON_LEFT]))
                {
                    classement++;
                    in.mousebuttons[SDL_BUTTON_LEFT] = 0;
                }
                if(in.key[SDLK_ESCAPE] || (temp==7 && in.mousebuttons[SDL_BUTTON_LEFT])){sortiedeboucle = true;}
            }
            in.key[SDLK_RETURN] = 0;
            in.key[SDLK_ESCAPE] = 0;
            in.mousebuttons[SDL_BUTTON_LEFT] = 0;
            updateEvents(&in);
            *menu = -1;
        }

        if(*menu == 4) // quitter le jeu
        {
            in.quit = 1;
        }

        if(*menu == -1)
        {
            *menu = afficherMenu(in, screen, imageMenu);
        }

        SDL_Flip(screen);
    } // end main loop

    // sauvegarde du score
    sauvegarderScore(score,nameUser.c_str());

    // free pointeurs
    free(score);
    free(numeroDeck);
    delete menu;

    // free loaded bitmap and created surface
    free_png(monTabImage, imageMenu, imageEditeur);

    SDL_FreeSurface(screen);

    for(int i = 0 ; i < NB_IMAGE_INTERFACE ; i++)
    {
        SDL_FreeSurface(imageinterface[i]);
    }
    free(imageinterface);

    for(int i = 0 ; i < NOMBRE_POLICE ; i++)
    {
        TTF_CloseFont(police[i]);
    }
    free(police);

    // libération des sons
    for(int i = 0 ; i < NOMBRE_MUSIQUE ; i++)
    {
        FMOD_Sound_Release(monTabZic[i]);
    }

    // fermeture propre de fmodex
    FMOD_System_Close(system);
    FMOD_System_Release(system);

    // all is well ;)
    // printf("Exited cleanly\n");

    return 0;
}

