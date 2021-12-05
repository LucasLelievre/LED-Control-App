#pragma once
#include <iostream>
#include <vector>
#include <algorithm>

class ledColour
{
private:
    int width, height, num_leds, num_leds_x, num_leds_y;

    short fade = 70;
    int minBrightness = 120;

    int pixelOffset[60][256];

    // RGB values for each LED
    short ledColor[180];
    short prevColor[180];

    char gamma[256][3];
    char serialData[60 * 3 + 2];
    int data_index = 0;

    int posToIndex(int, int);

    // return the LED position in a grid of num_leds_x * num_leds_y
    int LEDposX(int);
    int LEDposY(int);

public:
    char * computeColours(std::vector<uint8_t>*);
    //char * computeColours(char*);

    //ledColour(int, int, float, int, int, int);
    ledColour(int*, float);
    ~ledColour();
};

