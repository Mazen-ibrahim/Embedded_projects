/******************************************************/
/******************************************************/
/***************  Author:Mazen Ibrahim   **************/
/***************  Layer:  MCAL           **************/
/***************  SWC: ADC               **************/
/***************  Version: 1.00           *************/
/******************************************************/
/******************************************************/

#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_

typedef struct
{
	u16 *Result;
	u8  *Channel;
	u8 Size;
	void(*NotificationFunc) (void);

}ADC_Chain;

/*********************************************************
Description:                                             
 Used To Initialize ADC Peripheral Depend on Config File            
**********************************************************/
void  ADC_VoidINIT(void);


/*********************************************************
Description:                                             
 Used to Start conversion of ADC and wait for Conversion 

Parameters: 
 Copy_u8Channel:To select Channel to Read from
 Copy_u8Reading: Pointer to variable to save Reading
 
Return:
 OK: No Error Happen
 NOK: Error Happen
**********************************************************/
u8 ADC_u8StartconversionSynch(u8 Copy_u8Channel ,  u16*Copy_u16Reading);


/*********************************************************
Description:                                             
 Used to Start conversion of ADC and no wait for Conversion 

Parameters: 
 Copy_u8Channel:To select Channel to Read from
 Copy_u8Reading: Pointer to variable to save Reading
 Copy_pvNotificationFunc:CallBack Function Called when Conversion Finish
 
Return:
 OK: No Error Happen
 NOK: Error Happen
 
Note:Must Enable Global Inturrpt Before Call This Function
**********************************************************/
u8 ADC_u8StartconversionAsynch(u8 Copy_u8Channel, u16*Copy_u16Reading, void(*Copy_pvNotificationFunc)(void));


/*********************************************************
Description:                                             
 Used to Start chain Conversion in ADC Channels 
 
Parameters: 
  ADC_Chain :Pointer to Struct Hold All Information Needed
**********************************************************/
u8 StartChainConversionAsynch(ADC_Chain *chain);

#endif
