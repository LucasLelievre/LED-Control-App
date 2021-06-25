#pragma once
#include <windows.h>
#include <d3d9.h>
#include <iostream>
#include <string>
#include <vector>

class ScreenCapture_old
{
private:
    HDC hScreen;
    HDC hdcMem;
    HBITMAP hBitmap;
    BYTE* screenData;

    int width, height;

    //IDirect3DDevice9* g_pd3dDevice;
    //BYTE* pBits;
    HWND windowHandle;

public:
	void screenShotDesktop(void);
    //void screenShotFullscreen(void);

    BYTE* getScreenData(void);
    /*
    void selectWindow();
    void selectShadow();
    static BOOL CALLBACK enumWindowCallback(HWND, LPARAM);
    static BOOL CALLBACK shadowWindowCallback(HWND, LPARAM);
    */
    ScreenCapture_old(int, int);
    ~ScreenCapture_old();
};