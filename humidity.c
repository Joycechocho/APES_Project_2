#include "humidity.h"
#include "communication.h"

void humidityTask(void *pvParameters)
{
    for (;;)
    {
//        UARTprintf("In humidity\n");

        sendHeartbeat(HUM_TASK);
        vTaskDelay(1000);
    }
}
