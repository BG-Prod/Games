#include "Utile.h"
#include "Monde.h"

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

    for(int i = 0 ; i < 1 ; i++)
    {
        itoa(i,a,8);
        lien = cheminImage + "image0" + a + ".png";
        p_images[i] = SDL_DisplayFormat(IMG_Load(lien.c_str()));
    }

    lien = cheminImage + "Espace.png";
    p_images[1] = SDL_DisplayFormat(IMG_Load(lien.c_str()));

    p_images[2] = SDL_CreateRGBSurface(SDL_HWSURFACE, LARGEUR_MAP, HAUTEUR_MAP, 32, 0, 0, 0, 0);

    lien = cheminImage + "interface169.png";
    p_images[3] = SDL_DisplayFormat(IMG_Load(lien.c_str()));
    SDL_SetColorKey(p_images[3], SDL_SRCCOLORKEY, SDL_MapRGB(p_images[3]->format, 0, 183, 239));

    lien = cheminImage + "blason.png";
    p_images[4] = SDL_DisplayFormat(IMG_Load(lien.c_str()));
    SDL_SetColorKey(p_images[4], SDL_SRCCOLORKEY, SDL_MapRGB(p_images[4]->format, 255, 255, 255));

    lien = cheminImage + "blason.png";
    p_images[5] = SDL_DisplayFormat(IMG_Load(lien.c_str()));
    SDL_SetColorKey(p_images[5], SDL_SRCCOLORKEY, SDL_MapRGB(p_images[5]->format, 255, 255, 255));

    lien = cheminImage + "blason.png";
    p_images[6] = SDL_DisplayFormat(IMG_Load(lien.c_str()));
    SDL_SetColorKey(p_images[6], SDL_SRCCOLORKEY, SDL_MapRGB(p_images[6]->format, 255, 255, 255));

    for(int i = 0+7 ; i < 15+7 ; i++)
    {
        char a[1];
        itoa(i-7,a,10);
        string zero;
        if(i-7<10){zero = '0';}   else{zero="";}
        lien = cheminImage + "Mordak/P" + zero.c_str() + a + ".png";
        p_images[i] = SDL_DisplayFormat(IMG_Load(lien.c_str()));
        SDL_SetColorKey(p_images[i], SDL_SRCCOLORKEY, SDL_MapRGB(p_images[i]->format, 111, 49, 152));
    }

    lien = cheminImage + "BC-304H.bmp";
    p_images[22] = SDL_DisplayFormat(IMG_Load(lien.c_str()));
    SDL_SetColorKey(p_images[22], SDL_SRCCOLORKEY, SDL_MapRGB(p_images[22]->format, 192, 192, 192));

    lien = cheminImage + "BC-304B.bmp";
    p_images[23] = SDL_DisplayFormat(IMG_Load(lien.c_str()));
    SDL_SetColorKey(p_images[23], SDL_SRCCOLORKEY, SDL_MapRGB(p_images[23]->format, 192, 192, 192));

    lien = cheminImage + "BC-304G.bmp";
    p_images[24] = SDL_DisplayFormat(IMG_Load(lien.c_str()));
    SDL_SetColorKey(p_images[24], SDL_SRCCOLORKEY, SDL_MapRGB(p_images[24]->format, 192, 192, 192));

    lien = cheminImage + "BC-304D.bmp";
    p_images[25] = SDL_DisplayFormat(IMG_Load(lien.c_str()));
    SDL_SetColorKey(p_images[25], SDL_SRCCOLORKEY, SDL_MapRGB(p_images[25]->format, 192, 192, 192));

    lien = cheminImage + "BC-304HD.png";
    p_images[26] = SDL_DisplayFormat(IMG_Load(lien.c_str()));
    SDL_SetColorKey(p_images[26], SDL_SRCCOLORKEY, SDL_MapRGB(p_images[26]->format, 192, 192, 192));

    lien = cheminImage + "BC-304HG.png";
    p_images[27] = SDL_DisplayFormat(IMG_Load(lien.c_str()));
    SDL_SetColorKey(p_images[27], SDL_SRCCOLORKEY, SDL_MapRGB(p_images[27]->format, 192, 192, 192));

    lien = cheminImage + "BC-304BG.png";
    p_images[28] = SDL_DisplayFormat(IMG_Load(lien.c_str()));
    SDL_SetColorKey(p_images[28], SDL_SRCCOLORKEY, SDL_MapRGB(p_images[28]->format, 192, 192, 192));

    lien = cheminImage + "BC-304BD.png";
    p_images[29] = SDL_DisplayFormat(IMG_Load(lien.c_str()));
    SDL_SetColorKey(p_images[29], SDL_SRCCOLORKEY, SDL_MapRGB(p_images[29]->format, 192, 192, 192));

    lien = cheminImage + "boom.bmp";
    p_images[30] = SDL_DisplayFormat(IMG_Load(lien.c_str()));
    SDL_SetColorKey(p_images[30], SDL_SRCCOLORKEY, SDL_MapRGB(p_images[30]->format, 192, 192, 192));

    lien = cheminImage + "batterie.bmp";
    p_images[31] = SDL_DisplayFormat(IMG_Load(lien.c_str()));
    SDL_SetColorKey(p_images[31], SDL_SRCCOLORKEY, SDL_MapRGB(p_images[31]->format, 0, 183, 239));
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

