#include <Arduino.h>
#include "driver/i2s.h"

#define I2S_PORT I2S_NUM_0

#define I2S_BCLK 26
#define I2S_WS 25
#define I2S_SD 33

#define SAMPLE_RATE 16000

int32_t buffer[32];

void setup()
{
    Serial.begin(115200);
    delay(1000);

    i2s_config_t config = {
        .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX),

        .sample_rate = SAMPLE_RATE,

        .bits_per_sample = I2S_BITS_PER_SAMPLE_32BIT,

        .channel_format = I2S_CHANNEL_FMT_ONLY_RIGHT,

        .communication_format =
            (i2s_comm_format_t)(I2S_COMM_FORMAT_STAND_I2S),

        .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,

        .dma_buf_count = 4,
        .dma_buf_len = 256,

        .use_apll = false,
        .tx_desc_auto_clear = false,
        .fixed_mclk = 0};

    i2s_pin_config_t pins = {
        .bck_io_num = I2S_BCLK,
        .ws_io_num = I2S_WS,
        .data_out_num = I2S_PIN_NO_CHANGE,
        .data_in_num = I2S_SD};

    esp_err_t err;

    err = i2s_driver_install(I2S_PORT, &config, 0, nullptr);
    Serial.printf("driver install: %d\n", err);

    err = i2s_set_pin(I2S_PORT, &pins);
    Serial.printf("set pins: %d\n", err);

    i2s_zero_dma_buffer(I2S_PORT);

    Serial.println("Starting...");
}

void loop()
{
    size_t bytesRead = 0;

    i2s_read(
        I2S_PORT,
        buffer,
        sizeof(buffer),
        &bytesRead,
        portMAX_DELAY);

    int count = bytesRead / sizeof(int32_t);

    Serial.println("----");

    for (int i = 0; i < count; i++)
    {
        Serial.printf(
            "%ld   0x%08lX\n",
            (long)buffer[i],
            (unsigned long)buffer[i]);
    }

    delay(500);
}