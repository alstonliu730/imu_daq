#ifndef __MPU_9250_H__
#define __MPU_9250_H__

#include "common.h"
#include "esp_err.h"
#include "esp_types.h"

// Self Test Registers
#define IMU_SELF_TEST_X_GYRO        0x00
#define IMU_SELF_TEST_Y_GYRO        0x01
#define IMU_SELF_TEST_Z_GYRO        0x02
#define IMU_SELF_TEST_X_ACCEL       0x0D
#define IMU_SELF_TEST_Y_ACCEL       0x0E
#define IMU_SELF_TEST_Z_ACCEL       0x0F

// Gyrometer Offset Registers (16-bit)
#define IMU_XG_OFFSET_H             0x13
#define IMU_XG_OFFSET_L             0x14
#define IMU_YG_OFFSET_H             0x15
#define IMU_YG_OFFSET_L             0x16
#define IMU_ZG_OFFSET_H             0x17
#define IMU_ZG_OFFSET_L             0x18

// Accelerometer Offset Registers (16-bit)
#define IMU_XA_OFFSET_H             0x77
#define IMU_XA_OFFSET_L             0x78
#define IMU_YA_OFFSET_H             0x7A
#define IMU_YA_OFFSET_L             0x7B
#define IMU_ZA_OFFSET_H             0x7D
#define IMU_ZA_OFFSET_L             0x7E

// Configuration Registers
#define IMU_SMPLRT_DIV              0x19
#define IMU_CONFIG                  0x1A
#define IMU_GYRO_CONFIG             0x1B
#define IMU_ACCEL_CONFIG_1          0x1C
#define IMU_ACCEL_CONFIG_2          0x1D
#define IMU_LP_ACCEL_ODR            0x1E
#define IMU_WOM_THR                 0x1F

#define IMU_CFG_FIFO_MODE           BIT(6)
#define IMU_CFG_EXT_SYNC            BIT_MASK(5,3)
#define IMU_CFG_DLPF_CFG            BIT_MASK(2,0)

#define IMU_GYRO_X_STen             BIT(7)
#define IMU_GYRO_Y_STen             BIT(6)
#define IMU_GYRO_Z_STen             BIT(5)
#define IMU_GYRO_FS_SEL             BIT_MASK(4,3)
#define IMU_GYRO_FCHOICE_B          BIT_MASK(1,0)

#define IMU_ACCEL_X_STen            BIT(7)
#define IMU_ACCEL_Y_STen            BIT(6)
#define IMU_ACCEL_Z_STen            BIT(5)
#define IMU_ACCEL_FS_SEL            BIT_MASK(4,3)

#define IMU_ACCEL_FCHOICE_B         BIT(3)
#define IMU_ACCEL_DLPF_CFG          BIT_MASK(2,0)

// I2C Internal Registers
#define IMU_FIFO_EN                 0x23
#define IMU_I2C_MST_CTRL            0x24
#define IMU_I2C_SLV0_ADDR           0x25
#define IMU_I2C_SLV0_REG            0x26
#define IMU_I2C_SLV0_CTRL           0x27
#define IMU_I2C_SLV1_ADDR           0x28
#define IMU_I2C_SLV1_REG            0x29
#define IMU_I2C_SLV1_CTRL           0x2A
#define IMU_I2C_SLV2_ADDR           0x2B
#define IMU_I2C_SLV2_REG            0x2C
#define IMU_I2C_SLV2_CTRL           0x2D
#define IMU_I2C_SLV3_ADDR           0x2E
#define IMU_I2C_SLV3_REG            0x2F
#define IMU_I2C_SLV3_CTRL           0x30
#define IMU_I2C_SLV4_ADDR           0x31
#define IMU_I2C_SLV4_REG            0x32
#define IMU_I2C_SLV4_DO             0x33
#define IMU_I2C_SLV4_CTRL           0x34
#define IMU_I2C_SLV4_DI             0x35
#define IMU_I2C_MST_STATUS          0x36

#define IMU_I2C_SLV0_DO             0x63
#define IMU_I2C_SLV1_DO             0x64
#define IMU_I2C_SLV2_DO             0x65
#define IMU_I2C_SLV3_DO             0x66
#define IMU_I2C_MST_DELAY_CTRL      0x67

// Interrupt Configuration Registers
#define IMU_INT_PIN_CFG             0x37
#define IMU_INT_ENABLE              0x38
#define IMU_INT_STATUS              0x39

// Accelerometer Data Registers
#define IMU_ACCEL_XOUT_H            0x3B
#define IMU_ACCEL_XOUT_L            0x3C
#define IMU_ACCEL_YOUT_H            0x3D
#define IMU_ACCEL_YOUT_L            0x3E
#define IMU_ACCEL_ZOUT_H            0x3F
#define IMU_ACCEL_ZOUT_L            0x40

