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


#include "jeu.h"

using namespace std;


int cardGame(int *** p_monTab, Input p_in, SDL_Surface * p_monTabImage[NOMBRE_CARTE+1], SDL_Surface * p_imageinterface[15], SDL_Surface * p_screen,TTF_Font* p_police[NOMBRE_POLICE], int * p_score, ARG_MUSIC, int * p_numeroDeck)
{
    for(int i=0;i<40;i++)
    {
        for(int j=0;j<5;j++)
        {
            p_monTab[0][i][j] = 0;
            p_monTab[1][i][j] = 0;
            p_monTab[2][i][j] = 0;
        }
    }

    int memoireJeu[5][5];

    for(int i=0;i<5;i++)
    {
        for(int j=0;j<5;j++)
        {
            memoireJeu[i][j] = 0;
        }
    }

    //buildDeck(p_monTab[1]);
    int a = *p_numeroDeck -1;
    char c[1];
    itoa(a,c,8);
    std::string d ;
    d = "deck";
    d += c;
    loadDeck(p_monTab[1],d.c_str());
    buildDeck(p_monTab[2]);

    int vie[2] = {10000,10000};

    bool peutPlacer = false;
    bool peutPrendre = false;
    bool test[5] = {false,false,false,false,false};
    bool zone[5] = {false,false,false,false,false};
    bool peutPiocher = true;
    bool peutAttaquer = false;

    bouton * pressPioche = new bouton("Piocher");

    int tempsPrecedent = 0, tempsActuel = 0;
    while(!p_in.key[SDLK_ESCAPE] && !p_in.quit && ((vie[0] != 0) && (vie[1] != 0)))
    {
        updateEvents(&p_in);

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

        // test des boutons
        pressPioche->testPositionPiocheCombat(p_in, peutPiocher);

        //affichage
        majAffichage(p_monTab[0],p_monTabImage,p_imageinterface,p_screen,vie,p_police, p_in, test, pressPioche);

        // pioche
        if((p_in.key[SDLK_RETURN] || pressPioche->GetinUse()) && peutPiocher)
        {
            p_in.mousebuttons[SDL_BUTTON_LEFT] = 0;
            pressPioche->SetinUse(false); // remettre le bouton à zéro
            piocher(p_monTab);
            p_in.key[SDLK_RETURN] = 0;
            peutPlacer = true;
            peutPiocher = false;
            peutPrendre = true;
            peutAttaquer = true;
            IA(p_monTab,memoireJeu);
            FMOD_System_PlaySound(p_system, FMOD_CHANNEL_FREE, p_monTabZic[0], 0, NULL);
        }

        // placement
        if(peutPlacer){cliquerGlisser(p_in,p_monTab[0],test,zone, peutPrendre);}

        for(int i=0;i<5;i++)
        {
            for(int j=0;j<5;j++)
            {
                if(test[i] && zone[j])
                {
                    jouerCarte(p_monTab[0], i, j+10, VAR_MUSIC2);
                    for(int k=0;k<5;k++)
                    {
                        zone[k] = false;
                        test[k] = false;
                        peutPlacer = true;
                        peutPrendre = true;
                    }
                }
            }
        }

        // combat
        if((p_in.key[SDLK_SPACE] || pressPioche->GetinUse()) && peutAttaquer)
        {
            for(int i=0;i<5;i++)
            {
                for(int j=0;j<5;j++)
                {
                    p_monTab[0][20+i][j] = memoireJeu[i][j];
                }

                majAffichage(p_monTab[0],p_monTabImage,p_imageinterface,p_screen,vie,p_police, p_in, test, pressPioche);

                SDL_Delay(500);
            }

            majAffichage(p_monTab[0],p_monTabImage,p_imageinterface,p_screen,vie,p_police, p_in, test, pressPioche);


            applyEffect(p_monTab);


            majAffichage(p_monTab[0],p_monTabImage,p_imageinterface,p_screen,vie,p_police, p_in, test, pressPioche);

            SDL_Delay(1000);

            for(int i=0;i<5;i++)
            {
                combat(p_monTab[0][10+i], p_monTab[0][20+i], vie);
            }
            peutPlacer = false;
            peutPrendre = false;
            peutAttaquer = false;
            peutPiocher = true;
            p_in.mousebuttons[SDL_BUTTON_LEFT] = 0;
            pressPioche->SetinUse(false); // remettre le bouton à zéro

            FMOD_System_PlaySound(p_system, FMOD_CHANNEL_FREE, p_monTabZic[1], 0, NULL);
        }

        majAffichage(p_monTab[0],p_monTabImage,p_imageinterface,p_screen,vie,p_police, p_in, test, pressPioche);

        // fin de tour

    }
    delete pressPioche;

    return calculVictoire(p_score, vie, p_imageinterface, p_screen, p_police);
}


