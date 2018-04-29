#include "pedometer.h"
#include "pedometer_driver.h"
#include "communication.h"

uint32_t pedo_data;

void pedometerTask(void *pvParameters)
{
    I2C_write_pedometer();
    for (;;)
    {
//        UARTprintf("\n In Pedometer\n");

        sendHeartbeat(PEDO_TASK);
        vTaskDelay(1000);

        pedo_data = (uint32_t)I2C_Read_pedometer();
//        UARTprintf("\n PEDOMETER: %d\n",I2C_Read_pedometer());
        sendData(PEDO_TASK, pedo_data, PEDOMETER);
        vTaskDelay(1000);
    }
}
