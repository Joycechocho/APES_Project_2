#include <stdint.h>
#include <stdbool.h>
#include "drivers/pinout.h"
#include "utils/uartstdio.h"

// TivaWare includes
#include "driverlib/sysctl.h"
#include "driverlib/debug.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"

// FreeRTOS includes
#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#define HEARTBEAT_MSG 1
#define DATA_MSG      2

typedef enum task
{
    MAIN_TASK, //0
    PEDO_TASK,//1
    WEATHER_TASK,//2
    COMM_TASK
}Task;

//typedef struct task
//{
//    uint8_t MAIN_TASK =0 ;
//    uint8_t PEDO_TASK=1;
//    uint8_t WEATHER_TASK=2;
//    uint8_t COMM_TASK=3;
//}Task;

typedef enum type
{
    INIT, //0
    HEARTBEAT,
    DATA,//2
    ERROR
}Type;

//typedef struct type
//{
//    uint8_t INIT = 0;
//    uint8_t HEARTBEAT = 1;
//    uint8_t DATA = 2 ;
//    uint8_t ERROR = 3;
//}Type;

typedef enum data
{
    TEMPERATURE, //0
    HUMIDITY,
    PEDOMETER,
    NONE
}Data;

//typedef struct data
//{
//    uint8_t TEMPERATURE = 0;
//    uint8_t HUMIDITY = 1;
//    uint8_t PEDOMETER = 2;
//}Data;


typedef struct
{
    uint32_t     type;
    uint32_t    timestamp;
    Task        source;
    uint32_t    data;
    Data        sensor;
    size_t      length;
}message_t;

void communicationTask(void *pvParameters);
int8_t sendHeartbeat(Task task);
int8_t sendData(Task task, uint32_t data, Data sensor);
void UARTSend_7(const uint8_t *pui8Buffer, uint32_t ui32Count);
void UARTSend(const uint8_t *pui8Buffer, uint32_t ui32Count);

