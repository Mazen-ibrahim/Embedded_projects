/***************************************************************************************/
/****************************  IMT School Training Center ******************************/
/***************************************************************************************/
/** This file is developed by IMT School training center, All copyrights are reserved **/
/***************************************************************************************/
/* Description ! Keypad driver for 4x4 keypad                                          */
/* Release Date! 28/6/2016                                                             */
/* Version     ! V01                                                                   */
/***************************************************************************************/


/********************************** Header Files INCLUSIONS ****************************/

/******************* Include Library   ****************/
#include "STD_TYPES.h"
#include <util/delay.h>
/******************************************************/

/******************* Include MCAL *********************/
#include "DIO_private.h"
#include "DIO_inteface.h"
/******************************************************/

#include "KPD_interface.h"
/***************************************************************************************/

/************* KeyPad Key Index ***************/                         
/*         Col_3    Col_2   Col_1   Col_0     */
/*	                                          */
/* row_0      1        2       3       4      */
/*	                                          */
/* row_1  	  5        6       7       8      */
/*	                                          */
/* row_2	  9        10      11      12     */
/*	                                          */
/* row_3	  13       14      15      16     */
/**********************************************/


/*************************************** Constants *************************************/
/* Values of the Key Pad switches                                                      */
/* Matrix is not standard it depends on the connection between the Micro and KeyPad    */
const u8 KPD_au8SwitchVal[4][4] =
{
  { 0x04, 0x08, 0x0C, 0x10 },
  { 0x03, 0x07, 0x0B, 0x0F },
  { 0x02, 0x06, 0x0A, 0x0E },
  { 0x01, 0x05, 0x09, 0x0D } 
};

/***************************************************************************************/


/***************************************** Macros **************************************/
#define PORT DIO_u8PORTD

#define COL_INIT   0

#define COL_FIN    4

#define ROW_INIT   4

#define ROW_FIN    8

#define NOT_PRESSED    0
/***************************************************************************************/


/***************************************************************************************/
/* Description! Interface to get the ID of the pressed key, return 0 incase no key     */
/*              is pressed, this function doesn't handle the sitaution if 2 keys are   */
/*              pressed at the same time                               	     		   */
/* Input      ! Nothing                                                                */
/* Output     ! Nothing                                                                */
/***************************************************************************************/
u8 KPD_u8GetPressedKey(void)
{

  u8 LOC_u8Column;

  u8 LOC_u8Row;

  /* Initialize the switch status to NOT Pressed                                                                     */
  u8 LOC_u8Retrun = NOT_PRESSED;

  /* Looping on columns of the Key Pad                                                                               */
  for (LOC_u8Column = 0 + COL_INIT; LOC_u8Column < COL_FIN; LOC_u8Column++)
  {
    /* Activate the Column                                                                                           */
    DIO_u8SetPinValue(PORT, LOC_u8Column, DIO_u8PIN_LOW);

    /* Loop on the rows of the Key Pad                                                                               */
    for (LOC_u8Row = 0 + ROW_INIT; LOC_u8Row < ROW_FIN; LOC_u8Row++)
    {
    	u8 local_Status;
      /* Check the status of the switch                                                                              */
      if (!DIO_GetPinValue(PORT, LOC_u8Row, &local_Status))
      {
        /* Get the value of the currently pressed switch                                                             */
        LOC_u8Retrun = KPD_au8SwitchVal[LOC_u8Column - COL_INIT][LOC_u8Row - ROW_INIT];

        /* Wait until the switch is released (Single Press)                                                          */
        while (!DIO_GetPinValue(PORT,LOC_u8Row,&local_Status))
          ;

        /* Delay to avoid bouncing                                                                                   */
        _delay_ms(10);

      }
    }

    /* Deactivate the Column                                                                                         */
    DIO_u8SetPinValue(PORT, LOC_u8Column, DIO_u8PIN_HIGH);
  }

  return LOC_u8Retrun;
}
