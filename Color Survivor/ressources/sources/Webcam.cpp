#include "Webcam.h"

using namespace std;

Webcam::Webcam()
{
    //ctor
}

Webcam::~Webcam()
{
    //dtor
}



//WinMain -- Main Window
int WINAPI WinMain ( HINSTANCE hInstance, HINSTANCE hPrevInstance,
                     LPSTR lpCmdLine, int nCmdShow )
{

    HWND hwnd;
    MSG msg;

    WNDCLASS wc;
    wc.style = CS_HREDRAW|CS_VREDRAW;
    wc.lpfnWndProc = WindowProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(GetModuleHandle(NULL), IDI_APPLICATION);
    wc.hCursor = LoadCursor (NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH) (COLOR_WINDOW+1);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = szAppName;

    RegisterClass (&wc);

// Create the window
    hwnd = CreateWindow (szAppName,szAppName,WS_OVERLAPPED|WS_CAPTION|WS_SYSMENU|WS_MINIMIZEBOX,CW_USEDEFAULT,CW_USEDEFAULT,640,480,0,0,hInstance,0);

    ShowWindow (hwnd,SW_SHOW);
    UpdateWindow (hwnd);

    while (GetMessage(&msg,0,0,0))
    {
        if (!IsDialogMessage(hwnd, &msg))
        {
            TranslateMessage (&msg);
            DispatchMessage (&msg);
        }
    }
    return msg.wParam;
}

//Main Window Procedure WindowProc
LRESULT CALLBACK WindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HINSTANCE hInstance = GetModuleHandle(NULL);

//some buttons
    HWND hButtStartCam;
    HWND hButtStopCam;
    HWND hButtGrabFrame;

    switch (message)                  /* handle the messages */
    {

    case WM_CTLCOLORSTATIC:
        SetBkMode(hdc,TRANSPARENT);
        return (LRESULT)CreateSolidBrush(0xFFFFFF);

    case WM_CREATE:
    {
        hButtStartCam = CreateWindowEx(0,"BUTTON","Start Camera",WS_CHILD | WS_VISIBLE,
                                       0,0,100,20,hwnd,(HMENU)1,hInstance, 0);
        hButtStopCam = CreateWindowEx(0,"BUTTON","Stop Camera",WS_CHILD | WS_VISIBLE,
                                      0,25,100,20,hwnd,(HMENU)2,hInstance, 0);
        hButtGrabFrame = CreateWindowEx(0,"BUTTON","Grab Frame",WS_CHILD | WS_VISIBLE,
                                        0,50,100,20,hwnd,(HMENU)3,hInstance, 0);

        camhwnd = capCreateCaptureWindow ("camera window", WS_CHILD , 0, 100, 300, 300, hwnd, 0);
        SendMessage(camhwnd,WM_CAP_DRIVER_CONNECT,0,0);
        SendMessage(camhwnd,WM_CAP_DLG_VIDEOSOURCE,0,0);

        break;
    }

    case WM_COMMAND:
    {
        switch (LOWORD(wParam))
        {

        case 1:
        {
            ShowWindow(camhwnd,SW_SHOW);
            SendMessage(camhwnd,WM_CAP_DRIVER_CONNECT,0,0);
            SendMessage(camhwnd, WM_CAP_SET_SCALE, true , 0);
            SendMessage(camhwnd, WM_CAP_SET_PREVIEWRATE, 66, 0);
            SendMessage(camhwnd, WM_CAP_SET_PREVIEW, true , 0);
            break;
        }

        case 2:
        {
            ShowWindow(camhwnd,SW_HIDE);
            SendMessage(camhwnd, WM_CAP_DRIVER_DISCONNECT, 0, 0);
            break;
        }

        case 3:
        {
//Grab a Frame
            SendMessage(camhwnd, WM_CAP_GRAB_FRAME, 0, 0);
//Copy the frame we have just grabbed to the clipboard
            SendMessage(camhwnd, WM_CAP_EDIT_COPY,0,0);

//Copy the clipboard image data to a HBITMAP object called hbm
            hdc = BeginPaint(camhwnd, &ps);
            hdcMem = CreateCompatibleDC(hdc);
            if (hdcMem != NULL)
            {
                if (OpenClipboard(camhwnd))
                {
                    hbm = (HBITMAP) GetClipboardData(CF_BITMAP);
                    SelectObject(hdcMem, hbm);
                    GetClientRect(camhwnd, &rc);
                    CloseClipboard();
                }
            }
//Save hbm to a .bmp file called Frame.bmp
            PBITMAPINFO pbi = CreateBitmapInfoStruct(hwnd, hbm);
            CreateBMPFile(hwnd, "Frame.bmp", pbi, hbm, hdcMem);

            SendMessage(camhwnd,WM_CAP_DRIVER_CONNECT,0,0);
            SendMessage(camhwnd, WM_CAP_SET_SCALE, true , 0);
            SendMessage(camhwnd, WM_CAP_SET_PREVIEWRATE, 66, 0);
            SendMessage(camhwnd, WM_CAP_SET_PREVIEW, true , 0);
            break;
        }
        }
        break;
    }

    case WM_DESTROY:
    {
        SendMessage(camhwnd, WM_CAP_DRIVER_DISCONNECT, 0, 0);
        PostQuitMessage(0);   /* send a WM_QUIT to the message queue */
        break;
    }

    default:              /* for messages that we don't deal with */
        return DefWindowProc(hwnd, message, wParam, lParam);
    }
    return 0;
}

