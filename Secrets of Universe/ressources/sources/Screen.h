#ifndef SCREEN_H
#define SCREEN_H

#include <SDL.h>
#include <windows.h>
#include <windows.h>

#include <Coordonnees.h>
#include <Image.h>
#include <Camera.h>


#define CX_SCREEN           GetSystemMetrics(SM_CXSCREEN)            ///Largeur
#define CY_SCREEN           GetSystemMetrics(SM_CYSCREEN)            ///Hauteur
#define LARGEUR_ECRAN       CX_SCREEN
#define HAUTEUR_ECRAN       size_of_window(CY_SCREEN)
#define RESIZE              SDL_GetVideoSurface()->h/1080.0



class Screen
{
    friend class Image;

    public:
        Screen();
        virtual ~Screen();

        void resize();   /// change la taille de l'écran
        void fullScreen();  /// mode plein écran
        void windowed();    /// mmode fenêtré

        void display();

    protected:
        SDL_Surface * ecran;
        Image * videoBuffer;

    private:
        static int size_of_window(int);
};

#endif // SCREEN_H
