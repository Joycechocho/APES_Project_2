#include <weather.h>
#include "communication.h"
#include "I2C.h"

uint32_t humid_data;
uint32_t temp_data;

void weatherTask(void *pvParameters)
{
    for (;;)
    {
        sendHeartbeat(2);
        vTaskDelay(1000);

        humid_data = (int)I2C_Read_Humidity();
        if(humid_data < 0)
        {
            sendError(2, 1);
        }else{
            sendData(2, humid_data, 1);
        }
        vTaskDelay(500);

        temp_data = (int)I2C_Read_Temp();
        sendData(2, temp_data, 0);
        vTaskDelay(500);
    }
}
