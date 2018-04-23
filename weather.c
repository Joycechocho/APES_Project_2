#include <weather.h>
#include "communication.h"
#include "I2C.h"

uint32_t humid_data;
uint32_t temp_data;

void weatherTask(void *pvParameters)
{
    for (;;)
    {
        sendHeartbeat(WEATHER_TASK);
        vTaskDelay(1000);

        humid_data = (int)I2C_Read_Humidity();
        sendData(WEATHER_TASK, humid_data, HUMIDITY);
        vTaskDelay(3000);

        temp_data = (int)I2C_Read_Temp();
        sendData(WEATHER_TASK, temp_data, TEMPERATURE);
        vTaskDelay(3000);
    }
}
