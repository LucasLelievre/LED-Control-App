#include "ScreenCapture_old.h"

ScreenCapture_old::ScreenCapture_old(int width, int height) {
    this->width = width;
    this->height = height;

    hScreen = GetDC(NULL);
    hdcMem = CreateCompatibleDC(hScreen);
    hBitmap = CreateCompatibleBitmap(hScreen, this->width, this->height);
    screenData = (BYTE*)malloc(4 * this->width * this->height);

    this->windowHandle = NULL;
}

ScreenCapture_old::~ScreenCapture_old() {
    ReleaseDC(GetDesktopWindow(), this->hScreen);
    DeleteDC(this->hdcMem);
    DeleteObject(this->hBitmap);
}

BYTE * ScreenCapture_old::getScreenData() {
	return this->screenData;
}

void ScreenCapture_old::screenShotDesktop() {
    HGDIOBJ hOld = SelectObject(hdcMem, hBitmap);
    BitBlt(hdcMem, 0, 0, this->width, this->height, hScreen, 0, -this->height, SRCCOPY);
    SelectObject(hdcMem, hOld);

    BITMAPINFOHEADER bmi = { 0 };
    bmi.biSize = sizeof(BITMAPINFOHEADER);
    bmi.biPlanes = 1;
    bmi.biBitCount = 32;
    bmi.biWidth = this->width;
    bmi.biHeight = -this->height;
    bmi.biCompression = BI_RGB;
    bmi.biSizeImage = 3 * this->width * this->height;

    screenData = (BYTE*)malloc(4 * this->width * this->height);

    GetDIBits(hdcMem, hBitmap, 0, this->height, screenData, (BITMAPINFO*)&bmi, DIB_RGB_COLORS);
}
/*
void ScreenCapture_old::screenShotFullscreen() {
    
    IDirect3D9 * g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

    IDirect3DDevice9* g_pd3dDevice;
    D3DPRESENT_PARAMETERS d3dpp;

    g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, this->windowHandle, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &g_pd3dDevice);

    IDirect3DSurface9* pSurface;
    g_pd3dDevice->CreateOffscreenPlainSurface(this->width, this->height,
        D3DFMT_A8R8G8B8, D3DPOOL_SCRATCH,
        &pSurface, NULL);
    g_pd3dDevice->GetFrontBufferData(0, pSurface);
    D3DLOCKED_RECT lockedRect;
    pSurface->LockRect(&lockedRect, NULL,
        D3DLOCK_NO_DIRTY_UPDATE |
        D3DLOCK_NOSYSLOCK | D3DLOCK_READONLY);

    BYTE* pBits = (BYTE*)malloc(4 * this->width * this->height);
    int BITSPERPIXEL = 32;

    for (int i = 0; i < this->height; i++) {
        memcpy(pBits + i * this->width * BITSPERPIXEL / 8, (BYTE*)lockedRect.pBits + i * lockedRect.Pitch, this->width * BITSPERPIXEL / 8);
    }
    //g_pSurface->UnlockRect();
    pSurface->UnlockRect();
    pSurface->Release();
    
}

void ScreenCapture_old::selectWindow() {
    std::vector<HWND> windowHandles;
    std::cout << "List of all windows :\n";
    EnumWindows(this->enumWindowCallback, reinterpret_cast<LPARAM>(&windowHandles));
    std::cout << "\n\n";
    int choice;
    std::cout << "Choose the Fullscreen app\n\n";
    std::cin >> choice;
    this->windowHandle = windowHandles.at(choice - 1);
}

void ScreenCapture_old::selectShadow() {
    HWND windowHandle = NULL;
    EnumWindows(this->shadowWindowCallback, reinterpret_cast<LPARAM>(&windowHandle));
    this->windowHandle = windowHandle;
}

BOOL CALLBACK ScreenCapture_old::shadowWindowCallback(HWND hWnd, LPARAM lparam) {
    // get window text
    size_t length = GetWindowTextLength(hWnd);
    wchar_t* buffer = new wchar_t[length + 1];
    GetWindowText(hWnd, buffer, length + 1);
    // name to string
    std::wstring tmp(buffer);
    std::string title(tmp.begin(), tmp.end());
    // List visible windows with a non-empty title
    if (IsWindowVisible(hWnd) && length != 0 && title.compare("Shadow")==0) {
        // Retrieve the pointer passed into this callback, and re-'type' it.
        // The only way for a C API to pass arbitrary data is by means of a void*.
        HWND* windowHandle = reinterpret_cast<HWND*>(lparam);
        *windowHandle = hWnd;
    }
    return TRUE;
}

BOOL CALLBACK ScreenCapture_old::enumWindowCallback(HWND hWnd, LPARAM lparam) {
    // get window text
    size_t length = GetWindowTextLength(hWnd);
    wchar_t* buffer = new wchar_t[length+1];
    GetWindowText(hWnd, buffer, length+1);
    // name to string
    std::wstring tmp(buffer);
    std::string title(tmp.begin(), tmp.end());
    // List visible windows with a non-empty title
    if (IsWindowVisible(hWnd) && length != 0) {
        // Retrieve the pointer passed into this callback, and re-'type' it.
        // The only way for a C API to pass arbitrary data is by means of a void*.
        std::vector<HWND>& windowHandles = *reinterpret_cast<std::vector<HWND>*>(lparam);
        windowHandles.push_back(hWnd);
        std::cout << windowHandles.size() << ":\t" << hWnd << ":\t" << title << "\n";
    }
    return TRUE;
}*/