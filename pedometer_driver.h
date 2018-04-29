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

#define SLAVE_ADDR 0x6B
#define LSM6DS3_ACC_GYRO_CTRL1_XL 0x10
#define LSM6DS3_ACC_GYRO_CTRL10_C 0x19
#define PEDO_RESET	0x3E
#define LSM6DS3_ACC_GYRO_FS_XL_2g 0x00
#define LSM6DS3_ACC_GYRO_ODR_XL_26Hz 0x20
#define LSM6DS3_ACC_GYRO_TAP_CFG1 0x58
#define PEDO_EN	0x40
#define LSM6DS3_ACC_GYRO_INT1_CTRL	0x0D
#define INT_PIN	0x10
#define LSM6DS3_ACC_GYRO_STEP_COUNTER_H 0x4C
#define LSM6DS3_ACC_GYRO_STEP_COUNTER_L	0x4B
void I2C_Read_Pedometer();
uint16_t I2C_write_Pedometer();


#endif /* I2C_H_ */
