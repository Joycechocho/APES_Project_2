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

typedef enum task
{
    MAIN_TASK, //0
    PEDO_TASK,
    HUM_TASK,
    COMM_TASK
}Task;

typedef enum type
{
    INIT,
    HEARTBEAT,
    DATA,
    ERROR
}Type;

typedef struct
{
    Type        type;
    uint32_t    timestamp;
    Task        source;
    uint8_t     message;
    size_t      length;
}message_t;

void communicationTask(void *pvParameters);
int8_t sendHeartbeat(Task task);

