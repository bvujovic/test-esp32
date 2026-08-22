#include <Arduino.h>
#include <Wire.h>

void setup()
{
  Wire.begin();
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
    Serial.println("No I2C devices found\n");
  delay(5000);
}
