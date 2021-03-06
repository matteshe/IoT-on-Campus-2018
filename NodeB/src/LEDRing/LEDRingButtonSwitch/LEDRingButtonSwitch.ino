/*
 * Used libraries
 * - Adafruit Neopixel by Adafruit 1.1.6 (https://github.com/adafruit/Adafruit_NeoPixel)
 * 
 * to install: Sketch -> Include Library -> Manage Libraries -> Search 
 */

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define DATA_PIN D5
#define SW1_PIN D6
#define SW2_PIN D7

// setup color for the led with will be switched
const int COLOR_R = 0;
const int COLOR_G = 255;
const int COLOR_B = 0;

int button1State = 0;
int button2State = 0;

// index of led which is on
int ledOn = 0;

// index of last led which was on
int lastLedOn = -1;

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(12, DATA_PIN, NEO_GRB + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

void setup() {
  // initialize the pushbutton pin as an input:
  pinMode(SW1_PIN, INPUT);  
  pinMode(SW2_PIN, INPUT);
  
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif
  // End of trinket special code

  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  button1State = digitalRead(SW1_PIN);
  button2State = digitalRead(SW2_PIN);

  // At least one of the buttons must not be pressed
  if (button1State == LOW || button2State == LOW) {
    if (button1State == HIGH) {
      // button pressed
      ledOn += ledOn;
      if (ledOn == 12) {
         ledOn = 0;
      }
    }
    
    if (button2State == HIGH) {
      // button pressed
      ledOn -= ledOn;
      if (ledOn ==  -1) {
         ledOn = 11;
      }
    }
  }
  
  // Some example procedures showing how to display to the pixels:
  if (ledOn != lastLedOn) {
    lastLedOn = ledOn;
    colorWipe(strip.Color(COLOR_R, COLOR_G, COLOR_B));
    delay(1000);
  }
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    if (i == ledOn) {      
      strip.setPixelColor(i, c);
    } else {      
      strip.setPixelColor(i, strip.Color(0, 0, 0));
    }
    strip.show();
  }
}