void buildDeck(int ** p_deck)
{
    srand(SDL_GetTicks());
    string way;
    way = cheminFile + "card.txt";
    ifstream fichier(way.c_str(), ios::in);  // on ouvre le fichier en lecture

    if(fichier)  // si l'ouverture a réussi
    {
        string ligne = "";
        string temp = "";

        for(int i=0;i<40;i++)
        {
            p_deck[i][0] = rand()%((NOMBRE_CARTE+1)-1) + 1;
                //cerr << p_deck[i][0] << endl;
            ligne = niemeLigne(way.c_str(), p_deck[i][0]);
            temp = (extract_ssString(ligne.c_str(), '&'));
                //cerr << temp << endl;
            p_deck[i][1] = std::atoi( temp.c_str() );
            temp = (extract_ssString(ligne.c_str(), '$'));
                //cerr << temp << endl;
            p_deck[i][2] = std::atoi( temp.c_str() );
            temp = (extract_ssString(ligne.c_str(), '*'));
                //cerr << temp << endl;
            p_deck[i][3] = std::atoi( temp.c_str() );
            temp = (extract_ssString(ligne.c_str(), '!'));
                //cerr << temp << endl;
            p_deck[i][4] = std::atoi( temp.c_str() );
        }

    }
    else  // sinon
            cerr << "Impossible d'ouvrir le fichier !" << endl;

    fichier.close();  // on ferme le fichier

}


void loadDeck(int ** p_deck, std::string adversaire)
{
    string way;
    way = cheminFile + adversaire.c_str() + ".txt";
    ifstream sourceDeck(way.c_str(), ios::in);  // on ouvre le fichier du deck en lecture

    if(sourceDeck)  // si l'ouverture a réussi
    {
        for(int i=0;i<40;i++)
        {
            int a = 0;
            sourceDeck >> a;
            p_deck[i][0] = a;
        }
    }
    else  // sinon
            cerr << "Impossible d'ouvrir le fichier !" << endl;

    sourceDeck.close();  // on ferme le fichier


    way = cheminFile + "card.txt";
    ifstream fichier(way.c_str(), ios::in);  // on ouvre le fichier des cartes en lecture

    if(fichier)  // si l'ouverture a réussi
    {
        string ligne = "";
        string temp = "";

        for(int i=0;i<40;i++)
        {
            ligne = niemeLigne(way.c_str(), p_deck[i][0]);
            temp = (extract_ssString(ligne.c_str(), '&'));
                //cerr << temp << endl;
            p_deck[i][1] = std::atoi( temp.c_str() );
            temp = (extract_ssString(ligne.c_str(), '$'));
                //cerr << temp << endl;
            p_deck[i][2] = std::atoi( temp.c_str() );
            temp = (extract_ssString(ligne.c_str(), '*'));
                //cerr << temp << endl;
            p_deck[i][3] = std::atoi( temp.c_str() );
            temp = (extract_ssString(ligne.c_str(), '!'));
                //cerr << temp << endl;
            p_deck[i][4] = std::atoi( temp.c_str() );
        }

    }
    else  // sinon
            cerr << "Impossible d'ouvrir le fichier !" << endl;

    fichier.close();  // on ferme le fichier
}


