// WebCam.cpp: implementation of the WebCam class.
//
//////////////////////////////////////////////////////////////////////

#include "WebCam.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

WebCam::WebCam()
{
	//Créé une surface sur laquel on va pouvoir mettre l'image charger depuis la cam
	image = SDL_CreateRGBSurface(SDL_SWSURFACE, 640, 480, 32, 0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);
	if ( image == NULL ) {					fprintf(stderr, "Impossible de creer la surface de la classe WebCam: %s\n", SDL_GetError());
    }
}


WebCam::~WebCam()
{

}

bool WebCam::Connect()
{
	//Récupère le Hwnd et le HDC de la fenètre SDL
	SDL_SysWMinfo wmInfo;
	SDL_VERSION(&wmInfo.version);
	SDL_GetWMInfo(&wmInfo);
	WebCam::hWnd = wmInfo.window;
	WebCam::hDC = GetDC(WebCam::hWnd);

	//Connection a la webcam
	hWnd_WC = capCreateCaptureWindow("WebCam", WS_CHILD, 0, 0, 1, 1, hWnd, 0);

	//Vérifie la connection
	if(!capDriverConnect(hWnd_WC, 0))
	{
		MessageBox(NULL, "Erreur lors de l'initialisation de la WebCam.\nReportez-vous à l'aide pour plus d'information.", "Erreur", MB_ICONERROR);
		return FALSE;
	}

	//trouve le HDC associé a la cam
	hDC_WC = GetDC(hWnd_WC);
	return TRUE;
}

void WebCam::StopConnect()
{
	//Déconnect
	capDriverDisconnect(hWnd_WC);
}

void WebCam::GetImage_Init()
{
	BITMAPINFO bmpinfo;

//	capDlgVideoDisplay( hWnd_WC );
//	capDlgVideoFormat ( hWnd_WC );
//	capDlgVideoSource ( hWnd_WC );

	//Modifie les infos de la cam, et initialise la cam pour récuperer des image 320*240
	capGetVideoFormat(hWnd_WC, &bmpinfo, sizeof(BITMAPINFO));

	bmpinfo.bmiHeader.biSize	= sizeof(BITMAPINFOHEADER);
	bmpinfo.bmiHeader.biWidth	= 640;
	bmpinfo.bmiHeader.biHeight	= 480;
	if(!capSetVideoFormat(hWnd_WC, &bmpinfo, sizeof(BITMAPINFO)))
	{
		printf("erreur durant le setvideoformat\n");
	}

	//Définni la fonction de Callback en cas de nouvelle image
	capSetCallbackOnFrame(hWnd_WC, Main_CallBack);
}

void WebCam::GetImage()
{
	//Charge une image
	capCaptureSingleFrameOpen(hWnd_WC);
	capCaptureSingleFrame(hWnd_WC);
	capCaptureSingleFrameClose(hWnd_WC);
}

void WebCam::CallBack(HWND hWnd, LPVIDEOHDR lpVHdr)
{
	//Copie le buffer de la cam ds une surface SDL
	SDL_LockSurface(WebCam::image);
	for(unsigned int i=0;i<lpVHdr->dwBufferLength/3;i++)
	{
		putpixel(WebCam::image,  319-i%320,	239-i/320,	SDL_MapRGB(WebCam::image->format, lpVHdr->lpData[i*3]+2, lpVHdr->lpData[i*3+1] , lpVHdr->lpData[i*3]));
	}
	SDL_UnlockSurface(WebCam::image);
}
