/*
    Trace
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

#ifndef SCREEN_H
#define SCREEN_H

#include <SDL.h>
#include <windows.h>
#include <vector>

#include <Coordonnees.h>
#include <Image.h>
#include <Camera.h>
#include <Object.h>


#define CX_SCREEN           GetSystemMetrics(SM_CXSCREEN)            ///Largeur
#define CY_SCREEN           GetSystemMetrics(SM_CYSCREEN)            ///Hauteur
#define LARGEUR_ECRAN       CX_SCREEN
#define HAUTEUR_ECRAN       size_of_window(CY_SCREEN)
#define RESIZE              (Sint16)(SDL_GetVideoSurface()->h/1080.0)



class Screen
{
    friend class Image;

    public:
        Screen();
        Screen(int w, int h);
        virtual ~Screen();

        void resize();   /// change la taille de l'écran
        void resize(int width, int height);
        void fullScreen();  /// mode plein écran
        void windowed();    /// mode fenêtré


        void display();     /// pour afficher à l'écran
        Image * buffer();    /// ce qui sera afficher
        void setBuffer(Image * img);
        Image * getBuffer(){return videoBuffer;}
        void setClearing(bool a){clearing = a;} /// active le nettoyage

    protected:
        SDL_Surface * ecran;
        Image * videoBuffer;
        bool clearing;

    private:
        static int size_of_window(int);
};

#endif // SCREEN_H
