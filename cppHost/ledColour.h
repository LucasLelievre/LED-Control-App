#pragma once
#include <iostream>
#include <Windows.h>
#include <vector>

class ledColour
{
private:
    int width, height, num_leds, num_leds_x, num_leds_y;

    const int leds[60][2] = {
        {0, 15}, {0, 14}, {0, 13}, {0, 12}, {0, 11}, {0, 10}, {0, 9}, {0, 8}, {0, 7}, {0, 6}, {0, 5}, {0, 4}, {0, 3}, {0, 2}, {0, 1}, // Left edge
        {0, 0}, {1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0}, {6, 0}, {7, 0}, {8, 0}, {9, 0},
        {10, 0}, {11, 0}, {12, 0}, {13, 0}, {14, 0}, {15, 0}, {16, 0}, {17, 0}, {18, 0}, {19, 0},
        {20, 0}, {21, 0}, {22, 0}, {23, 0}, {24, 0}, {25, 0}, {26, 0}, {27, 0}, {28, 0}, {29, 0}, // Top edge
        {29, 1}, {29, 2}, {29, 3}, {29, 4}, {29, 5}, {29, 6}, {29, 7}, {29, 8}, {29, 9}, {29, 10}, {29, 11}, {29, 12}, {29, 13}, {29, 14}, {29, 15}// Right edge
    };

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

public:
    char * computeColours(std::vector<uint8_t>*);
    char * computeColours(BYTE*);

    ledColour(int, int, float, int, int, int);
    ~ledColour();
};

