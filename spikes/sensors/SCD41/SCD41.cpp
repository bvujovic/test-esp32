#include <Arduino.h>
#include <Wire.h>
#include <SensirionI2CScd4x.h> // sensirion/Sensirion I2C SCD4x@^1.1.0

SensirionI2cScd4x scd;

void setup()
{
  Serial.begin(115200);
  delay(2000);
  Serial.println("Initializing SCD41 sensor...");

  // Wire.begin(); // Adjust SDA/SCL pins here if needed (e.g., Wire.begin(21, 22))
  Wire.begin(8, 9); 
  Wire.setClock(100000);
  // scd.begin(Wire);
  scd.begin(Wire, 0x62); // Use the default I2C address for SCD41 (0x62)

  // Stop any active measurements before configuration
  auto error = scd.stopPeriodicMeasurement();
  if (error)
    Serial.printf("Error stopping SCD41!, Error code: %d\n", error);

  // Start continuous periodic measurements (samples every 5s)
  error = scd.startPeriodicMeasurement();
  if (error)
    Serial.printf("Error starting SCD41!, Error code: %d\n", error);
  else
  {
    Serial.println("SCD41 initialized successfully.");
  
    float tempOffset;
    scd.getTemperatureOffset(tempOffset);
    printf("Temperature offset: %.2f °C\n", tempOffset);
    uint16_t altitude;
    scd.getSensorAltitude(altitude);
    printf("Sensor altitude: %d m\n", altitude);
  }
}

void loop()
{
  bool isDataReady = false;
  auto error = scd.getDataReadyStatus(isDataReady);
  if (error)
    Serial.printf("Error checking data ready status from SCD41!, Error code: %d\n", error);

  if (isDataReady)
  {
    uint16_t co2 = 0;
    float temperature = 0.0f;
    float humidity = 0.0f;

    auto error = scd.readMeasurement(co2, temperature, humidity);
    if (!error)
      Serial.printf("CO2: %d ppm | Temp: %.2f °C | Humidity: %.2f %%\n", co2, temperature, humidity);
    else
      Serial.printf("Error reading measurement from SCD41!, Error code: %d\n", error);
  }
  else
    Serial.println("Data not ready yet. Waiting for the next cycle...");

  delay(10000);
}
