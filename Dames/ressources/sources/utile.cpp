#include "utile.h"

using namespace std;


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


void initialisation(FMOD_SYSTEM * p_system)
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
    FMOD_System_Init(p_system, 32, FMOD_INIT_NORMAL, NULL);
}

void fermeture(FMOD_SYSTEM * p_system)
{
    /// fermeture propre de fmodex
    FMOD_System_Close(p_system);
    FMOD_System_Release(p_system);
}


void load_images(SDL_Surface ** p_images)
{
    string lien;
    char a[1];
    for(int i = 0 ; i < NOMBRE_IMAGE ; i++)
    {
        itoa(i,a,8);
        lien = cheminImage + "image0" + a + ".png";
        p_images[i] = SDL_DisplayFormat(IMG_Load(lien.c_str()));
        p_images[i] = rotozoomSurface(p_images[i],0.0,(double)(HAUTEUR_ECRAN/1080.0),1);
    }
}

void load_musiques(FMOD_SYSTEM * p_system, FMOD_SOUND ** p_musiques)
{
    string lien;

    for(int i = 0 ; i < NOMBRE_MUSIQUE ; i++)
    {
        lien = cheminSon + "son01.mid";
        FMOD_System_CreateSound(p_system, lien.c_str(), FMOD_CREATESAMPLE, 0, &p_musiques[i]);
    }
}

void load_polices(TTF_Font ** p_polices)
{
    string lien;

    for(int i = 0 ; i < NOMBRE_POLICE ; i++)
    {
        lien = cheminPolice + "calibri.ttf";
        p_polices[i] = TTF_OpenFont(lien.c_str(), 20);
    }
}


void free_images(SDL_Surface ** p_images)
{
    for(int i = 0 ; i < NOMBRE_IMAGE ; i++)
    {
        SDL_FreeSurface(p_images[i]);
    }
    free(p_images);
}

void free_musiques(FMOD_SOUND ** p_sons)
{
    for(int i = 0 ; i < NOMBRE_MUSIQUE ; i++)
    {
        FMOD_Sound_Release(p_sons[i]);
    }
    free(p_sons);
}

void free_polices(TTF_Font ** p_polices)
{
    for(int i = 0 ; i < NOMBRE_POLICE ; i++)
    {
        TTF_CloseFont(p_polices[i]);
    }
    free(p_polices);
}

int size_of_game(int p_hauteur_ecran)
{
    int taille = p_hauteur_ecran;
    if(taille == 768){taille = 760;}
    return taille;
}



