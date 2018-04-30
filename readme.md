# Project 2 #

Team Member: Joyce Cho, Srikant Gaikwad

## Architecture Diagram ##

![alt text](https://github.com/Joycechocho/APES_Project_2/blob/master/img/APES_Project2.jpg)

## Features Implemented ##

### TIVA TM4C129 (FreeRTOS) ###
*  Heartbeat (using Queue and TaskNotify)

    * From Pedometer Task to Communication Task
  
    * From Weather Task to Communication Task

*  IPC (using Queue and TaskNotify)

    * From Pedometer Task to Communication Task

    * From Weather Task to Communication Task

*  Sensor Integration 
 
    * I2C is integrated to retrieve the temperature and humidity data 
    
    * I2C is integrated to retrieve the pedometer data from pedometer sensor
    
*  UART Communication

    * Configuration for TX
    
    * UART7 Interrupt Handler for RX
    
### Beaglebone Green ###

*  UART Communication

    * Configuration for RX
    
    * Sending ACK back to TIVA after receiving the message

*  IPC 

    * Message Queue is used to transmitted the message to logger task after receiving it at UART

*  Singal Hanlder
    
