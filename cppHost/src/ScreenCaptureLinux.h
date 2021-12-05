#pragma once

#include "ScreenCapture.h"

class ScreenCaptureLinux : public ScreenCapture {
private:
    int screenNumber;
public:

    ScreenCaptureLinux(int screenNumber);
    ~ScreenCaptureLinux();

    std::string initialize();
    void close();
    bool captureNext();

    std::vector<uint8_t>* getScreenData();
};