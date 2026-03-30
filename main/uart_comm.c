/**
 * Author: Alston Liu
 * 
 * Description: Enables the UART to communicate with a different platform. This source file defines the functions that will be used in the app main.
 */

#include "uart_comm.h"
#include "freertos/FreeRTOS.h"
#include "sdkconfig.h"
#include "driver/uart.h"
#include "string.h"
#include "esp_err.h"
#include "esp_log.h"
#include "freertos/semphr.h"
#include "imu_reader.h"

static const int RX_BUF_SIZE = 2048;
static const int TX_BUF_SIZE = 2048;

static uart_params_t imu_uart;
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
void init_uart_poll (void) {
    // Set the default configuration 
    const uart_config_t uart_config = {
        .baud_rate = CONFIG_UART_BAUD_RATE,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_DEFAULT,
    };


    // No event queue for the interrupts
    ESP_ERROR_CHECK(uart_driver_install(UART_NUM_1, 
                    RX_BUF_SIZE, 
                    TX_BUF_SIZE, 
                    0, 
                    NULL, 
                    0));

    // set communication configuration
    ESP_ERROR_CHECK(uart_param_config(UART_NUM_1, &uart_config));
    
    // set communication pins
    ESP_ERROR_CHECK(uart_set_pin(UART_NUM_1, 
                        TXD_PIN, 
                        RXD_PIN, 
                        UART_PIN_NO_CHANGE, 
                        UART_PIN_NO_CHANGE));
    
    // uart parameter initialization
    imu_uart.buf = xRingbufferCreateNoSplit(sizeof(imu_payload_t), UART_BUF_LEN);
    imu_uart.len = UART_BUF_LEN;

    // Spawn the transmit task with polling
    xTaskCreate(transmit_poll_task, "uart_tx_poll", CONFIG_TASK_STACK_SIZE, NULL, 5, NULL);
}

/**
 * @brief Handles the transmit task using a polling method
 * 
 * User will need to provide the buffer that the task will read off of. 
 * @param arg pointer to the arguments
 */
void transmit_poll_task(void* arg) {
    // set the logging task tag
    static const char *TX_TASK_TAG = "TX_POLL_TASK";
    esp_log_level_set(TX_TASK_TAG, ESP_LOG_INFO);
    ESP_LOGI(TX_TASK_TAG, "Transmit Polling Task started");
    
    // check arguments for buffer
    if (imu_uart.len == 0) {
        ESP_LOGE(TX_TASK_TAG, "There's no input buffer given in the transmit task.");
    }

    while (1) {
        // check and read the buffer
        if (imu_uart.len != 0) {
            // send the data to the transmit buffer
            uart_write_bytes(UART_NUM_1, imu_uart.buf, imu_uart.len);

            // delay for a bit
            vTaskDelay(2000 / portTICK_PERIOD_MS);
        }
    }
}

/**
 * @brief Handles the receiving task using a polling method
 * 
 * @param arg the pointer to the list of arguments
 */
void receive_poll_task(void* arg) {
    // set the logging task tag
    static const char* RX_TASK_TAG = "RX_POLL_TASK";
    esp_log_level_set(RX_TASK_TAG, ESP_LOG_INFO);
    ESP_LOGI(RX_TASK_TAG, "Receive Task started");

    // check arguments for buffer

}