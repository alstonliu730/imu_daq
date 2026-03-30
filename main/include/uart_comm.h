#ifndef __UART_COMM_H__
#define __UART_COMM_H__

#include "esp_err.h"
#include "freertos/FreeRTOS.h"
#include "freertos/ringbuf.h"
#include "esp_types.h"
#include "sdkconfig.h"
#include "hal/uart_types.h"

#define TXD_PIN             (CONFIG_UART_TXD_PIN)
#define RXD_PIN             (CONFIG_UART_RXD_PIN)

#define UART_BUF_LEN        1024
// uart message struct
typedef struct uart_msg {
    size_t size;
    esp_err_t status;
    char* message;
} uart_msg_t;

// uart task parameters
typedef struct uart_params {
    size_t len;
    RingbufHandle_t buf;
} uart_params_t;

/**
 * @brief Initializes the UART drivers and pins using the polling method.
 * 
 * Configures the UART to an 8N1 Data Policy with parity disabled 
 *      and hardware flow control disabled.
 * It uses the `uart_driver_install` to create an RX Buffer and no TX buffer 
 *      with no event queue. 
 * 
 * @param uart_num The UART port number (UART_NUM_0 --> UART_NUM_MAX - 1)
 */
void init_uart_poll (void);

/**
 * @brief Handles the transmit task using a polling method
 * 
 * @param arg the pointer to the list of arguments
 */
void transmit_poll_task(void* arg);

/**
 * @brief Handles the receiving task using a polling method
 * 
 * @param arg the pointer to the list of arguments
 */
void receive_poll_task(void* arg);
#endif /* __UART_COMM_H__ */