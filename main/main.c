/**
 * 
 */

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "uart_comm.h"

void app_main(void)
{   
    init_uart_poll();
}