int piocher(int *** p_monTab)
{
    srand(SDL_GetTicks());

    int j = 0;
    int n = 0;
    int nbCartesRestantes1 = 0;
    int nbCartesRestantes2 = 0;
    for(int temp = 0; temp<40 ; temp++)
    {
        if(p_monTab[1][temp][0] != 0){nbCartesRestantes1++;}
        if(p_monTab[2][temp][0] != 0){nbCartesRestantes2++;}
    }

    while(j<5 && nbCartesRestantes1 > 0)
    {
        if(p_monTab[0][j][0] == 0)
        {
            int nombreAleat = rand()%(nbCartesRestantes1-1);
            for(int k = 0; k<5 ; k++)
            {
                p_monTab[0][j][k] = p_monTab[1][nombreAleat][k];
                p_monTab[1][nombreAleat][k] = p_monTab[1][nbCartesRestantes1-1][k];
                p_monTab[1][nbCartesRestantes1-1][k] = 0;
            }
            nbCartesRestantes1--;
            j++;
        }
        else{j++;}
    }

    while(n<5 && nbCartesRestantes2 > 0)
    {
        if(p_monTab[0][n+30][0] == 0)
        {
            int nombreAleat = rand()%(nbCartesRestantes2-1);
            for(int k = 0; k<5 ; k++)
            {
                p_monTab[0][n+30][k] = p_monTab[2][nombreAleat][k];
                p_monTab[2][nombreAleat][k] = p_monTab[2][nbCartesRestantes2-1][k];
                p_monTab[2][nbCartesRestantes2-1][k] = 0;
            }
            nbCartesRestantes2--;
            n++;
        }
        else{n++;}
    }


    if(n==5 && j==5){return 0;}
    else {return 1;}
}


void combat(int * c1,int * c2, int p_vie[2])
{
    int res = c1[1] - c2[1];
    if(res>=0)
    {
        p_vie[1] -= res;
        c2[2]--;
    }
    if(res<=0)
    {
        p_vie[0] += res;
        c1[2]--;
    }

    if(p_vie[0]<0){p_vie[0]=0;}
    if(p_vie[1]<0){p_vie[1]=0;}

    actualisationCarte(c1);
    actualisationCarte(c2);
}


void actualisationCarte(int * c)
{
    if(c[2] == 0){c[0]=0; c[1]=0; c[3]=0; c[4]=0;}
}


void IA(int  *** p_monTab, int p_memoire[5][5])
{
    for(int i=0;i<5;i++)
    {
        if(p_monTab[0][20+i][0] == 0)
        {
            if((p_monTab[0][30+i][0] != 0) && (p_monTab[0][20+i][0] == 0))
            {
                p_memoire[i][0] = p_monTab[0][30+i][0];
                p_memoire[i][1] = p_monTab[0][30+i][1];
                p_memoire[i][2] = p_monTab[0][30+i][2];
                p_memoire[i][3] = p_monTab[0][30+i][3];
                p_memoire[i][4] = p_monTab[0][30+i][4];

                p_monTab[0][30+i][0] = 0;
                p_monTab[0][30+i][1] = 0;
                p_monTab[0][30+i][2] = 0;
                p_monTab[0][30+i][3] = 0;
                p_monTab[0][30+i][4] = 0;
            }
        }
        if(p_monTab[0][20+i][0] != 0)
        {
            p_memoire[i][0] = p_monTab[0][20+i][0];
            p_memoire[i][1] = p_monTab[0][20+i][1];
            p_memoire[i][2] = p_monTab[0][20+i][2];
            p_memoire[i][3] = p_monTab[0][20+i][3];
            p_memoire[i][4] = p_monTab[0][20+i][4];
        }
    }
}


