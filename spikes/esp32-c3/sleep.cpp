// 1: blue board with yellow pin headers and antenna connector
// 2: black board with short red antenna
// 3: ESP32-C3-Zero (blue), smaller red ceramic antenna with improvement
//
// Board    Normal   Deep Sleep (with power LED on)
// 1        19.2mA   2.8mA
// 2        17.8mA   0.88mA
// 3        18.2mA   0.50mA

#include <Arduino.h>

// const byte pinLedBuiltin = 48;

void setup()
{
    // delay(5000); // Wait for 5 seconds before starting
    // ESP.deepSleep(5000000); // Put the ESP32 into deep sleep for 5 seconds
    
    // delay(1000); // Short delay to ensure the LED state is set before sleeping
    // pinMode(pinLedBuiltin, OUTPUT);
    // digitalWrite(pinLedBuiltin, LOW); // Turn off the LED after setup
    // delay(3000); // Short delay to ensure the LED state is set before sleeping

    esp_sleep_enable_timer_wakeup(10 * 1000 * 1000);
    esp_deep_sleep_start();
}

void loop() {}
