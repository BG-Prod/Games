#include "main.h"

SDL_Surface *screen;
SDL_Surface *webcam_surf;
SDL_Surface *modif_surf;
SDL_Thread  *thread_webcam;
SDL_Event	 event;

WebCam		*Cam = NULL;
bool		 run = true;

int thread_func_webcam(void *unused)								//Processus de la gestion de la webcam
{
																	//Création de la surface dans laquel sera copié l'image de la webcam
	webcam_surf = SDL_CreateRGBSurface(SDL_HWSURFACE, 320, 240, 32, 0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);
	if ( webcam_surf == NULL ) {					fprintf(stderr, "Impossible de creer la surface webcam_surf: %s\n", SDL_GetError());
    }
																	//Efface webcam_surf
	SDL_FillRect(webcam_surf,NULL,SDL_MapRGB(webcam_surf->format, 0, 0 , 0));

	Cam = new WebCam;												//Création de l'objet Webcam cam
	Cam->Connect();													//Initialisation de la webcam
	Cam->GetImage_Init();
	while(run){														//Boucle infinie
		Cam->GetImage();											//Charge une nouvelle image ds la webcam, et copie l'image sur la surface webcam_surf
		SDL_BlitSurface(Cam->image, NULL, webcam_surf, NULL);
	}
	Cam->StopConnect();												//Déconnexion de la webcam
    return(0);
}

																	//Processus principal
int main(int argc, char *argv[])
{
																	//Initialisation de SDL
	if ( SDL_Init(SDL_INIT_VIDEO) < 0 ) {	fprintf(stderr, "Impossible d'initialiser SDL: %s\n", SDL_GetError());
		return 0;
	}

																	//Initialisation de l'écran
	screen = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE  | SDL_DOUBLEBUF /*| SDL_FULLSCREEN*/);
    if ( screen == NULL ) {					fprintf(stderr, "Impossible de creer la surface screen: %s\n", SDL_GetError());
		SDL_Quit();
        return 0;
    }


    thread_webcam = SDL_CreateThread(thread_func_webcam, NULL);		//Creation du processus de la webcam
    if ( thread_webcam == NULL ) {
        fprintf(stderr, "Impossible de creer le processus de la webcam: %s\n", SDL_GetError());
        return 0;
    }


	while(run)														//Boucle Infinie
	{
		while(SDL_PollEvent(&event))								//Gestion des Events
		{
			switch (event.type)
			{
				case SDL_QUIT:
					run = false;
					break;
				case SDL_KEYDOWN:
					switch(event.key.keysym.sym)
					{
						 case SDLK_ESCAPE:
							run = false;
							break;
					}
					break;
			}
		}

		Draw_Screen();												//Dessine l'écran
	}
	SDL_WaitThread(thread_webcam, NULL);							//Attend que le processus de la webcam ce soit terminer
	SDL_Quit();
	return 0;
}


LRESULT CALLBACK Main_CallBack(HWND hWnd, LPVIDEOHDR lpVHdr )		//Fonction de Callback de la webcam (si une nouvelle image a été chargé)
{
	Cam->CallBack(hWnd,lpVHdr);										//Appel la fonction callback de cam
	return 0;
}

//Dessine l'écran
void Draw_Screen()
{
	SDL_FillRect(screen,NULL,SDL_MapRGB(screen->format, 0, 0 , 0));	//Efface l'écran
	SDL_BlitSurface(webcam_surf, NULL, screen, NULL);				//Copie l'image webcam sur l'écran
	SDL_Flip(screen);												//Flip
}



