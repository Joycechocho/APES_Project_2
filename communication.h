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
    PEDO_TASK,
    WEATHER_TASK,
    COMM_TASK
}Task;

typedef enum type
{
    INIT,
    HEARTBEAT,
    DATA,
    ERROR
}Type;

typedef enum data
{
    TEMPERATURE,
    HUMIDITY,
    PEDOMETER
}Data;


typedef struct
{
    Type        type;
    uint32_t    timestamp;
    Task        source;
    uint32_t    data;
    Data        sensor;
    size_t      length;
}message_t;

void communicationTask(void *pvParameters);
int8_t sendHeartbeat(Task task);
int8_t sendData(Task task, uint32_t data, Data sensor);

