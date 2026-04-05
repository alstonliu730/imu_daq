#include "mpu9250.h"
#include "i2c_dev.h"
#include "driver/i2c_master.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

i2c_master_dev_handle_t mpu_i2c_handle;

static bool initialized = false;

esp_err_t mpu9250_init(void) {
    const char* mpu_init_tag = "mpu9250_init";
    esp_err_t status = ESP_OK;
    uint8_t* write_buf = malloc(sizeof(uint8_t) * 4); 

    ESP_LOGI(mpu_init_tag, "Initializing MPU9250");

    // Check if the i2c master bus is initialized
    if (bus_handle == NULL) {
        // initialize the i2c master bus
        i2c_master_init(bus_handle);
    }

    // Check if the MPU is connected
    if (i2c_master_probe(*bus_handle, MPU9250_DEV_ADDR, I2C_MASTER_TIMEOUT_MS))
    // Check if the mpu is already initialized
    if (initialized) {
        ESP_LOGE(mpu_init_tag, "MPU9250 already initialized.");
        return ESP_ERR_INVALID_STATE;
    }
    
    // set the device configuration
    i2c_device_config_t mpu_dev_config = {
        .dev_addr_length = I2C_ADDR_BIT_LEN_7,
        .device_address = MPU9250_DEV_ADDR,
        .scl_speed_hz = I2C_MASTER_FREQ_HZ,
    };

    // add this sensor as a device
    status = i2c_master_bus_add_device(*bus_handle, &mpu_dev_config, &mpu_i2c_handle);
    if (status != ESP_OK)
    {
        ESP_LOGE(mpu_init_tag, "Error adding MPU9250 to the i2c master bus.");
        return status;
    }

    // Reset the device
    status = i2c_write_bits(mpu_i2c_handle, IMU_PWR_MGMT_1, IMU_PWR_H_RESET, 1, 1);
    if (status != ESP_OK) {
        ESP_LOGE(mpu_init_tag, "Failed sending reset bit to power management");
        free(write_buf);
        return status;
    }
    vTaskDelay(100 / portTICK_PERIOD_MS); // wait for data to be available in the sensor

    // set clock source
    status = i2c_write_bits(mpu_i2c_handle, IMU_PWR_MGMT_1, 0, 3, auto_select);
    if (status != ESP_OK) {
        ESP_LOGE(mpu_init_tag, "Failed setting clock source bits in power management");
        free(write_buf);
        return status;
    }
    vTaskDelay(10 / portTICK_PERIOD_MS);
    
    // define configuration register
    uint16_t config_value = 0x2;
    status = i2c_write_bits(mpu_i2c_handle, IMU_CONFIG, 0, 8, config_value);
    if (status != ESP_OK) {
        ESP_LOGE(mpu_init_tag, "Failed setting the configuration register");
        free(write_buf);
        return status;
    }
    vTaskDelay(10/ portTICK_PERIOD_MS);

    // define gyro sensitivity
    write_buf[0] = IMU_GYRO_CONFIG;
    write_buf[1] = 0x08;

    status = i2c_master_transmit(mpu_i2c_handle, write_buf, 2, MPU9250_I2C_TIMEOUT);
    if (status != ESP_OK) {
        ESP_LOGE(mpu_init_tag, "Failed to write to gyro configuration");
        free(write_buf);
        return status;
    }

    // define accel sensitivity
    write_buf[0] = IMU_ACCEL_CONFIG_1;
    write_buf[1] = 0x08;
    write_buf[2] = 0x02;

    status = i2c_master_transmit(mpu_i2c_handle, write_buf, 2, MPU9250_I2C_TIMEOUT);
    if (status != ESP_OK) {
        ESP_LOGE(mpu_init_tag, "Failed to write to gyro configuration");
        free(write_buf);
        return status;
    }
    vTaskDelay(10 / portTICK_PERIOD_MS);

    // set sample rate divider (SAMP_RATE = INTERNAL_SampRate / (1 + SMPLRT_DIV))
    write_buf[0] = IMU_SMPLRT_DIV;
    write_buf[1] = 3;

    status = i2c_master_transmit(mpu_i2c_handle, write_buf, 2, MPU9250_I2C_TIMEOUT);
    if (status != ESP_OK) {
        ESP_LOGE(mpu_init_tag, "Failed to set sampling rate divider");
        free(write_buf);
        return status;
    }
    vTaskDelay(10 / portTICK_PERIOD_MS);

    // enable the magnetometer

    ESP_LOGI(mpu_init_tag, "MPU9250 Initialization Complete");
    free(write_buf);
    return status;
}

// gets the raw acceleration data
esp_err_t get_raw_accel(uint8_t* accel_buf) {
    uint8_t write_buf = IMU_ACCEL_XOUT_H;
    return i2c_master_transmit_receive(mpu_i2c_handle, &write_buf, 1, accel_buf, 6, -1); 
}

// gets the raw gyroscopic data
esp_err_t get_raw_gyro(uint8_t* gyro_buf) {
    uint8_t write_buf = IMU_GYRO_XOUT_H;
    return i2c_master_transmit_receive(mpu_i2c_handle, &write_buf, 1, gyro_buf, 6, -1);
}

// gets the raw temperature data
esp_err_t get_raw_temp(uint8_t* temp_buf) {
    uint8_t write_buf = IMU_TEMP_OUT_H;
    return i2c_master_transmit_receive(mpu_i2c_handle, &write_buf, 1, temp_buf, 2, -1);
}
