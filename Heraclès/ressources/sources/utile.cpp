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


#include "utile.h"


#include "bouton.h"

using namespace std;

void load_png(ARGUMENT_IMAGE)
{
    string lien, way;
    way = cheminFile + "card.txt";
    ifstream fichier(way.c_str(), ios::in);  // on ouvre le fichier en lecture

    if(fichier)  // si l'ouverture a réussi
    {
        int nbLignes = nombreLignes(way.c_str()) - 1; // on enlève la première ligne
        string ligne = "";
        string temp = "";
        for(int i = 0;i<nbLignes;i++)
        {
                lien = cheminImage+"playa";
                ligne = niemeLigne(way.c_str(), i);
                temp = (extract_ssString(ligne.c_str(), '#'));
                lien = lien + temp + ".png";
                p_monTabImage[i] = SDL_DisplayFormat(IMG_Load(lien.c_str()));
                if (!p_monTabImage[i])
                {
                    printf("Unable to load png: %s\n", SDL_GetError());
                }

        }
        for(int i = nbLignes;i<NOMBRE_CARTE+1;i++)
        {
                p_monTabImage[i] = NULL;
        }
    }
    else  // sinon
        cerr << "Impossible d'ouvrir le fichier !" << endl;

    fichier.close();  // on ferme le fichier

        for(int i = 0 ; i < NB_IMAGE_MENU ; i++)
        {
                char a[1];
                itoa(i,a,8);
                lien = cheminImage + "menu0" + a + ".png";
                p_imageMenu[i] = SDL_DisplayFormat(IMG_Load(lien.c_str()));
        }

    // charger les images d'interface graphique de l'éditeur
    char a[1];
    for(int x = 0 ; x < (NB_IMAGE_EDITEUR) ; x++)
    {
        itoa(x,a,8);
        std::string zero;
        if(x<10){zero = '0';}   else{zero="";}
        way = cheminImage + "editeur" + zero.c_str() + a + ".png";

        p_imageEditeur[x] = SDL_DisplayFormat(IMG_Load(way.c_str()));
    }

    SDL_SetColorKey(p_imageEditeur[5], SDL_SRCCOLORKEY, SDL_MapRGB(p_imageEditeur[5]->format, 100, 255, 100));
    SDL_SetColorKey(p_imageEditeur[6], SDL_SRCCOLORKEY, SDL_MapRGB(p_imageEditeur[6]->format, 100, 255, 100));
}

void free_png(SDL_Surface * p_monTab[NOMBRE_CARTE+1], SDL_Surface * p_imageMenu[NB_IMAGE_MENU], SDL_Surface * p_imageEditeur[NB_IMAGE_EDITEUR])
{
    for(int i = 0 ; i < NOMBRE_CARTE+1 ; i++)
    {
        if(p_monTab[i] != NULL)
        {
            SDL_FreeSurface(p_monTab[i]);
        }
    }
    free(p_monTab);

    for(int i = 0 ; i < NB_IMAGE_MENU ; i++)
    {
        if(p_imageMenu[i] != NULL)
        {
            SDL_FreeSurface(p_imageMenu[i]);
        }
    }
    free(p_imageMenu);

    // suppression des images de l'éditeur
    for(int x = 0 ; x < NB_IMAGE_EDITEUR ; x++)
    {
        SDL_FreeSurface(p_imageEditeur[x]);
    }
    free(p_imageEditeur);
}

string extract_ssString(string p_chaine,char p_borne)
{
    unsigned int i = 0;
    int j = 0;
    string res = "";
    while((j!=2) or (i < p_chaine.size()))
    {
        if(p_chaine[i] == p_borne){j++;}
        if(j==1 && p_chaine[i] != p_borne){res += p_chaine[i];}
        i++;
    }

    return res;
}

int nombreLignes (const string & filename)
{
    ifstream fichier(filename.c_str());
    string s;

    if(fichier){
        unsigned int count = 0;
        while(std::getline(fichier,s)) ++count;
        return count;
    }else{
        std::cout << "Ne peut ouvrir " << filename << std::endl;
    }
    fichier.close();
    return 0;
}

string niemeLigne(const std::string & filename, int p_count)
{
    ifstream p_fichier(filename.c_str());
    int i = 0;
    string ligne = "";
    bool test = false;
    while(!test && getline(p_fichier, ligne))
    {
        if(i == p_count)
        {
            test = true;
        }
        i++;
    }
    p_fichier.close();
    return ligne;
}

