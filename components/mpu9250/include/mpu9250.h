#ifndef __MPU_9250_H__
#define __MPU_9250_H__

// Self Test Registers
#define IMU_SELF_TEST_X_GYRO        0x00
#define IMU_SELF_TEST_Y_GYRO        0x01
#define IMU_SELF_TEST_Z_GYRO        0x02
#define IMU_SELF_TEST_X_ACCEL       0x0D
#define IMU_SELF_TEST_Y_ACCEL       0x0E
#define IMU_SELF_TEST_Z_ACCEL       0x0F

// Gyrometer Offset Registers
#define IMU_XG_OFFSET_H             0x13
#define IMU_XG_OFFSET_L             0x14
#define IMU_YG_OFFSET_H             0x15
#define IMU_YG_OFFSET_L             0x16
#define IMU_ZG_OFFSET_H             0x17
#define IMU_ZG_OFFSET_L             0x18

// Accelerometer Offset Registers
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

// WHO AM I register
#define IMU_WHO_AM_I                0x75

#endif /* __MPU_9250_H__ */