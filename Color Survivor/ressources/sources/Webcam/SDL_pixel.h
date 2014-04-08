
#if !defined(AFX_SDL_PIXEL_H)
#define AFX_SDL_PIXEL_H

	#include <SDL.h>

	void	putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel);
	Uint32  getpixel(SDL_Surface *surface, int x, int y);

#endif