void jouerCarte(int ** p_carte, int p_numMain, int p_numTerrain, ARG_MUSIC)
{
    if((p_carte[p_numMain][0] != 0) && (p_carte[p_numTerrain][0] == 0))
    {
        p_carte[p_numTerrain][0] = p_carte[p_numMain][0];
        p_carte[p_numTerrain][1] = p_carte[p_numMain][1];
        p_carte[p_numTerrain][2] = p_carte[p_numMain][2];
        p_carte[p_numTerrain][3] = p_carte[p_numMain][3];
        p_carte[p_numTerrain][4] = p_carte[p_numMain][4];

        p_carte[p_numMain][0] = 0;
        p_carte[p_numMain][1] = 0;
        p_carte[p_numMain][2] = 0;
        p_carte[p_numMain][3] = 0;
        p_carte[p_numMain][4] = 0;

        FMOD_System_PlaySound(p_system, FMOD_CHANNEL_FREE, p_monTabZic[0], 0, NULL);
    }
    else{FMOD_System_PlaySound(p_system, FMOD_CHANNEL_FREE, p_monTabZic[2], 0, NULL);}
}


void applyEffect(int *** p_monTab)
{
    for(int i = 10;i<25;i++)
    {
        if(p_monTab[0][i][0] != 0)
        {
            if(p_monTab[0][i][4] == 0){p_monTab[0][i][2] = 0;}
            else if(p_monTab[0][i][4] == 1){p_monTab[0][i][4] = 1;}
            else if(p_monTab[0][i][4] == 2){p_monTab[0][i][2] += 1;p_monTab[0][i][4] = 1;}
            else if(p_monTab[0][i][4] == 3){p_monTab[0][i][1] += 500;p_monTab[0][i][4] = 1;}
            else if(p_monTab[0][i][4] == 4)
            {
                bool test = false;
                for(int k=10;k<15;k++){if(p_monTab[0][k][3] == 4){test = true;}}
                for(int k=20;k<25;k++){if(p_monTab[0][k][3] == 4){test = true;}}
                if(!test){p_monTab[0][i][2] = 0;}
            }
            else if(p_monTab[0][i][4] == 5){p_monTab[0][i][1] += 500;}
            else if(p_monTab[0][i][4] == 6){p_monTab[0][i][4] = 3;}
            else if(p_monTab[0][i][4] == 7){p_monTab[0][i][4] = 5;}
            else if(p_monTab[0][i][4] == 8)
            {
                for(int k=10;k<25;k++){if(p_monTab[0][k][0] == 30){p_monTab[0][i][1] += 500;}}
            }
            else if(p_monTab[0][i][4] == 9)
            {
                for(int z = 10; z<25;z++)
                {
                    p_monTab[0][z][2] = 0 ;
                }
                for(int i = 10;i<25;i++)
                {
                    actualisationCarte(p_monTab[0][i]);
                }
            }
            else if(p_monTab[0][i][4] == 10)
            {
                p_monTab[0][i][0] = 1;
                p_monTab[0][i][1] = 3000;
                p_monTab[0][i][2] = 1;
                p_monTab[0][i][3] = 2;
                p_monTab[0][i][4] = 1;
            }
            else if(p_monTab[0][i][4] == 11){p_monTab[0][i][4] = 10;}
        }
    }

    for(int i = 10;i<25;i++)
    {
        actualisationCarte(p_monTab[0][i]);
    }

}


void cliquerGlisser(Input p_in, int ** p_monTab, bool p_test[5], bool p_zone[5], bool p_peutPrendre)
{
    int i =0;
    bool test = false;
    while(!test)
    {
        if( p_in.mousex >= (12+128*i) && p_in.mousex <= (12+128*i +104))
        {
            if(p_peutPrendre && p_in.mousebuttons[SDL_BUTTON_LEFT] && p_in.mousey >= 524 && p_in.mousey <= 628 && p_monTab[i][0] != 0)
            {
                p_test[i] = true;
                p_peutPrendre = false;
                for(int i=0;i<5;i++)
                {
                    p_zone[i] = false;
                }
                test = true;
            }
            if(!p_in.mousebuttons[SDL_BUTTON_LEFT] && p_in.mousey >= 352 && p_in.mousey <= 460 && p_monTab[i+10][0] == 0)
            {
                p_zone[i] = true;
                p_peutPrendre = true;
                test = true;
            }
            if(p_in.mousebuttons[SDL_BUTTON_RIGHT] or (!p_in.mousebuttons[SDL_BUTTON_LEFT] && !(p_in.mousey >= 352 && p_in.mousey <= 460)))
            {

                for(int i=0;i<5;i++)
                {
                    p_test[i] = false;
                }
            }
        }

        i++;
        if(i>4){test=true;}
    }
}


