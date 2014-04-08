
#if!defined(AFX_MAIN_H)
#define AFX_MAIN_H

	#include <stdio.h>
	#include <windows.h>
	#include <vfw.h>

	#include <SDL.h>
	#include <SDL_syswm.h>
	#include <SDL_thread.h>

	#include "SDL_pixel.h"
	#include "WebCam.h"

	LRESULT CALLBACK	Main_CallBack(HWND hWnd, LPVIDEOHDR lpVHdr );

	void				Draw_Screen();
	int					thread_func_webcam(void *unused);

#endif
