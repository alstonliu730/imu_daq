#include "i2c_dev.h"
#include "esp_log.h"
#include "driver/i2c_master.h"
#include "mpu9250.h"
#include "sdkconfig.h"
#include "esp_err.h"

static const char* TAG = "i2c_dev";
i2c_master_bus_handle_t bus_handle = NULL;

// initialize the bus and return the bus handler
esp_err_t i2c_master_init(i2c_master_bus_handle_t* i2c_bus) {
    i2c_master_bus_config_t i2c_master_config = {
        .i2c_port = I2C_MASTER_NUM,
        .sda_io_num = I2C_MASTER_SDA_NUM,
        .scl_io_num = I2C_MASTER_SCL_NUM,
        .clk_source = I2C_CLK_SRC_DEFAULT,
        .glitch_ignore_cnt = I2C_GLITCH_CNT,
        .flags.enable_internal_pullup = true,
    };

    return i2c_new_master_bus(&i2c_master_config, i2c_bus);
}

// reads a register and modifies specific bits, then writes back into register
esp_err_t i2c_write_bits(i2c_master_dev_handle_t dev_handle, uint8_t reg_addr, uint8_t start_bit, size_t length, uint16_t value) {
    // get the value from the register
    esp_err_t status = ESP_OK;

    uint8_t data;
    status = i2c_master_transmit_receive(dev_handle, &reg_addr, 1, &data, 1, -1);
    if (status != ESP_OK) {
        ESP_LOGE(TAG, "Failed to retreive register value in i2c_write_bits");
        return status;
    }

    // clear the intended part of data
    if (start_bit + length >= 8) { 
        data &= ~(BIT_MASK(7, start_bit));
    } else {
        data &= ~(BIT_MASK(start_bit + length - 1, start_bit));
    }

    // set the value to the intended part of data
    data |= (value << start_bit);

    // write back to memory
    uint8_t write_buf[2] = {reg_addr, data};
    status = i2c_master_transmit(dev_handle, write_buf, 2, -1);
    if (status != ESP_OK) {
        ESP_LOGE(TAG, "Failed to write back to register in i2c_write_bits");
        return status;
    }

    return status;
}

