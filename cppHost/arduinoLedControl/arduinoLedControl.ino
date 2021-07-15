#include <FastLED.h>
//#include <Adafruit_NeoPixel.h>

#define PIN 6
#define NUM_LED 60
#define NUM_DATA 182
#define RECON_TIME 1000

//Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LED, PIN, NEO_GRB + NEO_KHZ800);

uint8_t data[NUM_DATA];
CRGB leds[NUM_LED];
int index = 0;

void setup() {
  Serial.begin(115200);

  //strip.begin();
  //strip.show();
  FastLED.addLeds<WS2812, PIN, GRB>(leds, NUM_LED).setCorrection(TypicalLEDStrip);
  FastLED.clear();
  FastLED.show();

  Serial.print("ozy");
}

void loop() {
  if (Serial.available() > 0) {
    data[index++] = (uint8_t)Serial.read();
    
    if (index >= NUM_DATA) {
      index = 0;
      if ((data[0] == 'o') && (data[1] == 'z')) {
        for (int i = 0; i < NUM_LED; i++) {
          int led_index = i * 3 + 2;
          //strip.setPixelColor(i, strip.Color(data[led_index], data[led_index + 1], data[led_index + 2]));
          leds[i].setRGB((int) data[led_index], (int) data[led_index + 1], (int) data[led_index + 2]);
        }
        //strip.show();
        FastLED.show();
      }
    }
    Serial.print('y');
  }
}
