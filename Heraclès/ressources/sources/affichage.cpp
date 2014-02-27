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


#include "affichage.h"
#include "bouton.h"

using namespace std;

void afficherCarte(int ** p_monTab, SDL_Surface * p_monTabImage[NOMBRE_CARTE+1], SDL_Surface * p_ouColler)
{
    SDL_Rect place = {0,0,0,0};

    place = {12,12,0,0};
    SDL_BlitSurface(p_monTabImage[1], 0, p_ouColler, &place);
    place = {524,12,0,0};
    SDL_BlitSurface(p_monTabImage[2], 0, p_ouColler, &place);

    for(int i=0;i<5;i++)
    {
        if(p_monTab[i+10][0] != 0)
        {
            place = {(12+128*i),351};
            SDL_BlitSurface(p_monTabImage[p_monTab[i+10][0]], 0, p_ouColler, &place);
        }

        if(p_monTab[i][0] != 0)
        {
            place = {(12+128*i),524};
            SDL_BlitSurface(p_monTabImage[p_monTab[i][0]], 0, p_ouColler, &place);
        }
    }

}

void afficherCarteEnnemi(int ** p_monTab, SDL_Surface * p_monTabImage[NOMBRE_CARTE+1], SDL_Surface * p_ouColler)
{
    SDL_Rect place = {0,0,0,0};

    for(int i=0;i<5;i++)
    {
        if(p_monTab[i+20][0] != 0)
        {
            place = {(12+128*i),183};
            SDL_BlitSurface(p_monTabImage[p_monTab[i+20][0]], 0, p_ouColler, &place);
        }
    }
}

void afficherInterface(SDL_Surface * p_imageinterface[13], SDL_Surface * p_ouColler, int p_vie[2],TTF_Font* p_police[NOMBRE_POLICE])
{
    SDL_Rect place = {0,0,0,0};
    SDL_BlitSurface(p_imageinterface[5], 0, p_ouColler, &place);
    place = {128+12,12};
    SDL_BlitSurface(p_imageinterface[8], 0, p_ouColler, &place);
    place = {512-12-p_imageinterface[8]->w,12};
    SDL_BlitSurface(p_imageinterface[8], 0, p_ouColler, &place);
    place = {256+(128/2)-p_imageinterface[9]->w/2,128/2-p_imageinterface[9]->h/2};
    SDL_BlitSurface(p_imageinterface[9], 0, p_ouColler, &place);
    ostringstream oss;
    string result;
    oss << p_vie[0];
    result = oss.str();
    SDL_FreeSurface(p_imageinterface[6]);
    p_imageinterface[6] = TTF_RenderText_Blended(p_police[1], result.c_str(), {200,200,200});
    ostringstream oss2;
    oss2 << p_vie[1];
    result = oss2.str();
    SDL_FreeSurface(p_imageinterface[7]);
    p_imageinterface[7] = TTF_RenderText_Blended(p_police[1], result.c_str(), {200,200,200});;
    place = {128+(128/2)-p_imageinterface[6]->w/2,128/2-p_imageinterface[6]->h/2};
    SDL_BlitSurface(p_imageinterface[6], 0, p_ouColler, &place);
    place = {384+(128/2)-p_imageinterface[7]->w/2,128/2-p_imageinterface[7]->h/2};
    SDL_BlitSurface(p_imageinterface[7], 0, p_ouColler, &place);
}

void majAffichage(int ** p_monTab, SDL_Surface * p_monTabImage[NOMBRE_CARTE+1], SDL_Surface * p_imageinterface[13], SDL_Surface * p_ouColler, int p_vie[2],TTF_Font* p_police[NOMBRE_POLICE], Input p_in, bool p_test[5], bouton * p_bouton)
{
    afficherInterface(p_imageinterface, p_ouColler, p_vie, p_police);
    afficherCarte(p_monTab, p_monTabImage, p_ouColler);
    afficherCarteEnnemi(p_monTab, p_monTabImage, p_ouColler);
    afficherCliquerGlisser(p_monTab, p_test, p_monTabImage, p_in, p_ouColler);
    afficherInfos(p_monTab,p_imageinterface,p_ouColler,p_in,p_police);
    p_bouton->afficher(p_ouColler);
    SDL_Flip(p_ouColler);
}

