#include <Arduino.h>
#include "driver/i2s.h"

#define I2S_PORT I2S_NUM_0

#define I2S_BCLK 26
#define I2S_WS 25
#define I2S_SD 33

#define SAMPLE_RATE 16000
#define BUFFER_SIZE 512

int32_t samples[BUFFER_SIZE];

void setupI2S()
{
    i2s_config_t i2s_config = {
        .mode = (i2s_mode_t)(I2S_MODE_MASTER |
                             I2S_MODE_RX),

        .sample_rate = SAMPLE_RATE,

        .bits_per_sample = I2S_BITS_PER_SAMPLE_32BIT,

        .channel_format = I2S_CHANNEL_FMT_ONLY_RIGHT,

        .communication_format = I2S_COMM_FORMAT_STAND_I2S,

        .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,

        .dma_buf_count = 4,
        .dma_buf_len = 256,

        .use_apll = false,
        .tx_desc_auto_clear = false,
        .fixed_mclk = 0};

    i2s_pin_config_t pin_config = {
        .bck_io_num = I2S_BCLK,
        .ws_io_num = I2S_WS,
        .data_out_num = I2S_PIN_NO_CHANGE,
        .data_in_num = I2S_SD};

    i2s_driver_install(
        I2S_PORT,
        &i2s_config,
        0,
        nullptr);

    i2s_set_pin(
        I2S_PORT,
        &pin_config);

    i2s_zero_dma_buffer(I2S_PORT);
}

void setup()
{
    Serial.begin(115200);
    delay(1000);

    Serial.println();
    Serial.println("ICS-43434 microphone test");
    Serial.println("-------------------------");

    setupI2S();

    Serial.println("I2S initialized.");
}

void loop()
{
    size_t bytesRead = 0;

    esp_err_t result = i2s_read(
        I2S_PORT,
        samples,
        sizeof(samples),
        &bytesRead,
        portMAX_DELAY);

    if (result != ESP_OK || bytesRead == 0)
        return;

    int sampleCount = bytesRead / sizeof(int32_t);

    int32_t minValue = INT32_MAX;
    int32_t maxValue = INT32_MIN;

    double sumSquares = 0;

    for (int i = 0; i < sampleCount; i++)
    {
        int32_t sample = samples[i];

        if (sample < minValue)
            minValue = sample;

        if (sample > maxValue)
            maxValue = sample;

        // ICS-43434 data is 24-bit stored in a 32-bit I2S word.
        // Shift down to make the numbers easier to work with.
        int32_t s = sample >> 8;

        sumSquares += (double)s * s;
    }

    double rms = sqrt(sumSquares / sampleCount);

    // Serial.print("MIN=");
    // Serial.print(minValue);

    // Serial.print(" MAX=");
    // Serial.print(maxValue);

    Serial.print(" RMS=");
    Serial.println(rms);

    delay(100);
}