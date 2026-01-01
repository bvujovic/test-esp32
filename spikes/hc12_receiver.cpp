#include <Arduino.h>

// HC-12 is connected to pins 16 (RX2) and 17 (TX2)
HardwareSerial HC12(2); // use UART2 (index 2)

const byte pinLed = 2;                                         // onboard LED
void ledOn(bool on) { digitalWrite(pinLed, on ? HIGH : LOW); } // turn LED on/off

void setup()
{
    Serial.begin(115200);                 // USB serial monitor
    HC12.begin(4800, SERIAL_8N1, 16, 17); // RX, TX
    pinMode(pinLed, OUTPUT);
    ledOn(false);

    Serial.println("ESP32 HC-12 Receiver started...");
}

String message;

void loop()
{
    // while (HC12.available())
    // {
    //     char c = HC12.read();
    //     Serial.write(c); // forward everything to Serial Monitor
    // }
    if (HC12.available())
    {
        auto now = millis();
        ledOn(true);
        message = HC12.readStringUntil('\n');
        // Serial.println("Time: " + String(millis() - now) + " ms");
        Serial.println("Received: " + message);
        // const char *msg = message.c_str();
        // Serial.println(msg + 1); // skip first character
        if (millis() - now < 100)
            delay(100);
        ledOn(false);
    }
}
