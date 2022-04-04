#include <AudioAnalyzer.h>
#include <FastLED.h>

#define NUM_LED_STRIPES 7
#define NUM_LEDS 30

int FreqVal[7] = { 63, 160, 400, 1000, 2500, 6250, 16000 };
  
Analyzer Audio = Analyzer(10, 11, 0);
CRGB leds[NUM_LED_STRIPES][NUM_LEDS];
CRGB color;

void setup() {
  Serial.begin(57600);
  Audio.Init();
  FastLED.addLeds<WS2812B, 5, GRB>(leds[0], NUM_LEDS);
  FastLED.addLeds<WS2812B, 6, GRB>(leds[1], NUM_LEDS);
  FastLED.addLeds<WS2812B, 7, GRB>(leds[2], NUM_LEDS);
  FastLED.addLeds<WS2812B, 8, GRB>(leds[3], NUM_LEDS);
  FastLED.addLeds<WS2812B, 9, GRB>(leds[4], NUM_LEDS);
  FastLED.addLeds<WS2812B, 12, GRB>(leds[5], NUM_LEDS);
  FastLED.addLeds<WS2812B, 13, GRB>(leds[6], NUM_LEDS);
}

void loop() {
  Audio.ReadFreq(FreqVal);
  FastLED.clear();
  FastLED.show();  
  for (int i = 0; i < NUM_LED_STRIPES; i++) {
    int output = map(FreqVal[i], 95, 1023, 0, NUM_LEDS);
    for (int j = 0; j < output; j++) {
      int output_color = map(j, 0, output, 0, 255);
      color = CRGB(255, (255-output_color), 255-(output_color));
      leds[i][j] = color;
    }
  }
  FastLED.show();
}
