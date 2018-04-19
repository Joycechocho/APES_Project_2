#include "humidity.h"
#include "communication.h"

uint32_t humid_data = 50;

void humidityTask(void *pvParameters)
{
    for (;;)
    {
//        UARTprintf("In humidity\n");

        sendHeartbeat(HUM_TASK);
        vTaskDelay(1000);


        sendData(HUM_TASK, humid_data);
        vTaskDelay(3000);
    }
}
