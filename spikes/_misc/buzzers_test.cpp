//* Testing buzzers (3.3V and 5V) on ESP32  with interval selection (short/long) via pin 23

#include <Arduino.h>

const byte pinLed = 2;             // pin for onboard LED
const byte pinSmallBuzz = 22;      // pin for small buzzer
const byte pinBigBuzz = 14;        // pin for big buzzer
const byte pinIntervalSelect = 23; // pin to select interval (long or short)

const int itvPause = 2000;
const int itvShortBuzz = 100;
const int itvLongBuzz = 1000;

void setup()
{
    pinMode(pinLed, OUTPUT);
    digitalWrite(pinLed, LOW);
    pinMode(pinSmallBuzz, OUTPUT);
    digitalWrite(pinSmallBuzz, LOW);
    pinMode(pinBigBuzz, OUTPUT);
    digitalWrite(pinBigBuzz, LOW);
    pinMode(pinIntervalSelect, INPUT_PULLUP);
}

void loop()
{
    digitalWrite(pinBigBuzz, true);
    digitalWrite(pinSmallBuzz, true);
    delay(digitalRead(pinIntervalSelect) == LOW ? itvLongBuzz : itvShortBuzz);
    digitalWrite(pinBigBuzz, false);
    digitalWrite(pinSmallBuzz, false);
    delay(itvPause);
}
