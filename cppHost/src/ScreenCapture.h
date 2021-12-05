#pragma once

#include <string>
#include <vector>

#ifdef _WIN32
	#include "ScreenCaptureWindows.h"
#else
	#include "ScreenCaptureLinux.h"
#endif

// BGRA U8 Bitmap
struct Bitmap {
	int                  Width = 0;
	int                  Height = 0;
	std::vector<uint8_t> Buf;
};

class ScreenCapture {
private:
    int screenNumber;
public:
    static ScreenCapture* Create(int screenNumber);

    ScreenCapture();
    ScreenCapture(int screenNumber);
    ~ScreenCapture();

    virtual std::string initialize() = 0;
    virtual void close() = 0;
    virtual bool captureNext() = 0;

    virtual std::vector<uint8_t>* getScreenData() = 0;
};

ScreenCapture::ScreenCapture(){
    this->screenNumber = 0;
}

ScreenCapture::ScreenCapture(int screenNumber) {
    this->screenNumber = screenNumber;
}

ScreenCapture* ScreenCapture::Create(int screenNumber) {
    #ifdef _Win32
        return new ScreenCaptureWindows(screenNumber);
    #else
        return new ScreenCaptureLinux(screenNumber);
    #endif
}