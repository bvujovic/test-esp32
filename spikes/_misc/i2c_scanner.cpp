#include <Arduino.h>
#include <Wire.h>

int cntNoDevices = 0;

void setup()
{
  Wire.begin();
  // Wire.begin(8, 9); // Set SDA to pin 8 and SCL to pin 9
  Serial.begin(115200);
  for (size_t i = 0; i < 5; i++)
    Serial.print(".");
  Serial.println("\nI2C Scanner");
}

void loop()
{
  byte error, address;
  int devices = 0;
  for (address = 1; address < 127; address++)
  {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
    if (error == 0)
    {
      Serial.print("I2C device found at address 0x");
      Serial.println(address, HEX);
      devices++;
    }
  }
  if (devices == 0)
    Serial.printf("No I2C devices found (%d)\n", cntNoDevices++);
  delay(5000);
}