void afficherScore(SDL_Surface * p_imageinterface[13], SDL_Surface * p_ouColler, int * p_score, std::string p_chaine, TTF_Font* p_police[NOMBRE_POLICE])
{
    SDL_Rect place = {0,0,0,0};
    ostringstream oss;
    oss << *p_score;
    string result = oss.str();
    SDL_FreeSurface(p_imageinterface[7]);
    p_imageinterface[7] = TTF_RenderText_Blended(p_police[2], result.c_str(), {255,255,255});;
    place = {LARGEUR_ECRAN/2-p_imageinterface[7]->w/2,HAUTEUR_ECRAN/2-p_imageinterface[7]->h/2 -50};
    SDL_BlitSurface(p_imageinterface[7], 0, p_ouColler, &place);

    result = p_chaine.c_str();
    SDL_FreeSurface(p_imageinterface[6]);
    p_imageinterface[6] = TTF_RenderText_Blended(p_police[2], result.c_str(), {255,255,255});;
    place = {LARGEUR_ECRAN/2-p_imageinterface[6]->w/2,HAUTEUR_ECRAN/2-p_imageinterface[6]->h/2 -p_imageinterface[7]->h - 10-50};
    SDL_BlitSurface(p_imageinterface[6], 0, p_ouColler, &place);
}

