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

#define HEARTBEAT_MSG  1
#define DATA_MSG       2
#define ERROR_MSG      3

typedef enum task
{
    MAIN_TASK, //0
    PEDO_TASK,//1
    WEATHER_TASK,//2
    COMM_TASK
}Task;

typedef enum type
{
    INIT, //0
    HEARTBEAT,
    DATA,//2
    ERROR
}Type;

typedef enum data
{
    TEMPERATURE, //0
    HUMIDITY,
    PEDOMETER,
    NONE
}Data;


typedef struct
{
    uint32_t         type;  //0: init, 1: hb, 2: data, 3: error
    uint32_t         timestamp;
    uint32_t         source; //1: pedo task, 2: weather task
    uint32_t         data;
    uint32_t         sensor; //0: temp, 1: humidity, 2: pedo, 3: none
    size_t           length;
}message_t;

void communicationTask(void *pvParameters);
int8_t sendHeartbeat(uint32_t task);
int8_t sendData(uint32_t task, uint32_t data, uint32_t sensor);
int8_t sendError(uint32_t task, uint32_t sensor);
void UARTSend_7(const uint8_t *pui8Buffer, uint32_t ui32Count);
void UARTSend(const uint8_t *pui8Buffer, uint32_t ui32Count);

