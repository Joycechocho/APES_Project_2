## Environmental Sensing Systems
### Final project in "Advanced Practical Embedded Software Design" class at University of Colorado Boulder
Team Member: Joyce Cho, Srikant Gaikwad

## Project Description ##
The TIVA board running FreeRTOS is connected with two sensors: Pedometer sensor and Humidity sensor. Passing the sensor through UART, the BeagleBone Green board is receiving the data acts as a remote logging server for the TIVA board.

## Contribution ##
* Wrote a multithreaded c-program using the FreeRTOS on the TIVA development kit
* Learned to port an Embedded OS to a ARM supported architecture
* Utilized HAL libraries to interface with peripherals
* Created a communication interface from one Embedded System to another

## Architecture Diagram ##

![alt text](https://github.com/Joycechocho/APES_Project_2/blob/master/img/APES_Project2.jpg)

## Sensors
SI7021 Sensor for Humidity and Temperature

LSM6DS3 Pedometer Sensor


## Features Implemented ##

### TIVA TM4C129 (FreeRTOS) ###
#### Sensor/Device Tasks
1. Sensor tasks that sit on top of a peripheral driver library to knows the proper protocol for talking to the sensor itself. 
2. Intertask communication includes the use of queues, task event notifications, interrupt callback functions and synchronization devices.
    
### Beaglebone Green ###

#### Communication Interface: 
1. This thread handles the communication interface connection. It takes different messages and route them appropriately on the BeagleBone Green. 
2. This task is able to issue and receive remote API calls to the client device. 
3. This task is making sure the Tiva is alive (heartbeats) and logs when connections are lost or no heartbeat is received. 

#### Logging: 
1. This task reports on information about the status of the server, new connection requests, new worker client threads particular to log based messages. 
2. File handles is tracked and data is be logged to the file.

### Message API
* Heartbeat Messages between Server and Client
* Log Messages between Server and Client
* Data Integrity for messages between server and client (checksums)
* Status Messaging (Initialization, Errors, etc)
* Client Information (Board Type, Code Version, Unique Identifier, etc)

    
