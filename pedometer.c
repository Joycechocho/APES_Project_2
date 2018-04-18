#include "pedometer.h"
#include "communication.h"

void pedometerTask(void *pvParameters)
{
    for (;;)
    {
//        UARTprintf("In Pedometer\n");

        sendHeartbeat(PEDO_TASK);
        vTaskDelay(1000);
    }
}
