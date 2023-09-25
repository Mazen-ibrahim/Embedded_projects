/******************************************************/
/******************************************************/
/***************  Author:Mazen Ibrahim   **************/
/***************  Layer:  MCAL           **************/
/***************  SWC: SPI               **************/
/***************  Version: 1.00           *************/
/******************************************************/


#ifndef SPI_INTERFACE_H_
#define SPI_INTERFACE_H_


/*
Description: Function Used to Initialize SPI Master Base on Config file
Parameters: void
Return: void
*/
void SPI_void_MasterInit();


/*
Description: Function Used to Initialize SPI Slave Base on Config file
Parameters: void
Return: void
*/
void SPI_void_SlaveInit();


/*
Description: Function Used to Send Data From Master and Recieve Data From Slave Depend on Busy Waiting
Parameters: Data Send From Master
Return: Data Receive From Slave
*/
u8 SPI_u8_Synctransceive(u8 copy_u8Data);



/*
Description: Function Used to Send Data From Master and Recieve Data From Slave Depend on Interrupt
Parameters: Data Send From Master
Return: Data Receive From Slave
*/
void SPI_u8_Asynctransceive(u8 copy_u8Data);



/*
Description: Fuctnion Used To Enabel SPI Interrupt
Parameters: void
Return: void 
*/
void SPI_void_EnableInterrupt();


/*
Description: Fucntion Used To Disable SPI Interrupt
Parameters: void 
Return: void
*/
void SPI_void_DisableInterrupt();


/*
Description: Fucntion Used To Set CallBack Fucntion to Execute When SPI Interrupt Happen
Parameters: Pointer to Variable To Hold SPI Data , Pointer to Fucntion To Hold Notification Fucntion
Return: 
  1-NULL_POINTER 
  2-SPI_OK
  3-SPI_NOK
*/
u8 SPI_NotificationFucntion(u8 *Copy_u8Value , void(*SPI_CallBackFucntion)(void));


#endif
