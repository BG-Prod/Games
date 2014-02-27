#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <windows.h>

#include "Map.h"

using namespace std;

Map::Map(SDL_Surface ** p_images)
{
    string lien = cheminImage + "Espace.png";
    m_fond = p_images[1];
    m_fondBase = p_images[2];
    m_menu = p_images[3];

    for(int i = 0 ; i < 15 ; i++)
    {
        m_planete[i] = p_images[i+7];
    }
    m_planete[15] = NULL;

    FMOD_System_Create(&m_system);
    FMOD_System_Init(m_system, 2, FMOD_INIT_NORMAL, NULL);

    lien = cheminSon + "Atlantis_Wakes_GE.mp3";
    FMOD_System_CreateSound(m_system, lien.c_str(), FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM |FMOD_LOOP_NORMAL, 0, &m_musique);
    FMOD_Sound_SetLoopCount(m_musique, -1);

    m_uniPremiereMap = new Univers();

    m_position.x = 0;
    m_position.y = 0;
    m_position.w = 1280;
    m_position.h = 1024;

    m_placeFond.x = -1280;
    m_placeFond.y = -1024;

    m_sysPlanete.x = LARGEUR_MAP/2;
    m_sysPlanete.y = HAUTEUR_MAP/2;

    for(int i = 0; i <20; i++)
    {
        m_cartonAVaisseaux[i] = NULL;
    }

    for(int i = 0; i <20; i++)
    {
        m_cartonDegat[i] = 0;
    }

    for(int i = 0; i <20; i++)
    {
        for(int j = 0; j <2; j++)
        {
            m_cartonInfo[i][j] = 100;
        }
    }

    for(int i = 0; i < ((LARGEUR_MAP / 40) +1); i++)
    {
        for(int j = 0; j < ((HAUTEUR_MAP / 40) +1); j++)
        {
            m_carte[i][j] = 0;
            m_spawnPoint[i][j] = 0;
        }
    }

}

Map::Map(const Map &p_mapACopier)
{

}

Map::~Map()
{
    FMOD_Sound_Release(m_musique);
    delete m_uniPremiereMap;

    FMOD_System_Close(m_system);
    FMOD_System_Release(m_system);
}

int Map::charger()
{
    FILE* fichier = NULL;
    char ligneFichier[LARGEUR_MAP * HAUTEUR_MAP + 1] = {0};
    int i = 0, j = 0;

    fichier = fopen("ressources/map/niveaux.lvl", "r");
    if (fichier == NULL)
        return 0;

    fgets(ligneFichier, LARGEUR_MAP * HAUTEUR_MAP + 1, fichier);

    for (i = 0 ; i < LARGEUR_MAP ; i++)
    {
        switch (ligneFichier[i])
            {
                case '0':
                    m_carte[i][j] = 0;
                    break;
                case '1':
                    m_carte[i][j] = 0;
                    break;
                case '2':
                    m_carte[i][j] = 0;
                    break;
                case '3':
                    m_carte[i][j] = 0;
                    break;
                case '4':
                    m_carte[i][j] = 0;
                    break;
                default:
                    break;
            }
    }

    fclose(fichier);
    return 1;
}

void Map::playMap(SDL_Surface *p_ecran, Input p_in, SDL_Surface ** p_images)
{
    //this->charger();

    m_cartonAVaisseaux[0] = new BC304(p_images);
    SDL_Rect depart = {800, 600};
    m_cartonAVaisseaux[1] = new Hatak(depart);
    majCoor();
    int tempsPrecedent = 0, tempsActuel = 0;
    int i = 0;

    updateEvents(&p_in);

    //FMOD_System_PlaySound(m_system, FMOD_CHANNEL_FREE, m_musique, 0, NULL);

    while(!p_in.key[SDLK_ESCAPE] && !p_in.quit)
    {
        updateEvents(&p_in);

        tempsActuel = SDL_GetTicks();

        if(tempsActuel - tempsPrecedent >= 40)
        {
            tempsPrecedent = tempsActuel;
        }
        else if (tempsActuel - tempsPrecedent < 40)
        {
            SDL_Delay(tempsActuel - tempsPrecedent);
            tempsPrecedent = tempsActuel;
        }

        SDL_Rect rect;
        if(m_cartonAVaisseaux[0] != NULL)
        {rect = m_cartonAVaisseaux[0]->getPos();}
        m_position.x = rect.x - LARGEUR_ECRAN / 2 + rect.w / 2;
        m_position.y = rect.y - HAUTEUR_ECRAN / 2 + rect.w / 2;
        if(m_position.x <= 0)
        {m_position.x = 0;}
        if(m_position.y <= 0)
        {m_position.y = 0;}
        if(m_position.x >= LARGEUR_MAP - LARGEUR_ECRAN)
        {m_position.x = LARGEUR_MAP - LARGEUR_ECRAN;}
        if(m_position.y >= HAUTEUR_MAP - HAUTEUR_ECRAN)
        {m_position.y = HAUTEUR_MAP - HAUTEUR_ECRAN;}


        SDL_BlitSurface(m_fondBase, &m_position, p_ecran, NULL);
        SDL_BlitSurface(m_fond, NULL, m_fondBase, NULL);

        ///if(m_planete[i] == NULL){i = 0;}SDL_BlitSurface(m_planete[i], NULL, m_fondBase, &m_sysPlanete);i++;
        majCoor();
        m_ent.gerer(m_cartonAVaisseaux, m_fondBase, p_ecran, p_in,m_coorObjet,m_cartonDegat,m_uniPremiereMap,m_cartonInfo);
        rebootCartonDegat();
        majCoor();
        SDL_Flip(p_ecran);
    }

    p_in.key[SDLK_RETURN] = 0;
    p_in.key[SDLK_ESCAPE] = 0;
}


void Map::majCoor()
{
    if(m_cartonAVaisseaux[0] != NULL)
    {
        m_coorObjet[0] = m_cartonAVaisseaux[0]->getPosition();
    }
    else
        {m_coorObjet[0] = {-1000,-1000,0,0};}

    if(m_cartonAVaisseaux[1] != NULL)
    {
        m_coorObjet[1] = m_cartonAVaisseaux[1]->getPosition();
    }
    else
        {m_coorObjet[1] = {-1000,-1000,0,0};}
}

void Map::majCartonDegat(int p_i, int p_mod)
{
    m_cartonDegat[p_i] = m_cartonDegat[p_i] + p_mod;
}

int Map::getCartonDegat(int p_i)
{
    return m_cartonDegat[p_i];
}

void Map::rebootCartonDegat()
{
    for(int i = 0; i <20; i++)
    {
        m_cartonDegat[i] = 0;
    }
}
