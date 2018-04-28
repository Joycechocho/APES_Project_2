#include "pedometer_driver.h"


uint8_t Config_Data = 0;
uint8_t Pedo_MSB = 0;
uint8_t Pedo_LSB = 0;
uint16_t Pedo_data;


void I2C_write_pedometer()
{
	/*Specifying address of slave device and write mode*/
	I2CMasterSlaveAddrSet(I2C0_BASE, SLAVE_ADDR, false);
	Config_Data = 0;
	Config_Data |=  LSM6DS3_ACC_GYRO_FS_XL_2g;
	Config_Data |=	LSM6DS3_ACC_GYRO_ODR_XL_26Hz;



	/*Setting the control byte to be sent to the slave*/
	I2CMasterDataPut(I2C0_BASE, LSM6DS3_ACC_GYRO_CTRL1_XL);
    I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_START);

	/*Waiting till transaction is finished*/
	while(I2CMasterBusy(I2C0_BASE));



	I2CMasterDataPut(I2C0_BASE, Config_Data);
    I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_FINISH);

	while(I2CMasterBusy(I2C0_BASE));




	I2CMasterDataPut(I2C0_BASE, LSM6DS3_ACC_GYRO_CTRL10_C);
    I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_START);

	while(I2CMasterBusy(I2C0_BASE));




	I2CMasterDataPut(I2C0_BASE, PEDO_RESET);
    I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_FINISH);
	
	while(I2CMasterBusy(I2C0_BASE));



	I2CMasterDataPut(I2C0_BASE, LSM6DS3_ACC_GYRO_TAP_CFG1);
    I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_START);
	
	while(I2CMasterBusy(I2C0_BASE));


	I2CMasterDataPut(I2C0_BASE, PEDO_EN);

    I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_FINISH);
	
	while(I2CMasterBusy(I2C0_BASE));



	I2CMasterDataPut(I2C0_BASE, LSM6DS3_ACC_GYRO_INT1_CTRL);
    I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_START);
	
	while(I2CMasterBusy(I2C0_BASE));



	I2CMasterDataPut(I2C0_BASE, INT_PIN);
    I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_FINISH);
	
	while(I2CMasterBusy(I2C0_BASE));

	// /*Setting to read the values from slave*/
	// I2CMasterSlaveAddrSet(I2C0_BASE, SLAVE_ADDR, true);

	/*Sending the control byte and reading from the register*/

}


uint16_t I2C_Read_pedometer()
{

    I2CMasterSlaveAddrSet(I2C0_BASE, SLAVE_ADDR, false);



	I2CMasterDataPut(I2C0_BASE, LSM6DS3_ACC_GYRO_STEP_COUNTER_H);
	I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_SINGLE_SEND);
	while(I2CMasterBusy(I2C0_BASE));
	I2CMasterSlaveAddrSet(I2C0_BASE, SLAVE_ADDR, true);

	I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_SINGLE_RECEIVE);

	while(I2CMasterBusy(I2C0_BASE));


	Pedo_MSB = I2CMasterDataGet(I2C0_BASE);
    while(I2CMasterBusy(I2C0_BASE));

	I2CMasterSlaveAddrSet(I2C0_BASE, SLAVE_ADDR, false);

	I2CMasterDataPut(I2C0_BASE, LSM6DS3_ACC_GYRO_STEP_COUNTER_L);
    I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_SINGLE_SEND);
	
	while(I2CMasterBusy(I2C0_BASE));
    I2CMasterSlaveAddrSet(I2C0_BASE, SLAVE_ADDR, true);

	I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_SINGLE_RECEIVE);

    while(I2CMasterBusy(I2C0_BASE));
    //I2CMasterDataGet(I2C0_BASE);

	Pedo_LSB = I2CMasterDataGet(I2C0_BASE);
	while(I2CMasterBusy(I2C0_BASE));

	Pedo_data = ((uint16_t)(Pedo_MSB<<8) + (Pedo_LSB));

	return Pedo_data;
}

