#ifndef WEBCAM_H
#define WEBCAM_H

#define WM_CAP_START  0x0400
#define WM_CAP_DRIVER_CONNECT  (WM_CAP_START + 10)
#define WM_CAP_DRIVER_DISCONNECT  (WM_CAP_START + 11)
#define WM_CAP_EDIT_COPY (WM_CAP_START + 30)
#define WM_CAP_GRAB_FRAME (WM_CAP_START + 60)
#define WM_CAP_SET_SCALE (WM_CAP_START + 53)
#define WM_CAP_SET_PREVIEWRATE (WM_CAP_START + 52)
#define WM_CAP_SET_PREVIEW (WM_CAP_START + 50)
#define WM_CAP_DLG_VIDEOSOURCE  (WM_CAP_START + 42)
#define WM_CAP_STOP (WM_CAP_START+ 68)

#include <windows.h>
#include <vfw.h>

LRESULT CALLBACK WindowProc (HWND, UINT, WPARAM, LPARAM);
PBITMAPINFO CreateBitmapInfoStruct(HWND hwnd, HBITMAP hBmp);
void CreateBMPFile(HWND hwnd, LPTSTR pszFile, PBITMAPINFO pbi, HBITMAP hBMP, HDC hDC);

char szAppName [] = TEXT("WebCam");
HWND camhwnd;
HDC hdc ;
HDC hdcMem;
PAINTSTRUCT ps;
HBITMAP hbm;
RECT rc;


class Webcam
{
    public:
        Webcam();
        virtual ~Webcam();

    protected:
};

#endif // WEBCAM_H
