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

#include "communication.h"
#include "pedometer.h"
#include "humidity.h"
#include "main.h"

QueueHandle_t heartbeat_queue;
QueueHandle_t data_queue;

TaskHandle_t xTask3;

// Main function
int main(void)
{
    // Initialize system clock to 120 MHz
    uint32_t output_clock_rate_hz;
    output_clock_rate_hz = ROM_SysCtlClockFreqSet(
                               (SYSCTL_XTAL_25MHZ | SYSCTL_OSC_MAIN |
                                SYSCTL_USE_PLL | SYSCTL_CFG_VCO_480),
                               SYSTEM_CLOCK);
    ASSERT(output_clock_rate_hz == SYSTEM_CLOCK);

    // Set up the UART which is connected to the virtual COM port
    UARTStdioConfig(0, 57600, SYSTEM_CLOCK);

    // Initialize the GPIO pins for the Launchpad
    PinoutSet(false, false);

    heartbeat_queue = xQueueCreate(10, sizeof(message_t));
    data_queue = xQueueCreate(10, sizeof(message_t));

    // Create demo tasks
    xTaskCreate(pedometerTask, (const portCHAR *)"Pedometer",
                configMINIMAL_STACK_SIZE, NULL, 1, NULL);

    xTaskCreate(humidityTask, (const portCHAR *)"Humidity",
                configMINIMAL_STACK_SIZE, NULL, 1, NULL);

    xTaskCreate(communicationTask, (const portCHAR *)"Communication",
                configMINIMAL_STACK_SIZE, NULL, 1,  &xTask3);

    vTaskStartScheduler();
    return 0;
}


void __error__(char *pcFilename, uint32_t ui32Line)
{
    // Place a breakpoint here to capture errors until logging routine is finished
    while (1)
    {
    }
}