void updateEvents(Input *in)
{
	SDL_Event event;
        in->mousebuttons[SDL_BUTTON_WHEELUP] = 0;
        in->mousebuttons[SDL_BUTTON_WHEELDOWN] = 0;
	while(SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_KEYDOWN:
			in->key[event.key.keysym.sym]=1;
			break;
		case SDL_KEYUP:
			in->key[event.key.keysym.sym]=0;
			break;
		case SDL_MOUSEMOTION:
			in->mousex=event.motion.x;
			in->mousey=event.motion.y;
			in->mousexrel=event.motion.xrel;
			in->mouseyrel=event.motion.yrel;
			break;
		case SDL_MOUSEBUTTONDOWN:
			in->mousebuttons[event.button.button]=1;
			break;
		case SDL_MOUSEBUTTONUP:
                        if (event.button.button!=SDL_BUTTON_WHEELUP && event.button.button!=SDL_BUTTON_WHEELUP)
			   in->mousebuttons[event.button.button]=0;
			break;
		case SDL_QUIT:
			in->quit = 1;
			break;
		default:
			break;
		}
	}
}

int loadNombreDeCartes()
{
    std::string way;
    way = cheminFile + "card.txt";
    int nombreCartes = 0;
    std::ifstream fichier(way.c_str(), std::ios::in);  // on ouvre le fichier en lecture
    if(fichier)  // si l'ouverture a réussi
    {
        nombreCartes = nombreLignes(way.c_str()) - 2; // on enlève la première ligne

    }
    fichier.close();
    return nombreCartes;
}

int stringTOint(std::string chaine)
{
    int a;
    a = atoi(chaine.c_str());
    return a;
}

void chargerHighscores(int p_highscores[3], std::string * p_highscoreurs)
{
    std::string way;
    std::string ligne;
    way = cheminFile + "highscore.txt";
    std::ifstream fichier(way.c_str(), std::ios::in);  // on ouvre le fichier en lecture
    if(fichier)  // si l'ouverture a réussi
    {
        getline(fichier, ligne);
        p_highscores[0] = stringTOint(extract_ssString(ligne.c_str(), '^'));
        p_highscoreurs[0] = (extract_ssString(ligne.c_str(), '/'));
        getline(fichier, ligne);
        p_highscores[1] = stringTOint(extract_ssString(ligne.c_str(), '^'));
        p_highscoreurs[1] = (extract_ssString(ligne.c_str(), '/'));
        getline(fichier, ligne);
        p_highscores[2] = stringTOint(extract_ssString(ligne.c_str(), '^'));
        p_highscoreurs[2] = (extract_ssString(ligne.c_str(), '/'));
    }
    fichier.close();
}

void sauvegarderScore(int * p_score, std::string p_name)
{
    int highscores[4] = {0};
    std::string highscoreurs[4];
    chargerHighscores(highscores,highscoreurs);

    highscoreurs[3] = p_name;
    highscores[3] = min(highscores[0],*p_score);
    highscores[0] = max(highscores[0],*p_score);
    if(highscores[0] == *p_score){highscoreurs[3] = highscoreurs[0]; highscoreurs[0] = p_name;}

    *p_score = highscores[3];
    p_name = highscoreurs[3];
    highscores[3] = min(highscores[1],*p_score);
    highscores[1] = max(highscores[1],*p_score);
    if(highscores[1] == *p_score){highscoreurs[3] = highscoreurs[1]; highscoreurs[1] = p_name;}

    *p_score = highscores[3];
    p_name = highscoreurs[3];
    highscores[3] = min(highscores[2],*p_score);
    highscores[2] = max(highscores[2],*p_score);
    if(highscores[2] == *p_score){highscoreurs[2] = p_name;}

    std::string way;
    way = cheminFile + "highscore.txt";
    std::ofstream fichier(way.c_str(), ios::out | ios::trunc);
    if(fichier)  // si l'ouverture a réussi
    {
        fichier << "^" << highscores[0] << "^ /" << highscoreurs[0] << "/" << std::endl;
        fichier << "^" << highscores[1] << "^ /" << highscoreurs[1] << "/" << std::endl;
        fichier << "^" << highscores[2] << "^ /" << highscoreurs[2] << "/" << std::endl;
    }
    fichier.close();
}

void chargerDeckEditeur(int p_deck[NOMBRE_DECK_PERSO][40], std::string p_listeNoms[NOMBRE_CARTE])
{
    std::string way;
    char a[1];

    // charger les decks

    for(int x = 0 ; x < NOMBRE_DECK_PERSO ; x++)
    {
        itoa(x,a,8);
        way = cheminFile + "deck" + a + ".txt";
        std::ifstream fichier(way.c_str(), std::ios::in);  // on ouvre le fichier en lecture
        if(fichier)  // si l'ouverture a réussi
        {
            for(int i = 0 ; i < 40 ; i++)
            {
                fichier >> p_deck[x][i] ;
            }
        }
        fichier.close();
    }

    // charger les noms des cartes

    way = cheminFile + "card_name.txt";
    std::ifstream fichier(way.c_str(), std::ios::in);  // on ouvre le fichier en lecture
    if(fichier)  // si l'ouverture a réussi
    {
        for(int i = 0 ; i < NOMBRE_CARTE ; i++)
        {
            fichier >> p_listeNoms[i] ;
        }
    }
    fichier.close();

}