int calculVictoire(int * p_score, int * vie, SDL_Surface * p_imageinterface[15], SDL_Surface * p_screen, TTF_Font* p_police[NOMBRE_POLICE])
{

    SDL_Rect place = {0,0,0,0};

    if((vie[0] == 0) || (vie[1] == 0))
    {
        SDL_Delay(1000);
        SDL_BlitSurface(p_imageinterface[2], 0, p_screen, &place);

        if(!vie[0] && vie[1])
        {
            place.x = LARGEUR_ECRAN/2-p_imageinterface[11]->w/2;
            place.y = HAUTEUR_ECRAN/2-p_imageinterface[11]->h/2;
            SDL_BlitSurface(p_imageinterface[11], 0, p_screen, &place);
            *p_score = *p_score + 3000 - vie[1];
        }
        if(!vie[1] && vie[0])
        {
            place.x = LARGEUR_ECRAN/2-p_imageinterface[11]->w/2;
            place.y = HAUTEUR_ECRAN/2-p_imageinterface[11]->h/2;
            SDL_BlitSurface(p_imageinterface[10], 0, p_screen, &place);
            *p_score = *p_score +3000 + vie[0];
        }
        if(!vie[1] && !vie[0])
        {
            place.x = LARGEUR_ECRAN/2-p_imageinterface[14]->w/2;
            place.y = HAUTEUR_ECRAN/2-p_imageinterface[14]->h/2;
            SDL_BlitSurface(p_imageinterface[14], 0, p_screen, &place);
            *p_score = *p_score + 2500;
        }
        SDL_Flip(p_screen);
        SDL_Delay(1000);
    }

    *p_score -= 3000;
    //if(p_score<0){p_score =0;}

    place.x = 0;
    place.y = 0;
    place.w = 0;
    place.h = 0;
    SDL_BlitSurface(p_imageinterface[2], 0, p_screen, &place);
    afficherScore(p_imageinterface, p_screen, p_score, "SCORE", p_police);

    place.x = LARGEUR_ECRAN/2 - p_imageinterface[13]->w/2;
    place.y = 3*HAUTEUR_ECRAN/4 - p_imageinterface[13]->h/2;
    SDL_BlitSurface(p_imageinterface[13], 0, p_screen, &place);

    SDL_Flip(p_screen);

    return *p_score;
}

void highscore(SDL_Surface * p_imageMenu[15], Input p_in, int * p_score, SDL_Surface * p_imageinterface[15], SDL_Surface * p_screen, TTF_Font* p_police[NOMBRE_POLICE], int * p_menu)
{
    bool sortiedeboucle = false;
    int classement = 1;

    p_in.mousebuttons[SDL_BUTTON_LEFT] = 0;
    while(!p_in.key[SDLK_ESCAPE] && !p_in.quit && !p_in.key[SDLK_RETURN] && !sortiedeboucle)
    {
        updateEvents(&p_in);
        int temp = 5;
        if(testCurseur2(p_in)>=3){temp = testCurseur2(p_in)+3;}else{temp = 5;}
        SDL_BlitSurface(p_imageMenu[temp], 0, p_screen, 0);
        afficherScore(p_imageinterface, p_screen, p_score, "SCORE", p_police);
        SDL_Flip(p_screen);
        if(p_in.key[SDLK_RETURN] || (temp==6 && p_in.mousebuttons[SDL_BUTTON_LEFT])){classement++;}
        if(p_in.key[SDLK_ESCAPE] || (temp==7 && p_in.mousebuttons[SDL_BUTTON_LEFT])){sortiedeboucle = true;}
    }
    p_in.key[SDLK_RETURN] = 0;
    p_in.key[SDLK_ESCAPE] = 0;
    p_in.mousebuttons[SDL_BUTTON_LEFT] = 0;
    updateEvents(&p_in);
    *p_menu = -1;
}
// aide pour un entier aléatoire dans [a;b[ faire rand()%(b-a) +a
