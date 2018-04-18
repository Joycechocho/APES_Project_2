#include "communication.h"

extern QueueHandle_t heartbeat_queue;
extern TaskHandle_t xTask3;

void communicationTask(void *pvParameters)
{
    uint32_t notifyValue;
    message_t hb_msg;
    for (;;)
    {
//        UARTprintf("In communication\n");

        xTaskNotifyWait( pdFALSE, 0xFFFFFFFF, &notifyValue, portMAX_DELAY );
        if(notifyValue & HEARTBEAT_MSG)
        {
            xQueueReceive(heartbeat_queue, &hb_msg, 10);
            if(hb_msg.source == 1){
                UARTprintf("\n\r [HEARBEAT] from [PEDO_TASK] ");
            }else if(hb_msg.source == 2){
                UARTprintf("\n\r [HEARBEAT] from [HUMID_TASK] ");
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

    msg.message = 0;
    msg.length = 0;
    if(pdPASS != xQueueSend(heartbeat_queue, (void*)&msg, 10))
    {
        UARTprintf("\r\nHeartBeat sending failed");
        return -1;
    }
    xTaskNotify(xTask3, HEARTBEAT_MSG, eSetBits);
    return 0;
}
