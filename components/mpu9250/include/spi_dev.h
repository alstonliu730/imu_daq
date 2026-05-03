#ifndef __SPI_DEV_H__
#define __SPI_DEV_H__

#include "driver/spi_master.h"
#include "esp_err.h"
#include "esp_types.h"
#include "common.h"

esp_err_t spi_master_initialize(spi_host_device_t host);

#endif /* __SPI_DEV_H__ */