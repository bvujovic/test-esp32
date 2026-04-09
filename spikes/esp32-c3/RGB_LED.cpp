//* Test the Adafruit NeoPixel library with the onboard LED of an ESP32-C3-Zero

#include <Adafruit_NeoPixel.h> // lib_deps = adafruit/Adafruit NeoPixel@^1.11.0

#define PIN 10      // GPIO10 is the onboard LED on the ESP32-C3-Zero
#define NUMPIXELS 1 // Only 1 onboard LED

// NEO_RGB + NEO_KHZ800 is common, sometimes NEO_GRB
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup()
{
    pixels.begin();
}

void loop()
{
    pixels.clear();
    pixels.setPixelColor(0, pixels.Color(0, 150, 0)); // Green
    pixels.show();
    delay(1000);
    pixels.setPixelColor(0, pixels.Color(0, 0, 150)); // Blue
    pixels.show();
    delay(1000);
    // pixels.setPixelColor(0, pixels.Color(150, 0, 0)); // Red
    // pixels.show();
    // delay(1000);
    pixels.setPixelColor(0, pixels.Color(50, 0, 0)); // Red
    pixels.show();
    delay(1000);
    pixels.setPixelColor(0, pixels.Color(15, 0, 0)); // Red
    pixels.show();
    delay(1000);
    pixels.setPixelColor(0, pixels.Color(5, 0, 0)); // Red
    pixels.show();
    delay(1000);
    pixels.setPixelColor(0, pixels.Color(50, 0, 50)); // purple
    pixels.show();
    delay(1000);
    pixels.setPixelColor(0, pixels.Color(50, 30, 0)); // yellow
    pixels.show();
    delay(1000);
    // turn off the LED
    pixels.clear();
    pixels.show();
    delay(3000);
}