// Temperature Data Registers
#define IMU_TEMP_OUT_H              0x41
#define IMU_TEMP_OUT_L              0x42

// Gyrometer Data Registers
#define IMU_GYRO_XOUT_H             0x43
#define IMU_GYRO_XOUT_L             0x44
#define IMU_GYRO_YOUT_H             0x45
#define IMU_GYRO_YOUT_L             0x46
#define IMU_GYRO_ZOUT_H             0x47
#define IMU_GYRO_ZOUT_L             0x48

// Control Registers
#define IMU_SIG_PATH_RESET          0x68
#define IMU_MOT_DETECT_CTRL         0x69
#define IMU_USER_CTRL               0x6A
#define IMU_PWR_MGMT_1              0x6B
#define IMU_PWR_MGMT_2              0x6C
#define IMU_FIFO_COUNT_H            0x72
#define IMU_FIFO_COUNT_L            0x73
#define IMU_FIFO_R_W                0x74

// Power Managment Bit Mask & Configuration
#define IMU_PWR_H_RESET             BIT(7)
#define IMU_PWR_SLEEP               BIT(6)
#define IMU_PWR_CYCLE               BIT(5)
#define IMU_PWR_GYRO_STANDBY        BIT(4)
#define IMU_PWR_PDPTAT              BIT(3)
#define IMU_PWR_CLKSEL              BIT_MASK(2,0)

typedef enum  {
    internal_osc = 0,
    auto_select = 1,
    stop_clk = 7
} imu_pwr_clock_src;

typedef struct {
    float x,y,z;
} vector_t;

typedef struct {
    // accelerometer
    vector_t a_offset;
    vector_t a_scale_min;
    vector_t a_scale_max;

    // gyroscope
    vector_t g_offset;

    // magnetometer
    vector_t mag_adj;
} calibration_t;

// WHO AM I register
#define IMU_WHO_AM_I                0x75
#define IMU_WHO_AM_I_VALUE          0x68

// MPU9250 Configuration Values
#define MPU9250_DEV_ADDR            0x68
#define MPU9250_I2C_TIMEOUT         100

// Function Declarations
/**
 * @brief MPU9250 Sensor Initialization
 * 
 * Adds the MPU9250 sensor the i2c bus if it's initialized. If not, it will initialize the master bus setting 
 * using default configurations.
 * Resets the device and configures the gyroscope, accelerometer and the sampling rate.
 * 
 * @return An ESP error value
 */
esp_err_t mpu9250_init(void);

/**
 * @brief Reads raw entire frame data
 * 
 * @param frame_buf [out] Frame data including Accel, Temp, & Gyro
 * 
 * @return An ESP error value
 */
esp_err_t get_raw_frame(uint8_t* frame_buf);

/**
 * @brief Get Raw Acceleration data from MPU9250
 * 
 * @param accel_buf [out] Acceleration buffer written to
 * 
 * @return An ESP error value
 */
esp_err_t get_raw_accel(uint8_t* accel_buf);

/**
 * @brief Get Raw Gyroscope data from MPU9250
 * 
 * @param gyro_buf [out] Gyroscope data buffer written to
 * 
 * @return An ESP error value
 */
esp_err_t get_raw_gyro(uint8_t* gyro_buf);

/**
 * @brief Get Raw Temperature data from MPU9250
 * 
 * @param temp_buf [out] Temperature data buffer written to 
 * 
 * @return An ESP error value
 */
esp_err_t get_raw_temp(uint8_t* temp_buf);

/**
 * @brief Checks if the WHO AM I register is correct
 * 
 * @param whoami [out] `True` if the WHO AM I register is the default value
 * 
 * @return An ESP error value 
 */
esp_err_t verifyWhoAmI(bool* whoami);

/**
 * @brief Set the Sampling Rate Divider
 * 
 * @param div [in] Divider value to set sample rate
 * 
 * @return An ESP error value
 */
esp_err_t set_sample_rate_div(uint8_t div);

/**
 * @brief Get the Sampling Rate Divider
 * 
 * @param div [out] Divider value
 * 
 * @return An ESP error value
 */
esp_err_t get_sample_rate_div(uint8_t* div);

typedef enum {
    fifo_discard = 0,
    fifo_keep = 1
} mpu_fifo_mode;

/**
 * @brief Set the FIFO Mode in the Configuration Register
 * 
 * @param mode the fifo policy value
 * 
 * @return An ESP error value
 */
esp_err_t set_fifo_mode(mpu_fifo_mode mode);

/**
 * @brief Set Digital Low-Pass Filter Configuration
 * 
 * @param dlpf_cfg [in] DLPF Value Config
 * 
 * @return An ESP error value
 */
esp_err_t set_dlpf_cfg(uint8_t dlpf_cfg);

/**
 * @brief Prints the configuration settings
 */
void print_settings();

#endif /* __MPU_9250_H__ */