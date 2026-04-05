# IMU Data Acquisition
In this project, we will use the ESP32 as a data acquisition controller that collects data from the IMU (MPU9250) through I2C protocols. This module would have the flexibility to add more sensors to read from. It exports the data through UART communication with a custom payload for the imu data. For my use case, this would be connected to a Raspberry Pi to use as data for part of a multi-modal system.

## Building the Project
When developing this project, we used the ESP-IDF VSCode Extension that requires you to set the version of ESP-IDF we are using, the method of flashing, the development port, and the device target.

## Usage

## Features

## Future Consideration
- [] Multiple Master Devices to Export Data
- [] Use SPI protocols to interact with sensors
- [] Wireless Protocols for asynchronous data collection