void dechargerDeckEditeur(int p_deck[NOMBRE_DECK_PERSO][40])
{
    // suppression des boutons des cartes
    // supprime car changement d'idée

    // suppression des fleches
    // supprime car changement d'idée
    /*for(int x = 0 ; x < 2 ; x++)
    {
        if(p_boutonsDefilement[x] != NULL)
        {
            delete p_boutonsDefilement[x];
        }
    }*/
}

void sauvegarderDeckEditeur(int p_deck[NOMBRE_DECK_PERSO][40])
{
    std::string way;
    char a[1];

    for(int x = 0 ; x < NOMBRE_DECK_PERSO ; x++)
    {
        itoa(x,a,8);
        way = cheminFile + "deck" + a + ".txt";
        std::ofstream fichier(way.c_str(), ios::out | ios::trunc);  // on ouvre le fichier en écriture
        if(fichier)  // si l'ouverture a réussi
        {
            for(int i = 0 ; i < 40 ; i++)
            {
                fichier << p_deck[x][i] << " ";
            }
        }
        fichier.close();
    }
}

void editeurDeck(int p_deck[NOMBRE_DECK_PERSO][40], SDL_Surface * p_imageEditeur[NB_IMAGE_EDITEUR], Input p_in, SDL_Surface* p_screen, int * p_numeroDeck, int ** p_index, TTF_Font* p_police[NOMBRE_POLICE], std::string * p_cardsName, int * p_b)
{
    testCurseurEditeur(p_in,p_numeroDeck);

    afficherEditeur(p_deck,p_imageEditeur,p_screen, p_numeroDeck, p_index, p_police, p_cardsName, p_in, p_b);
}

void afficherEditeur(int p_deck[NOMBRE_DECK_PERSO][40], SDL_Surface * p_imageEditeur[NB_IMAGE_EDITEUR], SDL_Surface * p_screen, int * p_numeroDeck, int ** p_index, TTF_Font* p_police[NOMBRE_POLICE], std::string * p_cardsName, Input p_in, int * b)
{
    // affichage fond
    SDL_Rect nulle = {0,0,0,0};
    SDL_Rect selection = {0,0,32,32};
    SDL_Rect emplacement = {0,160,0,0};
    SDL_BlitSurface(p_imageEditeur[0], NULL, p_screen, &nulle);
    nulle = {0,0,640,128};
    SDL_BlitSurface(p_imageEditeur[*p_numeroDeck], &nulle, p_screen, &nulle);
    nulle = {0,320,0,0};
    SDL_BlitSurface(p_imageEditeur[5], NULL, p_screen, &nulle);

    testScan(p_in, b, p_deck, p_numeroDeck);

    afficherInfoEditeur(b, p_screen, p_imageEditeur, p_police, p_index, p_cardsName);


    for(int i = 0 ; i < 40 ; i++)
    {
        emplacement.x = i*32 - 320*(i/10);
        emplacement.y = 160 + (i/10) * 32;
        selection.x = (p_deck[(*p_numeroDeck)-1][i])*32 - 320*((p_deck[(*p_numeroDeck)-1][i])/10);
        selection.y = ((p_deck[(*p_numeroDeck)-1][i])/10) * 32;
        SDL_BlitSurface(p_imageEditeur[5],&selection,p_screen,&emplacement);
    }

    SDL_Flip(p_screen);
}

void testCurseurEditeur(Input p_in, int * p_numeroDeck)
{
    if(p_in.mousey >= 10 && p_in.mousey < 10 + 108 && p_in.mousebuttons[SDL_BUTTON_LEFT])
    {
        if(p_in.mousex >= 10 && p_in.mousex < 10 + 200)
        {
            *p_numeroDeck = 1;
        }
        if(p_in.mousex >= 220 && p_in.mousex < 220 + 200)
        {
            *p_numeroDeck = 2;
        }
        if(p_in.mousex >= 450 && p_in.mousex < 450 + 200)
        {
            *p_numeroDeck = 3;
        }
    }
}


