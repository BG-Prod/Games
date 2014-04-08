/// WebCam.h: interface for the WebCam class.
///
///////////////////////////////////////////////////////////////////////

#if !defined(AFX_WEBCAM_H)
#define AFX_WEBCAM_H

	#include <stdio.h>
	#include <windows.h>
	#include <vfw.h>

	#include <SDL.h>

	#include "main.h"

	class WebCam
	{
        public:
            WebCam();
            virtual ~WebCam();

            bool Connect();
            void StopConnect();
            void GetImage();
            void GetImage_Init();
            void CallBack(HWND hWnd, LPVIDEOHDR lpVHdr);

            HWND	hWnd;
            HWND	hWnd_WC;
            HDC		hDC;
            HDC		hDC_WC;

            SDL_Surface *image;
	};

#endif