void CreateBMPFile(HWND hwnd, LPTSTR pszFile, PBITMAPINFO pbi, HBITMAP hBMP, HDC hDC)
{
    HANDLE hf;                  // file handle
    BITMAPFILEHEADER hdr;       // bitmap file-header
    PBITMAPINFOHEADER pbih;     // bitmap info-header
    LPBYTE lpBits;              // memory pointer
    DWORD dwTotal;              // total count of bytes
    DWORD cb;                   // incremental count of bytes
    BYTE *hp;                   // byte pointer
    DWORD dwTmp;

    pbih = (PBITMAPINFOHEADER) pbi;
    lpBits = (LPBYTE) GlobalAlloc(GMEM_FIXED, pbih->biSizeImage);

    if (!lpBits)
    {
        MessageBox(hwnd,"GlobalAlloc","Error", MB_OK );
    }
// Retrieve the color table (RGBQUAD array) and the bits
// (array of palette indices) from the DIB.
    if (!GetDIBits(hDC, hBMP, 0, (WORD) pbih->biHeight, lpBits, pbi,DIB_RGB_COLORS))
    {
        MessageBox(hwnd,"GetDIBits","Error",MB_OK );
    }
// Create the .BMP file.
    hf = CreateFile(pszFile,GENERIC_READ | GENERIC_WRITE,(DWORD) 0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,(HANDLE) NULL);
    if (hf == INVALID_HANDLE_VALUE)
    {
        MessageBox( hwnd,"CreateFile","Error", MB_OK);
    }

    hdr.bfType = 0x4d42;  // File type designator "BM" 0x42 = "B" 0x4d = "M"
// Compute the size of the entire file.
    hdr.bfSize = (DWORD) (sizeof(BITMAPFILEHEADER) + pbih->biSize + pbih->biClrUsed * sizeof(RGBQUAD) + pbih->biSizeImage);
    hdr.bfReserved1 = 0;
    hdr.bfReserved2 = 0;
// Compute the offset to the array of color indices.
    hdr.bfOffBits = (DWORD) sizeof(BITMAPFILEHEADER) + pbih->biSize + pbih->biClrUsed * sizeof (RGBQUAD);
// Copy the BITMAPFILEHEADER into the .BMP file.
    if (!WriteFile(hf, (LPVOID) &hdr, sizeof(BITMAPFILEHEADER), (LPDWORD) &dwTmp,  NULL) )
    {
        MessageBox(hwnd,"WriteFileHeader","Error",MB_OK );
    }
// Copy the BITMAPINFOHEADER and RGBQUAD array into the file.
    if (!WriteFile(hf, (LPVOID) pbih, sizeof(BITMAPINFOHEADER) + pbih->biClrUsed * sizeof (RGBQUAD), (LPDWORD) &dwTmp, NULL))
    {
        MessageBox(hwnd,"WriteInfoHeader","Error",MB_OK );
    }
// Copy the array of color indices into the .BMP file.
    dwTotal = cb = pbih->biSizeImage;
    hp = lpBits;
    if (!WriteFile(hf, (LPSTR) hp, (int) cb, (LPDWORD) &dwTmp,NULL))
    {
        MessageBox(hwnd,"WriteFile","Error",MB_OK );
    }
// Close the .BMP file.
    if (!CloseHandle(hf))
    {
        MessageBox(hwnd,"CloseHandle","Error",MB_OK );
    }

// Free memory.
    GlobalFree((HGLOBAL)lpBits);
}

