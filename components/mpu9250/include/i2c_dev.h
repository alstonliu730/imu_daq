#ifndef __I2C_DEV_H__
#define __I2C_DEV_H__

#include "driver/i2c_types.h"
#include "esp_err.h"
#include "esp_types.h"
#include "sdkconfig.h"

#define I2C_MASTER_NUM          I2C_NUM_0
#define I2C_MASTER_SCL_NUM      CONFIG_I2C_MASTER_SCL
#define I2C_MASTER_SDA_NUM      CONFIG_I2C_MASTER_SDA
#define I2C_GLITCH_CNT          7
#define I2C_MASTER_FREQ_HZ      CONFIG_I2C_MASTER_FREQ
#define I2C_MASTER_TIMEOUT_MS   1000

extern i2c_master_bus_handle_t bus_handle;

/**
 * @brief I2C Master Initialization
 * 
 * Initializes the I2C Master Bus and returns the bus handler to the given parameter.
 * The following attributes are set for i2c master:
 * - port:              I2C_NUM_0
 * - sda pin:           21
 * - scl pin:           22
 * - clk src:           Default
 * - glitch_ignore:     7
 * - internal pullup:   enabled
 * 
 * @param i2c_bus [out] i2c master bus handler
 * 
 * @return An ESP error value
 */
esp_err_t i2c_master_init(i2c_master_bus_handle_t* i2c_bus);

/**
 * @brief Reads the register and changes certain bits of the value
 * 
 * Requests the data from the device and write specific bits of that value
 *  
 * @param dev_handle    The device handler
 * @param reg_addr      The register address that it reads
 * @param size          Size of the data read
 * @param start_bit     The starting bit
 * @param length        The number of bits that will be changed
 * @param value         Replacement bit value
 * 
 * @return An ESP error value
 */
esp_err_t i2c_write_bits(i2c_master_dev_handle_t dev_handle, uint8_t reg_addr, uint8_t start_bit, size_t length, uint16_t value);

#endif /* __I2C_DEV_H__*/