void afficherInfos(int ** p_monTab, SDL_Surface * p_imageinterface[13], SDL_Surface * p_ouColler, Input p_in,TTF_Font* p_police[NOMBRE_POLICE])
{
    SDL_Rect place = {0,0,0,0};
    ostringstream oss;
    bool test = false;
    int i = 0;
    string result = "";

    while(!test)
    {
        if( p_in.mousex >= (12+128*i) && p_in.mousex <= (12+128*i +104))
        {

            if(p_in.mousey >= 183 && p_in.mousey <= 286 && p_monTab[i+20][0] != 0)
            {
                place.x = p_in.mousex + testCurseur(p_in).x;
                place.y = p_in.mousey + testCurseur(p_in).y;
                SDL_BlitSurface(p_imageinterface[12], 0, p_ouColler, &place);
                int z=i+20;
                oss << p_monTab[i+20][1];
                result = "FORCE";
                SDL_FreeSurface(p_imageinterface[7]);
                p_imageinterface[7] = TTF_RenderText_Blended(p_police[0], result.c_str(), {220,30,30});;
                place = {p_in.mousex +12, p_in.mousey +8};
                place.x += testCurseur(p_in).x;
                place.y += testCurseur(p_in).y;
                SDL_BlitSurface(p_imageinterface[7], 0, p_ouColler, &place);
                result = oss.str();
                SDL_FreeSurface(p_imageinterface[6]);
                p_imageinterface[6] = TTF_RenderText_Blended(p_police[1], result.c_str(), {240,50,50});;
                place = {p_in.mousex +12, p_in.mousey +4 +p_imageinterface[7]->h};
                place.x += testCurseur(p_in).x;
                place.y += testCurseur(p_in).y;
                SDL_BlitSurface(p_imageinterface[6], 0, p_ouColler, &place);

                result = afficherEffet(z,p_monTab);
                SDL_FreeSurface(p_imageinterface[7]);
                p_imageinterface[7] = TTF_RenderText_Blended(p_police[1], result.c_str(), {120,80,180});;
                place = {p_in.mousex +12, p_in.mousey +15 + 2*(p_imageinterface[6]->h)};
                place.x += testCurseur(p_in).x;
                place.y += testCurseur(p_in).y;
                SDL_BlitSurface(p_imageinterface[7], 0, p_ouColler, &place);

                test = true;
            }

            if(p_in.mousey >= 351 && p_in.mousey <= 454 && p_monTab[i+10][0] != 0)
            {
                place.x = p_in.mousex + testCurseur(p_in).x;
                place.y = p_in.mousey + testCurseur(p_in).y;
                SDL_BlitSurface(p_imageinterface[12], 0, p_ouColler, &place);
                int z=i+10;
                oss << p_monTab[i+10][1];
                result = "FORCE";
                SDL_FreeSurface(p_imageinterface[7]);
                p_imageinterface[7] = TTF_RenderText_Blended(p_police[0], result.c_str(), {220,30,30});;
                place = {p_in.mousex +12, p_in.mousey +8};
                place.x += testCurseur(p_in).x;
                place.y += testCurseur(p_in).y;
                SDL_BlitSurface(p_imageinterface[7], 0, p_ouColler, &place);
                result = oss.str();
                SDL_FreeSurface(p_imageinterface[6]);
                p_imageinterface[6] = TTF_RenderText_Blended(p_police[1], result.c_str(), {240,50,50});;
                place = {p_in.mousex +12, p_in.mousey +4 +p_imageinterface[7]->h};
                place.x += testCurseur(p_in).x;
                place.y += testCurseur(p_in).y;
                SDL_BlitSurface(p_imageinterface[6], 0, p_ouColler, &place);

                result = afficherEffet(z,p_monTab);
                SDL_FreeSurface(p_imageinterface[7]);
                p_imageinterface[7] = TTF_RenderText_Blended(p_police[1], result.c_str(), {120,80,180});;
                place = {p_in.mousex +12, p_in.mousey +15 + 2*(p_imageinterface[6]->h)};
                place.x += testCurseur(p_in).x;
                place.y += testCurseur(p_in).y;
                SDL_BlitSurface(p_imageinterface[7], 0, p_ouColler, &place);

                test = true;
            }

            if(p_in.mousey >= 524 && p_in.mousey <= 627 && p_monTab[i][0] != 0)
            {
                place.x = p_in.mousex + testCurseur(p_in).x;
                place.y = p_in.mousey + testCurseur(p_in).y;
                SDL_BlitSurface(p_imageinterface[12], 0, p_ouColler, &place);
                int z=i;
                oss << p_monTab[i][1];
                result = "FORCE";
                SDL_FreeSurface(p_imageinterface[7]);
                p_imageinterface[7] = TTF_RenderText_Blended(p_police[0], result.c_str(), {220,30,30});;
                place = {p_in.mousex +12, p_in.mousey +8};
                place.x += testCurseur(p_in).x;
                place.y += testCurseur(p_in).y;
                SDL_BlitSurface(p_imageinterface[7], 0, p_ouColler, &place);
                result = oss.str();
                SDL_FreeSurface(p_imageinterface[6]);
                p_imageinterface[6] = TTF_RenderText_Blended(p_police[1], result.c_str(), {240,50,50});;
                place = {p_in.mousex +12, p_in.mousey +4 +p_imageinterface[7]->h};
                place.x += testCurseur(p_in).x;
                place.y += testCurseur(p_in).y;
                SDL_BlitSurface(p_imageinterface[6], 0, p_ouColler, &place);

                result = afficherEffet(z,p_monTab);
                SDL_FreeSurface(p_imageinterface[7]);
                p_imageinterface[7] = TTF_RenderText_Blended(p_police[1], result.c_str(), {120,80,180});;
                place = {p_in.mousex +12, p_in.mousey +15 + 2*(p_imageinterface[6]->h)};
                place.x += testCurseur(p_in).x;
                place.y += testCurseur(p_in).y;
                SDL_BlitSurface(p_imageinterface[7], 0, p_ouColler, &place);

                test = true;
            }
        }

        i++;
        if(i>4){test=true;}
    }
}

SDL_Rect testCurseur(Input p_in)
{
    SDL_Rect res = {0,0,0,0};
    if(p_in.mousex > 640 - 185 ){res.x = 640-185-p_in.mousex;}
    if(p_in.mousey > 640 - 107 ){res.y = 640-107-p_in.mousey;}
    return res;
}