PBITMAPINFO CreateBitmapInfoStruct(HWND hwnd, HBITMAP hBmp)
{
    BITMAP bmp;
    PBITMAPINFO pbmi;
    WORD cClrBits;
// Retrieve the bitmap color format, width, and height.
    if (!GetObject(hBmp, sizeof(BITMAP), (LPSTR)&bmp))
    {
        MessageBox(hwnd,"GetObject","Error",MB_OK );
    }
// Convert the color format to a count of bits.
    cClrBits = (WORD)(bmp.bmPlanes * bmp.bmBitsPixel);
    if (cClrBits == 1)
        cClrBits = 1;
    else if (cClrBits <= 4)
        cClrBits = 4;
    else if (cClrBits <= 8)
        cClrBits = 8;
    else if (cClrBits <= 16)
        cClrBits = 16;
    else if (cClrBits <= 24)
        cClrBits = 24;
    else cClrBits = 32;

// Allocate memory for the BITMAPINFO structure. (This structure
// contains a BITMAPINFOHEADER structure and an array of RGBQUAD
// data structures.)

    if (cClrBits != 24)
    {
        pbmi = (PBITMAPINFO) LocalAlloc(LPTR,sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * (1<< cClrBits));
    }
// There is no RGBQUAD array for the 24-bit-per-pixel format.
    else
        pbmi = (PBITMAPINFO) LocalAlloc(LPTR, sizeof(BITMAPINFOHEADER));

// Initialize the fields in the BITMAPINFO structure.
    pbmi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    pbmi->bmiHeader.biWidth = bmp.bmWidth;
    pbmi->bmiHeader.biHeight = bmp.bmHeight;
    pbmi->bmiHeader.biPlanes = bmp.bmPlanes;
    pbmi->bmiHeader.biBitCount = bmp.bmBitsPixel;
    if (cClrBits < 24)
    {
        pbmi->bmiHeader.biClrUsed = (1<<cClrBits);
    }
// If the bitmap is not compressed, set the BI_RGB flag.
    pbmi->bmiHeader.biCompression = BI_RGB;

// Compute the number of bytes in the array of color
// indices and store the result in biSizeImage.
// For Windows NT, the width must be DWORD aligned unless
// the bitmap is RLE compressed. This example shows this.
// For Windows 95/98/Me, the width must be WORD aligned unless the
// bitmap is RLE compressed.
    pbmi->bmiHeader.biSizeImage = ((pbmi->bmiHeader.biWidth * cClrBits +31) & ~31) /8 * pbmi->bmiHeader.biHeight;
// Set biClrImportant to 0, indicating that all of the
// device colors are important.
    pbmi->bmiHeader.biClrImportant = 0;

    return pbmi; //return BITMAPINFO
}