void jeu(SDL_Surface ** p_images)
{
    bool done = false;
    int tempsPrecedent = 0, tempsActuel = 0;
    int * menu = new int;
    Input in;
    SDL_Event event;
    TTF_Font * police = NULL;
    Monde * espace = NULL;
    SDL_Rect position;
    string lien;

    memset(&in,0,sizeof(in));

    *menu = -1;
    lien = cheminPolice + "tunga.ttf";
    police = TTF_OpenFont(lien.c_str(), 20);
    SDL_Color couleur = {255, 255, 255};
    SDL_Surface *texte = TTF_RenderText_Blended(police, "PRESSEZ ENTRER POUR COMMENCER UNE NOUVELLE PARTIE", couleur);
    lien = cheminImage + "The Arvernes.jpg";
    SDL_Surface* arvernes = IMG_Load(lien.c_str());
    SDL_Rect coorTxt = {SDL_GetVideoSurface()->w / 2 - texte->w / 2, SDL_GetVideoSurface()->h - texte->h -200};
    SDL_Rect coorArv = {SDL_GetVideoSurface()->w / 2 - arvernes->w / 2, SDL_GetVideoSurface()->h /2 - arvernes->h /2};

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

        SDL_Flip(SDL_GetVideoSurface());
    }

    in.key[SDLK_RETURN] = 0;
    in.mousebuttons[SDL_BUTTON_LEFT] = 0;

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





        if(*menu == 1 or in.key[SDLK_1] or in.key[SDLK_RETURN] or in.key[SDLK_KP1]) // jouer
        {
            SDL_FillRect(SDL_GetVideoSurface(), 0, SDL_MapRGB(SDL_GetVideoSurface()->format, 0, 0, 0));
            SDL_Flip(SDL_GetVideoSurface());
            espace = new Monde(p_images);
            espace->playMonde(SDL_GetVideoSurface(), &in, p_images);
            delete espace;
            in.mousebuttons[SDLK_RETURN] = SDL_RELEASED;
            *menu = -1;
        }

        if(*menu == 2) // editeur
        {
            *menu = -1;
        }

        if(*menu == 3) // classement
        {
            *menu = -1;
        }

        if(*menu == 4) // quitter le jeu
        {
            in.quit = 1;
        }

        if(*menu == -1)
        {
            *menu = -1;
        }

        SDL_FillRect(SDL_GetVideoSurface(), 0, SDL_MapRGB(SDL_GetVideoSurface()->format, 0, 0, 0));

        SDL_BlitSurface(arvernes, 0, SDL_GetVideoSurface(), &coorArv);

        SDL_BlitSurface(texte, 0, SDL_GetVideoSurface(), &coorTxt);

        SDL_Flip(SDL_GetVideoSurface());

    }   /// end main loop

    TTF_CloseFont(police);
    SDL_FreeSurface(texte);
    SDL_FreeSurface(arvernes);
    delete menu;
}


