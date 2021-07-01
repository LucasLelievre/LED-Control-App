#include <Adafruit_NeoPixel.h>

#define PIN 6
#define NUM_LED 60
#define NUM_DATA 182
#define RECON_TIME 1000

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LED, PIN, NEO_GRB + NEO_KHZ800);

uint8_t led_color[NUM_DATA];
int index = 0;
unsigned long before = 0;
unsigned long now = 0;

void setup() {
  strip.begin();
  strip.show();
  Serial.begin(115200);
  Serial.print("ozy");
}

void loop() {


  if (Serial.available() > 0) {
    led_color[index++] = (uint8_t)Serial.read();

    if (index > NUM_DATA) {
      index = 0;
      if ((led_color[0] == 'o') && (led_color[1] == 'z')) {
        for (int i = 0; i < NUM_LED; i++) {
          int led_index = i * 3 + 2;
          strip.setPixelColor(i, strip.Color(led_color[led_index], led_color[led_index + 1], led_color[led_index + 2]));
        }
        strip.show();
      }
    }
    Serial.print('y');
  }

  /*
    before = millis();
    // max 3ms
    for (int i = 0; i < NUM_LED; i++){
      strip.setPixelColor(i, 255, 255, 255);
    }
    strip.show();

    Serial.println(millis() - before);
  */
}