void testScan(Input p_in, int * p_b, int p_deck[NOMBRE_DECK_PERSO][40], int * p_numeroDeck)
{
    SDL_Rect temp = {p_in.mousex,p_in.mousey-320,320,320};
    int y = 0;
    if(temp.x >=0 && temp.x < 320 && temp.y >=0 && temp.x < 320)
    {
        y = (temp.x / 32) + 10*(temp.y / 32);
        if(y<=NOMBRE_CARTE){*p_b = y;}
        else{*p_b = 0;}
        /*if(p_in.mousebuttons[SDL_BUTTON_LEFT] == SDL_PRESSED )
        {
            p_in.mousebuttons[SDL_BUTTON_LEFT] = SDL_RELEASED;
            int i = 0;
            bool stop = false;
            while(i < 40 && p_deck[*p_numeroDeck-1][i] != 0)
                {
                    i++;
                    if(i>=40){stop = true;}
                }
            if(!stop)
            {p_deck[*p_numeroDeck-1][i] = *p_b;}

            p_in.mousebuttons[SDL_BUTTON_LEFT] = SDL_RELEASED;
        }*/
    }
    else if(p_in.mousex < 320 && p_in.mousey >=160 && p_in.mousey < 288)
    {
        temp = {p_in.mousex, p_in.mousey - 160};
        y = (temp.x / 32) + 10*(temp.y / 32);
        *p_b = p_deck[(*p_numeroDeck)-1][y];
        /*if(p_in.mousebuttons[SDL_BUTTON_LEFT] == SDL_PRESSED)
        {
            p_in.mousebuttons[SDL_BUTTON_LEFT] = SDL_RELEASED;
            p_deck[*p_numeroDeck-1][y] = 0;
        }*/
    }
    else{*p_b = 0;}

    p_in.mousebuttons[SDL_BUTTON_LEFT] = SDL_RELEASED;
}


void afficherInfoEditeur(int * p_carteScannee, SDL_Surface * p_screen, SDL_Surface * p_imageEditeur[NB_IMAGE_EDITEUR], TTF_Font* p_police[NOMBRE_POLICE], int ** p_index, std::string * p_cardsName)
{
    SDL_Surface * texte_a_coller = NULL;
    SDL_Rect place = {0,0,0,0};
    SDL_Rect selection = {0,0,208,208};
    ostringstream oss;
    std::string result = "";

    if((*p_carteScannee)>0 && (*p_carteScannee)<NOMBRE_CARTE+1)
    {
        oss << p_index[*p_carteScannee][1];
        result = "FORCE";
        texte_a_coller = TTF_RenderText_Blended(p_police[0], result.c_str(), {220,30,30});;
        place = {376+10, 448};
        SDL_BlitSurface(texte_a_coller, 0, p_screen, &place);
        SDL_FreeSurface(texte_a_coller);

        result = oss.str();
        texte_a_coller = TTF_RenderText_Blended(p_police[1], result.c_str(), {240,50,50});;
        place = {376+190-texte_a_coller->w, 448+5};
        SDL_BlitSurface(texte_a_coller, 0, p_screen, &place);
        SDL_FreeSurface(texte_a_coller);

        result = "EFFET";
        texte_a_coller = TTF_RenderText_Blended(p_police[0], result.c_str(), {220,30,30});;
        place = {376+10, 448+50};
        SDL_BlitSurface(texte_a_coller, 0, p_screen, &place);
        SDL_FreeSurface(texte_a_coller);

        result = afficherEffet(*(p_carteScannee),p_index);
        texte_a_coller = TTF_RenderText_Blended(p_police[1], result.c_str(), {120,80,180});;
        place = {376+10, 450+75};
        SDL_BlitSurface(texte_a_coller, 0, p_screen, &place);
        SDL_FreeSurface(texte_a_coller);

        result = (p_cardsName[(*p_carteScannee)-1]).c_str();
        texte_a_coller = TTF_RenderText_Blended(p_police[0], result.c_str(), {240,50,50});;
        place = {480-texte_a_coller->w/2,139};
        SDL_BlitSurface(texte_a_coller, 0, p_screen, &place);
        SDL_FreeSurface(texte_a_coller);
    }

    place = {376,185};
    selection = {(* p_carteScannee)*208 - 2080*((* p_carteScannee)/10),((* p_carteScannee)/10) * 208, 208, 208};
    SDL_BlitSurface(p_imageEditeur[6], &selection, p_screen, &place);
}

void initIndex(int ** p_deck)
{
    for(int i = 0 ; i < NOMBRE_CARTE+1 ; i++)
    {
        p_deck[i][0] = i;
    }

    std::string way = cheminFile + "card.txt";
    ifstream fichier(way.c_str(), ios::in);  // on ouvre le fichier des cartes en lecture

    if(fichier)  // si l'ouverture a réussi
    {
        string ligne = "";
        string temp = "";

        for(int i=0;i<NOMBRE_CARTE+1;i++)
        {
            if(i==0){ligne = niemeLigne(way.c_str(), p_deck[i][0]);}
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


