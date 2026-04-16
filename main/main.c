#include <stdio.h>
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "uart_comm.h"
#include "mpu9250.h"
#include "esp_err.h"
#include "i2c_dev.h"

static const char* TAG = "main";

void app_main(void)
{   
    esp_err_t status;

    // initialize the i2c master bus
    status = i2c_master_init(&bus_handle);
    if (status != ESP_OK) {
        ESP_LOGE(TAG, "I2C Master Init Function Returned: %s", esp_err_to_name(status));
    }

    // print out the device list
    i2c_detect();

    // initialize the mpu9250
    status = mpu9250_init();
    if (status != ESP_OK) {
        ESP_LOGE(TAG, "MPU9250 Init Function Returned: %s", esp_err_to_name(status));
    }
}