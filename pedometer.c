#include "pedometer.h"
#include "communication.h"

uint32_t pedo_data = 20;

void pedometerTask(void *pvParameters)
{
    for (;;)
    {
//        UARTprintf("In Pedometer\n");

        sendHeartbeat(PEDO_TASK);
        vTaskDelay(1000);

        sendData(PEDO_TASK, pedo_data, PEDOMETER);
        vTaskDelay(3000);
    }
}
