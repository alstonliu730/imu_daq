#ifndef __IMU_READER_H__
#define __IMU_READER_H__

#include <esp_types.h>

typedef struct imu_payload{
    uint16_t source_id;
    uint32_t timestamp;
    float   quarternion[4];
    float   linear_acc[3];
} imu_payload_t;


#endif /* __IMU_READER_H__ */