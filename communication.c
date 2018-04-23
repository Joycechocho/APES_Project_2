#include "communication.h"

extern QueueHandle_t heartbeat_queue;
extern QueueHandle_t data_queue;
extern TaskHandle_t xTask3;

void communicationTask(void *pvParameters)
{
    uint32_t notifyValue;
    message_t hb_msg;
    message_t data_msg;
    for (;;)
    {
        xTaskNotifyWait( pdFALSE, 0xFFFFFFFF, &notifyValue, portMAX_DELAY );
        if(notifyValue & HEARTBEAT_MSG)
        {
            xQueueReceive(heartbeat_queue, &hb_msg, 10);
            if(hb_msg.source == 1){
                UARTprintf("\n\r [HEARBEAT] from [PEDO_TASK] ");
            }else if(hb_msg.source == 2){
                UARTprintf("\n\r [HEARBEAT] from [WEATHER_TASK] ");
            }
        }if(notifyValue & DATA_MSG){
            xQueueReceive(data_queue, &data_msg, 10);
            if(data_msg.source == 1){
                UARTprintf("\n\r [PEDOMETER_DATA] from [PEDO_TASK] is %d", data_msg.data);
            }else if(data_msg.source == 2 && data_msg.sensor == HUMIDITY){
                UARTprintf("\n\r [HUMIDITY_DATA] from [WEATHER_TASK] is %d (percentage)", data_msg.data);
            }else if(data_msg.source == 2 && data_msg.sensor == TEMPERATURE){
                UARTprintf("\n\r [TEMPERATURE_DATA] from [WEATHER_TASK] is %d (degree celsius)", data_msg.data);
            }
        }
    }
}

int8_t sendHeartbeat(Task task)
{
    message_t msg;
    msg.type = HEARTBEAT;
    msg.timestamp = 0;
    msg.source = task;

    msg.data = 0;
    msg.sensor = 0;
    msg.length = 0;
    if(pdPASS != xQueueSend(heartbeat_queue, (void*)&msg, 10))
    {
        UARTprintf("\r\nHeartBeat sending failed");
        return -1;
    }
    xTaskNotify(xTask3, HEARTBEAT_MSG, eSetBits);
    return 0;
}

int8_t sendData(Task task, uint32_t data, Data sensor)
{
    message_t msg;
    msg.type = DATA;
    msg.timestamp = 0;
    msg.source = task;

    msg.data = data;
    msg.sensor = sensor;
    msg.length = 0;
    if(pdPASS != xQueueSend(data_queue, (void*)&msg, 10))
    {
        UARTprintf("\r\nData sending failed");
        return -1;
    }
    xTaskNotify(xTask3, DATA_MSG, eSetBits);
    return 0;
}
