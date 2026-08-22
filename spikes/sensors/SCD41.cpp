#include <Arduino.h>
#include <Wire.h>
#include <SensirionI2CScd4x.h> // sensirion/Sensirion I2C SCD4x@^1.1.0

SensirionI2cScd4x scd;

void setup()
{
  Serial.begin(115200);
  while (!Serial)
    delay(10);

  Wire.begin(); // Adjust SDA/SCL pins here if needed (e.g., Wire.begin(21, 22))
  // scd.begin(Wire);
  scd.begin(Wire, 0x62); // Use the default I2C address for SCD41 (0x62)

  // Stop any active measurements before configuration
  scd.stopPeriodicMeasurement();

  // Start continuous periodic measurements (samples every 5s)
  auto error = scd.startPeriodicMeasurement();
  if (error)
    Serial.println("Error starting SCD41!");
  else
    Serial.println("SCD41 initialized successfully.");
}

void loop()
{
  bool isDataReady = false;
  scd.getDataReadyStatus(isDataReady);

  if (isDataReady)
  {
    uint16_t co2 = 0;
    float temperature = 0.0f;
    float humidity = 0.0f;

    auto error = scd.readMeasurement(co2, temperature, humidity);
    if (!error)
      Serial.printf("CO2: %d ppm | Temp: %.2f °C | Humidity: %.2f %%\n", co2, temperature, humidity);
  }
  delay(1000);
}
