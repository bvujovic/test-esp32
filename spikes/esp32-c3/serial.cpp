//* https://www.reddit.com/r/esp32/comments/16qaf8u/trouble_reading_serial_output_on_my_esp32c3/?rdt=50276

// ; platformio.ini, only for super mini ESP32
// ; build_flags = 
// ;   -D ARDUINO_USB_MODE=1
// ;   -D ARDUINO_USB_CDC_ON_BOOT=1

// build_flags =
    // -DARDUINO_USB_MODE=1
    // -DARDUINO_USB_CDC_ON_BOOT=1
    // -DARDUINO_ESP32C3_DEV=1

#include <Arduino.h>

void setup()
{
    Serial.begin(115200);
    Serial.println("\nHey now.");
    pinMode(8, OUTPUT);
    digitalWrite(8, 0);
}

void loop()
{
    Serial.print('x');
    delay(1000);
}
