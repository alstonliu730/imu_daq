# Use GLOB to find source files in the main directory
file(GLOB MPU9250_SRCS "i2c_dev.c" "mpu9250.c" "*.c")

# Set the mpu9250 component
idf_component_register(SRCS ${MPU9250_SRCS}
                INCLUDE_DIRS "include"
                REQUIRES driver)