/*
 * UART.h
 *
 *  Created on: Apr 23, 2018
 *      Author: Srikant
 */

#ifndef UART_H_
#define UART_H_

#include "driverlib/uart.h"
#include "utils/uartstdio.h"
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "inc/hw_ints.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include "driverlib/systick.h"


void ConfigureUART(void);
void UART7IntHandler(void);


#endif /* UART_H_ */
