/*
 * UART.c
 *
 *  Created on: Apr 23, 2018
 *      Author: Srikant
 */




#include "UART.h"

//extern uint32_t g_ui32SysClock;

void ConfigureUART(void)
{
    /*Enabling the peripheral for UART*/
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);

    /*Enabling the UART peripheral*/
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART7);

    IntMasterDisable();


    /*Configuring the UART GPIO pins*/
    GPIOPinConfigure(GPIO_PC4_U7RX);
    GPIOPinConfigure(GPIO_PC5_U7TX);
    ROM_GPIOPinTypeUART(GPIO_PORTC_BASE, GPIO_PIN_4 | GPIO_PIN_5);

    /*Configuring the UART Baud Rate*/
   // UARTClockSourceSet(UART7_BASE, UART_CLOCK_PIOSC);
    ROM_UARTConfigSetExpClk(UART7_BASE, 32000000, 57600,(UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |
            UART_CONFIG_PAR_NONE));
    IntMasterEnable();
   IntEnable(INT_UART7);
    UARTIntEnable(UART7_BASE, UART_INT_RX);


}


void UART7IntHandler(void)
{
    uint32_t status;

    uint32_t value;

    status = UARTIntStatus(UART7_BASE,true);
    UARTIntClear(UART7_BASE, status);


        value = UARTCharGetNonBlocking(UART7_BASE);
        UARTprintf("receiving back %d\n",value);

}

