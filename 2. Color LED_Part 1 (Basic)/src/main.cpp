#include <Arduino.h>
#include "NeoPixelBus.h"

#define PIN GPIO_NUM_2
#define colorSaturation 255

NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> strip(4, PIN);

RgbColor red(colorSaturation, 0, 0);
RgbColor green(0, colorSaturation, 0);
RgbColor blue(0, 0, colorSaturation);
RgbColor white(colorSaturation);
RgbColor black(0);

long nPixel = 0;

void setup() {
  Serial.begin(115200);

  ////////////////////////////////////////////////////////////////
  // 
  strip.Begin();
  strip.SetPixelColor(0, black);
  strip.Show();   // Send the updated pixel colors to the hardware.
}

void loop() {
  int c = ++nPixel % 4;
  strip.SetPixelColor(0, c==0? blue : black);
  strip.SetPixelColor(1, c==1? green : black);
  strip.SetPixelColor(2, c==2? red : black);
  strip.SetPixelColor(3, c==3? blue : black);
  strip.Show();   // Send the updated pixel colors to the hardware.

  delay( 1000 );
}