//* Target: Idle single shot mode - 300 sec (5 min) sensor consumes 450µA @ 3.3V
//* it is recommended to adjust the sensor’s standard ASC period parameter depending on
//* the average sampling period achieved during idle single shot operation.
//* Every 5min read CO2 and send it to the hub (SensorNodeESP project)
//* Measured current consumption: 0.16mA, Li-ion full battery, ESP32 in deep sleep
//* ~2mA for period of 4.5min sleep, and 30sec awake

#include <Arduino.h>
#include <Wire.h>

#define MIN_SLEEP_TIME (5) // 5 minutes
const byte pinLed = 10;
ulong msStart;

#include <SensirionI2CScd4x.h> // sensirion/Sensirion I2C SCD4x@^1.1.0
SensirionI2cScd4x scd;

void takeSingleShotReading()
{
  //* Call this if the sensor was in periodic measurement mode before
  // auto msStartStop = millis();
  // scd.stopPeriodicMeasurement();
  // auto itvStop = millis() - msStartStop;
  // Serial.printf("Stop Time: %lu ms\n", itvStop);

  // auto msStartCall = millis();
  auto error = scd.measureSingleShot(); // blocking call, takes ~5s to complete
  if (error)
  {
    Serial.println("Failed to trigger single shot.");
    return;
  }
  // Serial.printf("Call Time: %lu ms\n", millis() - msStartCall);

  // Wait for measurement completion
  bool isDataReady = false;
  ulong startTime = millis();
  const ulong TIMEOUT_MS = 3000;

  // Poll until data is ready or timeout expires
  while (!isDataReady && (millis() < startTime + TIMEOUT_MS))
  {
    delay(200); // yield to avoid hammering the I2C bus
    scd.getDataReadyStatus(isDataReady);
  }
  Serial.printf("Single-Shot Measurement Time: %lu ms\n", millis() - startTime);

  if (isDataReady)
  {
    uint16_t co2 = 0;
    float temp = 0.0f, humidity = 0.0f;
    error = scd.readMeasurement(co2, temp, humidity);
    if (!error)
      Serial.printf("CO2: %d ppm | T: %.2f °C | RH: %.2f %%\n", co2, temp, humidity);
  }
  else
    Serial.println("Data not ready yet.");
}

void setup()
{
  msStart = millis();
  pinMode(pinLed, OUTPUT);
  digitalWrite(pinLed, HIGH);
  Serial.begin(115200);
  // while (!Serial)
  //   delay(100);
  delay(2000);
  digitalWrite(pinLed, LOW);
  Serial.println("Initializing SCD41 sensor...");

  // Wire.begin();          // Adjust SDA/SCL pins here if needed (e.g., Wire.begin(21, 22))
  Wire.begin(8, 9);
  scd.begin(Wire, 0x62); // Use the default I2C address for SCD41 (0x62)

  //* Power Cycled Single Shot Operation: use wakeUp() and powerDown() to save power between readings
  //* ASC is not available in that mode
  // scd.wakeUp();
  takeSingleShotReading();
  // scd.powerDown();

  // float tempOffset = 0.0f;
  // // scd.setTemperatureOffset(tempOffset);
  // auto error = scd.getTemperatureOffset(tempOffset);
  // if (!error)
  //   printf("Temperature offset set to %.2f °C\n", tempOffset);
  // else
  //   printf("Failed to get temperature offset, error code: %d\n", error);

  // uint16_t alt = 170;
  // // scd.setSensorAltitude(alt);
  // error = scd.getSensorAltitude(alt);
  // if (!error)
  //   printf("Altitude: %d m\n", alt);
  // else
  //   printf("Failed to get altitude, error code: %d\n", error);

  //* Persist settings to EEPROM (optional, only needed if you want to save the current configuration)
  // scd.persistSettings();
  // Serial.println("Settings persisted to EEPROM.");

  auto itvAwake = millis() - msStart;
  Serial.printf("Awake time: %lu ms\n", itvAwake);
  Serial.println("Entering MCU sleep cycle...");
  delay(100);
  esp_sleep_enable_timer_wakeup(MIN_SLEEP_TIME * 60 * 1000000 - itvAwake * 1000); // Adjust sleep time to account for awake time
  esp_deep_sleep_start();
}

void loop() { delay(100); }
