#include <FastLED.h>
//#include <Adafruit_NeoPixel.h>

#define PIN 6
#define NUM_LED 60
#define NUM_DATA 182
#define RECON_TIME 1000

uint8_t data[NUM_DATA];
CRGB leds[NUM_LED];
//Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LED, PIN, NEO_GRB + NEO_KHZ800);
//uint8_t led_color[NUM_DATA];
int index = 0;
//unsigned long last_afk = 0;
//unsigned long cur_time = 0;

void setup() {
  //strip.begin();
  //strip.show();
  Serial.begin(115200);
  FastLED.addLeds<WS2812, PIN, GRB>(leds, NUM_LED).setCorrection(TypicalLEDStrip);
  FastLED.clear();
  FastLED.show();

  //Serial.print("ozy");
}

void loop() {
  if (Serial.available() > 0) {
    data[index++] = (uint8_t)Serial.read();

    if (index >= NUM_DATA) {
      //last_afk =  millis();
      index = 0;
      if ((data[0] == 'o') && (data[1] == 'z')) {
        for (int i = 0; i < NUM_LED; i++) {
          int led_index = i * 3 + 2;
          //strip.setPixelColor(i, strip.Color(led_color[led_index], led_color[led_index + 1], led_color[led_index + 2]));
          leds[i].setRGB((int)data[led_index], (int)data[led_index + 1], (int)data[led_index + 2]);
        }
        //strip.show();
        FastLED.show();
      }
      //Serial.write('y');
    }
  } /*else {
    cur_time = millis();
    if (cur_time - last_afk > RECON_TIME) {
      Serial.write('y');
      last_afk =  cur_time;
      index = 0;
    }

  }*/
}
