//* Test code for ESP32-s3 SuperMini: blinks an external LED and prints a message to the Serial Monitor every second.

#include <Arduino.h>

const byte pinLedBuiltin = 48; // Built-in LED pin for ESP32-S3-DevKitC-1
const byte pinLed = 12; // External LED

void setup()
{
    Serial.begin(115200);
    while (!Serial) {
        delay(10); // wait for serial port to connect. Needed for native USB
    }
    pinMode(pinLedBuiltin, OUTPUT);
    digitalWrite(pinLedBuiltin, LOW); // Turn off the LED after setup
    pinMode(pinLed, OUTPUT);
}

int counter = 0;

void loop()
{
    delay(1000);
    Serial.println("*");
    digitalWrite(pinLed, counter++ % 2);
}