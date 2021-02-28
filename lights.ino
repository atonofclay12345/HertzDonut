#include "FastLED.h"
#include "Python.h"

//How many lights?
#define NUM_LEDS 20
#define PIN 0
#define updateLEDS 8
#define COLOR_SHIFT 180000 //shifts color spectrum this often (ms)

CRGB leds[NUM_LEDS]; 

//Yo wtf
unsigned long setTime = COLOR_SHIFT;
int shiftC = 0;
int mulC = 2;

// Define color structure for rgb
struct color {
  int r;
  int g;
  int b;
};
typedef struct color Color;

void setup() { 
    Serial.begin(9600); 
  	FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS); //telling FastLED how many

    for(int i = 0; i < NUM_LEDS ; i++) {
        leds[i] = CRGB(0,0,0);
        }
        FastLED.show();
}