int testCurseur2(Input p_in)
{
    int res = 0;
    if(p_in.mousex >= 32 && p_in.mousex < 288)
    {
        if(p_in.mousey >= 160 && p_in.mousey < 288)
        {
            res = 1;
        }
        if(p_in.mousey >= 335 && p_in.mousey < 463)
        {
            res = 3;
        }
    }
    if(p_in.mousex >= 352 && p_in.mousex < 608)
    {
        if(p_in.mousey >= 160 && p_in.mousey < 288)
        {
            res = 2;
        }
        if(p_in.mousey >= 335 && p_in.mousey < 463)
        {
            res = 4;
        }
    }
    return res;
}

void afficherCliquerGlisser(int ** p_monTab, bool p_test[5], SDL_Surface * p_monTabImage[NOMBRE_CARTE+1], Input p_in, SDL_Surface * p_ouColler)
{
    int i = 0;
    SDL_Rect place = {0,0,0,0};
    while(!p_test[i] && i<5){i++;}
    if(i<5)
    {
        place ={(p_in.mousex - p_monTabImage[p_monTab[i][0]]->w /2), (p_in.mousey - p_monTabImage[p_monTab[i][0]]->h /2)};
        SDL_BlitSurface(p_monTabImage[p_monTab[i][0]],0, p_ouColler, &place);
    }
}

string afficherEffet(int p_z, int ** p_monTab)
{
    if(p_monTab[p_z][4] == 0){return "Va mourir !";}
    if(p_monTab[p_z][4] == 1){return "Aucun effet";}
    if(p_monTab[p_z][4] == 2){return "Gagne une vie";}
    if(p_monTab[p_z][4] == 3){return "Gagne 500pts";}
    if(p_monTab[p_z][4] == 4){return "Va mourir si aucun BEBE !";}
    if(p_monTab[p_z][4] == 5){return "Gagne 500pts par tour";}
    if(p_monTab[p_z][4] == 6){return "Gagne 500pts";}
    if(p_monTab[p_z][4] == 7){return "Gagne 500pts par tour";}
    if(p_monTab[p_z][4] == 8){return "Gagne 500pts par HUMANON";}
    if(p_monTab[p_z][4] == 9){return "Elimine tout le monde";}
    if(p_monTab[p_z][4] == 10){return "Evolue en BENOIT au second tour";}
    if(p_monTab[p_z][4] == 11){return "Evolue en BENOIT au second tour";}
    else{return "Aucun effet";}
}

int afficherMenu(Input p_in, SDL_Surface *p_screen, SDL_Surface *p_imageMenu[NB_IMAGE_MENU])
{
    int souris = testCurseur2(p_in);
    int res = -1;
    SDL_BlitSurface(p_imageMenu[souris], 0, p_screen, 0);
    if(p_in.key[SDLK_RETURN] || (souris==1 && p_in.mousebuttons[SDL_BUTTON_LEFT])){res = 1;}
    //if(p_in.key[SDLK_KP0]){res = 0;}
    if(p_in.key[SDLK_KP1]){res = 1;}
    if(p_in.key[SDLK_KP2] || (souris==2 && p_in.mousebuttons[SDL_BUTTON_LEFT])){res = 2;}
    if(p_in.key[SDLK_KP3] || (souris==3 && p_in.mousebuttons[SDL_BUTTON_LEFT])){res = 3;}
    if(p_in.key[SDLK_KP4] || (souris==4 && p_in.mousebuttons[SDL_BUTTON_LEFT])){res = 4;}
    /*if(p_in.key[SDLK_KP5]){res = 5;}
    if(p_in.key[SDLK_KP6]){res = 6;}
    if(p_in.key[SDLK_KP7]){res = 7;}
    if(p_in.key[SDLK_KP8]){res = 8;}
    if(p_in.key[SDLK_KP9]){res = 9;}*/
    return res;
}



