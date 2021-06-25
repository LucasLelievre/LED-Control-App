#include "ledColour.h"

ledColour::ledColour(int width, int height, int num_leds, int num_leds_x, int num_leds_y) {

    this->width = width;
    this->height = height;
    this->num_leds = num_leds;
    this->num_leds_x = num_leds_x;
    this->num_leds_y = num_leds_y;

    // Initialising pixelOffset data

    int x[16];
    int y[16];

    float rangeX, rangeY, stepX, stepY, startX, startY;

    rangeX = (float)this->width / this->num_leds_x;
    rangeY = (float)this->height / this->num_leds_y;
    stepX = rangeX / 16.0f;
    stepY = rangeY / 16.0f;

    for (int i = 0; i < this->num_leds; i++) { // For each LED...

        startX = rangeX * (float)leds[i][0] + stepX * 0.5f;
        startY = rangeY * (float)leds[i][1] + stepY * 0.5f;

        for (int j = 0; j < 16; j++) {
            x[j] = (int)(startX + stepX * (float)j);
            y[j] = (int)(startY + stepY * (float)j);
        }

        for (int row = 0; row < 16; row++) {
            for (int col = 0; col < 16; col++) {
                pixelOffset[i][row * 16 + col] = posToIndex((int)x[row], (int)y[col]);
            }
        }
    }
    
    // A special header expected by the Arduino, to identify the beginning of a new bunch data.

    serialData[0] = 'o';
    serialData[1] = 'z';
}
ledColour::~ledColour() {
}

char * ledColour::computeColours(std::vector<uint8_t> * screenData) {

    this->data_index = 2; // 0, 1 are predefined header

    for (int i = 0; i < this->num_leds; i++) {  // For each LED...
        int r = 0;
        int g = 0;
        int b = 0;

        for (int o = 0; o < 256; o++)
        {       //ARGB variable with 32 int bytes where
            /*
            r += (int)screenData->data()[(pixelOffset[i][o] + 2)];
            g += (int)screenData->data()[(pixelOffset[i][o] + 1)];
            b += (int)screenData->data()[(pixelOffset[i][o] + 0)];
            */
            r += (int)screenData->at(pixelOffset[i][o] + 2);
            g += (int)screenData->at(pixelOffset[i][o] + 1);
            b += (int)screenData->at(pixelOffset[i][o] + 0);
        }

        // Blend new pixel value with the value from the prior frame   
        ledColor[i * 3 + 0] = ((r >> 8) * (255 - this->fade) + prevColor[i * 3 + 0] * fade) >> 8;
        ledColor[i * 3 + 1] = ((g >> 8) * (255 - this->fade) + prevColor[i * 3 + 1] * fade) >> 8;
        ledColor[i * 3 + 2] = ((b >> 8) * (255 - this->fade) + prevColor[i * 3 + 2] * fade) >> 8;

        serialData[data_index++] = (byte)ledColor[i * 3 + 0];
        serialData[data_index++] = (byte)ledColor[i * 3 + 1];
        serialData[data_index++] = (byte)ledColor[i * 3 + 2];
    }

    std::copy(ledColor, ledColor+180, prevColor);
    //delete[] screenData;
    return this->serialData;
}

char* ledColour::computeColours(BYTE * screenData) {

    this->data_index = 2; // 0, 1 are predefined header

    for (int i = 0; i < this->num_leds; i++) {  // For each LED...
        int r = 0;
        int g = 0;
        int b = 0;

        for (int o = 0; o < 256; o++)
        {       //ARGB variable with 32 int bytes where
            r += (int)screenData[(pixelOffset[i][o] + 2)];
            g += (int)screenData[(pixelOffset[i][o] + 1)];
            b += (int)screenData[(pixelOffset[i][o] + 0)];
        }

        // Blend new pixel value with the value from the prior frame   
        ledColor[i * 3 + 0] = r / 256;
        ledColor[i * 3 + 0] = g / 256;
        ledColor[i * 3 + 0] = b / 256;

        serialData[data_index++] = (byte)ledColor[i * 3 + 0];
        serialData[data_index++] = (byte)ledColor[i * 3 + 0];
        serialData[data_index++] = (byte)ledColor[i * 3 + 0];
    }

    delete[] screenData;
    return this->serialData;
}

int ledColour::posToIndex(int x, int y) {
    return (x + (y * this->width)) * 4;
}