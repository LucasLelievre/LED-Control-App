// cppHost.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include <Windows.h>
#include "SerialArduino.h"
#include "ScreenCapture_old.h"
#include "ScreenCapture.h"
#include "ledColour.h"

int main()
{
    std::cout << "Starting ...\n\n";

    static int WIDTH = 1920;
    static int HEIGHT = 1080;
    static int NUM_LEDS = 60;
    static int NUM_LEDS_X = 30;
    static int NUM_LEDS_Y = 16;

    ledColour leds (WIDTH, HEIGHT, NUM_LEDS, NUM_LEDS_X, NUM_LEDS_Y);

    ScreenCapture capture(1);
    std::string err = capture.Initialize();
    ScreenCapture_old capture_old(1920, 1080);

    if (err.length()) {
        std::cout << err << "\n";
        return 1;
    }


    std::cout << "Connecting to Arduino...\n\n";
    SerialArduino * arduino = new SerialArduino("\\\\.\\COM5");
    if (arduino->IsConnected()) {
        std::cout << "Arduino connected.\n\n";
    } else {
        std::cout << "Connexion to Arduino failed.\nQuitting.";
        return 1;
    }

    auto now = std::chrono::steady_clock::now();
    auto old = now;

    std::cout << "App initialised.\n\nSending data.\n\n";
    while (arduino->IsConnected()) {

        //old = std::chrono::steady_clock::now();

        capture.CaptureNext();
        char* serialData = leds.computeColours(capture.getScreenData());
        //capture_old.screenShotDesktop();
        //char* serialData = host.computeColours(capture_old.getScreenData());

        //std::this_thread::sleep_for(std::chrono::milliseconds(1));
        
        
        /*
        char inData[256] = "";
        int dataLength = 256;
        for (;;) {
            int readSize = arduino->ReadData(inData, 256);
            if (inData[readSize - 1] == 'y') {
                break;
            }
        }*/

        arduino->WriteData(serialData, NUM_LEDS * 3 + 2);
        

        Sleep(25);
        //now = std::chrono::steady_clock::now();
        
        //std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(now - old).count() << std::endl;
        //old = now;
    }
    std::cout << "Connexion to Arduino lost.\nQuitting.";
}
