/*
 * I2C.h
 *
 *  Created on: Apr 21, 2018
 *      Author: Srikant
 */

#ifndef I2C_H_
#define I2C_H_

#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "inc/hw_i2c.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "driverlib/i2c.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"

#define SLAVE_ADDR 0x40
#define REG_VALUE_HUMID 0xE5
#define REG_VALUE_TEMP 0xE3

float I2C_Read_Humidity();
float I2C_Read_Temp();

int8_t Init_I2C(void);

#endif /* I2C_H_ */
