#include <weather.h>
#include "communication.h"
#include "I2C.h"

int32_t humid_data;
int32_t temp_data;

void weatherTask(void *pvParameters)
{
    for (;;)
       {
           vTaskDelay(1000);
           sendHeartbeat(2);

           humid_data = (int)I2C_Read_Humidity();

           if(humid_data < 0)
           {
               sendError(2, 1);
           }else{
               sendData(2, humid_data, 1);
           }
           vTaskDelay(500);

           temp_data = (int)I2C_Read_Temp();
           if(temp_data < 0)
           {
               sendError(2, 0);
           }else{
               sendData(2, temp_data, 0);
           }
           vTaskDelay(500);
       }
//    for (;;)
//    {
//        sendHeartbeat(WEATHER_TASK);
//        vTaskDelay(1000);
//        humid_data = (int)I2C_Read_Humidity();
//        if(humid_data <0)
//        {
//            sendError(2,1);
//        }else{
//            sendData(2,humid_data,1);
//        }
//
////        sendData(WEATHER_TASK, humid_data, HUMIDITY);
//        vTaskDelay(500);
//
//        temp_data = (int)I2C_Read_Temp();
//        sendData(WEATHER_TASK, temp_data, TEMPERATURE);
//        vTaskDelay(500);
//    }
}