void animation(SDL_Surface ** p_animation, SDL_Rect p_position, SDL_Surface* p_ouColler, int i)
{
    if(p_animation[i] == NULL)
    {
        i = 0;
    }

    SDL_BlitSurface(p_animation[i], NULL, p_ouColler, &p_position);
    i++;
    SDL_BlitSurface(p_animation[i], NULL, p_ouColler, &p_position);
}

bool collision( SDL_Rect A, SDL_Rect B )
{
//Les cotes des rectangles
int leftA, leftB;
int rightA, rightB;
int topA, topB;
int bottomA, bottomB;
//Calcul les cotes du rectangle A
leftA = A.x;
rightA = A.x + A.w;
topA = A.y;
bottomA = A.y + A.h;
//Calcul les cotes du rectangle B
leftB = B.x;
rightB = B.x + B.w;
topB = B.y;
bottomB = B.y + B.h;

//Tests de collision
if( bottomA <= topB )
{
return false;
}
if( topA >= bottomB )
{
return false;
}
if( rightA <= leftB )
{
return false;
}
if( leftA >= rightB )
{
return false;
}
//Si conditions collision detectee
return true;
}

BarreVie::BarreVie()
{
  m_vie = 100;
  m_barreInfo.x = 16;
  m_barreInfo.y = 24;
  m_barreInfo.w = 408;
  m_barreInfo.h = 32;
  m_tailleCadre.w = 4;
  m_tailleCadre.h = 4;

  m_barreCadre = SDL_CreateRGBSurface(SDL_HWSURFACE, m_barreInfo.w + 2*m_tailleCadre.h, m_barreInfo.h + 2*m_tailleCadre.h, 32, 0, 0, 0, 0);
  SDL_FillRect(m_barreCadre, NULL, SDL_MapRGB(m_barreCadre->format, 60, 60, 60));

  m_barreJauge = SDL_CreateRGBSurface(SDL_HWSURFACE, m_barreInfo.w, m_barreInfo.h, 32, 0, 0, 0, 0);
  SDL_FillRect(m_barreJauge, NULL, SDL_MapRGB(m_barreJauge->format, 200, 0, 0));
}

BarreVie::~BarreVie()
{
  SDL_FreeSurface(m_barreCadre);

  SDL_FreeSurface(m_barreJauge);
}

void BarreVie::setPosition(SDL_Rect p_position)
{
  m_barreInfo.x = p_position.x;
  m_barreInfo.y = p_position.y;
}

void BarreVie::actualiserEtat(int p_vie)
{
  m_vie = p_vie;
  SDL_FreeSurface(m_barreJauge);
  m_barreJauge = SDL_CreateRGBSurface(SDL_HWSURFACE, m_vie / 100 * m_barreInfo.w, m_barreInfo.h, 32, 0, 0, 0, 0);
  SDL_FillRect(m_barreJauge, NULL, SDL_MapRGB(m_barreJauge->format, 200, 0, 0));
}

void BarreVie::afficher(SDL_Surface *p_ecran)
{
  if(m_estVisible)
    {
      SDL_Rect temp;
      temp.x = m_barreInfo.x - m_tailleCadre.w;
      temp.y = m_barreInfo.y - m_tailleCadre.h;
      SDL_BlitSurface(m_barreCadre, NULL, p_ecran, &temp);
      SDL_BlitSurface(m_barreJauge, NULL, p_ecran, &m_barreInfo);
    }
}

