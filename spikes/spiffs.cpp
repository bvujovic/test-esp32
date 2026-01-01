#include <Arduino.h>
#include <SPIFFS.h>

void setup()
{
  Serial.begin(115200);

  SPIFFS.begin();
  size_t total = SPIFFS.totalBytes(), used = SPIFFS.usedBytes();  
  Serial.printf("Total: %d KB\n", total / 1024);
  Serial.printf("Free: %d KB\n", (total - used) / 1024);
  SPIFFS.end();
}

void loop()
{
  delay(1000);
}
