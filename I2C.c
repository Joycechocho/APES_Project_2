#include "I2C.h"


uint32_t Humid_data = 0;
uint32_t Humid_MSB = 0;
uint32_t Humid_LSB = 0;
float Humid_C;

uint32_t Temp_data = 0;
uint32_t Temp_MSB = 0;
uint32_t Temp_LSB = 0;
float Temp_C;
  
uint8_t Init_I2C(void)
{
	/*Enable the I2C*/
	SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C0);

	/*Reset the module*/
	SysCtlPeripheralReset(SYSCTL_PERIPH_I2C0);

	/*Enabling GPIO port B*/
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);

	/*Muxing the pins for SDA and SCL*/
	GPIOPinConfigure(GPIO_PB2_I2C0SCL);
	GPIOPinConfigure(GPIO_PB3_I2C0SDA);

	/*Setting the pins for I2C*/
	GPIOPinTypeI2CSCL(GPIO_PORTB_BASE, GPIO_PIN_2);
	GPIOPinTypeI2C(GPIO_PORTB_BASE, GPIO_PIN_3);

	/*Setting the I2C transfer rate*/
	I2CMasterInitExpClk(I2C0_BASE, 32000000U, false);
return 0;
}


float I2C_Read_Humidity()
{
	/*Specifying address of slave device and write mode*/
	I2CMasterSlaveAddrSet(I2C0_BASE, SLAVE_ADDR, false);

    I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_SINGLE_SEND);

	/*Setting the control byte to be sent to the slave*/
	I2CMasterDataPut(I2C0_BASE, REG_VALUE_HUMID);

	/*Waiting till transaction is finished*/
	while(I2CMasterBusy(I2C0_BASE));

	/*Setting to read the values from slave*/
	I2CMasterSlaveAddrSet(I2C0_BASE, SLAVE_ADDR, true);

	/*Sending the control byte and reading from the register*/
	I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_RECEIVE_START);

	while(I2CMasterBusy(I2C0_BASE));


	Humid_MSB = I2CMasterDataGet(I2C0_BASE);

	I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_RECEIVE_FINISH);

	while(I2CMasterBusy(I2C0_BASE));

	//I2CMasterDataGet(I2C0_BASE);

	 Humid_LSB = I2CMasterDataGet(I2C0_BASE);

	Humid_data = ((Humid_MSB<<8) + (Humid_LSB));

	Humid_C = ((125.0*Humid_data)/65536.0)-6;

	return Humid_C;
}



float I2C_Read_Temp()
{
    /*Specifying address of slave device and write mode*/
    I2CMasterSlaveAddrSet(I2C0_BASE, SLAVE_ADDR, false);

    I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_SINGLE_SEND);

    /*Setting the control byte to be sent to the slave*/
    I2CMasterDataPut(I2C0_BASE, REG_VALUE_TEMP);

    /*Waiting till transaction is finished*/
    while(I2CMasterBusy(I2C0_BASE));

    /*Setting to read the values from slave*/
    I2CMasterSlaveAddrSet(I2C0_BASE, SLAVE_ADDR, true);

    /*Sending the control byte and reading from the register*/
    I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_RECEIVE_START);

    while(I2CMasterBusy(I2C0_BASE));


    Temp_MSB = I2CMasterDataGet(I2C0_BASE);

    I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_RECEIVE_FINISH);

    while(I2CMasterBusy(I2C0_BASE));

    //I2CMasterDataGet(I2C0_BASE);

     Temp_LSB = I2CMasterDataGet(I2C0_BASE);

    Temp_data = ((Temp_MSB<<8) + (Temp_LSB & 0xFC));

    Temp_C = ((175.72*Temp_data)/65536.0)-46.85;

    return Temp_C;
}
