#include "communication.h"
#include "UART.h"

extern QueueHandle_t heartbeat_queue;
extern QueueHandle_t data_queue;
extern QueueHandle_t error_queue;
extern TaskHandle_t xTask3;

void communicationTask(void *pvParameters)
{
    uint32_t notifyValue;
    message_t hb_msg;
    message_t data_msg;
    message_t error_msg;
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
        }else if(notifyValue & DATA_MSG)
        {
            xQueueReceive(data_queue, &data_msg, 10);
            if(data_msg.source == 1){
                UARTprintf("\n\r [PEDOMETER_DATA] from [PEDO_TASK] is %d", data_msg.data);
            }else if(data_msg.source == 2 && data_msg.sensor == HUMIDITY){
                UARTprintf("\n\r [HUMIDITY_DATA] from [WEATHER_TASK] is %d (percentage)", data_msg.data);
            }else if(data_msg.source == 2 && data_msg.sensor == TEMPERATURE){
                UARTprintf("\n\r [TEMPERATURE_DATA] from [WEATHER_TASK] is %d (degree celsius)", data_msg.data);
            }
        }else if(notifyValue & ERROR_MSG)
        {
            xQueueReceive(error_queue, &error_msg, 10);
            if(hb_msg.source == 1){
                if(data_msg.sensor == 0)
                {
                    UARTprintf("\n\r [FATAL ERROR] Cannot read temperature data");
                }
            }else if(hb_msg.source == 2){
                if(data_msg.sensor == 1)
                {
                    UARTprintf("\n\r [FATAL ERROR] Cannot read humidity data");
                }else if(data_msg.sensor == 2){
                    UARTprintf("\n\r [FATAL ERROR] Cannot read pedometer data");
                }
            }
        }
    }
}

int8_t sendHeartbeat(uint32_t task)
{
    message_t msg;
    msg.type = 1;
    msg.timestamp = 0;
    msg.source = task;

    msg.data = 0;
    msg.sensor = 3;
    msg.length = 0;
    UARTSend_7((uint8_t*)&msg, sizeof(msg));
    if(pdPASS != xQueueSend(heartbeat_queue, (void*)&msg, 10))
    {
        UARTprintf("\r\nHeartBeat sending failed");
        return -1;
    }
    xTaskNotify(xTask3, HEARTBEAT_MSG, eSetBits);
    return 0;
}

int8_t sendData(uint32_t task, uint32_t data, uint32_t sensor)
{
    message_t msg;
    msg.type = 2;
    msg.timestamp = 0;
    msg.source = task;

    msg.data = data;
    msg.sensor = sensor;
    msg.length = 0;
    UARTSend_7((uint8_t*)&msg, sizeof(msg));
    UARTSend((uint8_t*)&msg, sizeof(msg));
    if(pdPASS != xQueueSend(data_queue, (void*)&msg, 10))
    {
        char *error = "Data sending failed";
        UARTSend_7((uint8_t*)&error, sizeof(error));
        UARTprintf("\r\nData sending failed");
        return -1;
    }
    xTaskNotify(xTask3, DATA_MSG, eSetBits);
    return 0;
}

int8_t sendError(uint32_t task, uint32_t sensor)
{
    message_t msg;
    msg.type = 3; //3: ERROR
    msg.timestamp = 0;
    msg.source = task;

    msg.data = 999;
    msg.sensor = sensor;
    msg.length = 0;
    UARTSend_7((uint8_t*)&msg, sizeof(msg));
    if(pdPASS != xQueueSend(error_queue, (void*)&msg, 10))
    {
        UARTprintf("\r\Error sending failed");
        return -1;
    }
    xTaskNotify(xTask3, ERROR_MSG, eSetBits);
    return 0;
}


void UARTSend_7(const uint8_t *pui8Buffer, uint32_t ui32Count)
{
    while(ui32Count--)
    {
        UARTCharPutNonBlocking(UART7_BASE, *pui8Buffer++);
//        UARTCharPut(UART7_BASE, *pui8Buffer++);
    }
}

void UARTSend(const uint8_t *pui8Buffer, uint32_t ui32Count)
{
    while(ui32Count--)
    {
        UARTCharPutNonBlocking(UART0_BASE, *pui8Buffer++);
//        UARTCharPut(UART7_BASE, *pui8Buffer++);
    }
}


