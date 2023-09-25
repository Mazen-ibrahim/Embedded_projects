/******************************************************/
/******************************************************/
/***************  Author:Mazen Ibrahim   **************/
/***************  Layer:  MCAL           **************/
/***************  SWC: KEYPAD            **************/
/***************  Version: 1.00          **************/
/******************************************************/
/******************************************************/

/******************* Include Library   ****************/
#include "STD_TYPES.h"
#include <util/delay.h>
/******************************************************/

/******************* Include MCAL *********************/
#include "DIO_private.h"
#include "DIO_inteface.h"
/******************************************************/

/******************* Include HAL **********************/
#include "KEYPAD_interface.h"
#include "KEYPAD_config.h"
#include "KEYPAD_private.h"
/******************************************************/



u8 KPD_u8GETPressedKey(void)
{
	u8 Local_u8PressedKey = KPD_No_PressedKey , Local_u8ColumnIdx , Local_u8RowIdx ,Local_u8Pin_State;
	static u8 Local_KPD_u8Arr[Row_NUM][Column_NUM] = KPD_ARR ;
	static u8 Local_KPD_u8ColumnNum[Column_NUM] = {KPD_COLUMN0_PIN,KPD_COLUMN1_PIN,KPD_COLUMN2_PIN};
    static u8 Local_KPD_u8RowNum[Row_NUM] = {KPD_ROW0_PIN,KPD_ROW1_PIN,KPD_ROW2_PIN,KPD_ROW3_PIN};


	for(Local_u8ColumnIdx = 0 ; Local_u8ColumnIdx < Column_NUM; Local_u8ColumnIdx++)
	{
		/* Activate Current Column */
		DIO_u8SetPinValue(KPD_PORT,Local_KPD_u8ColumnNum[Local_u8ColumnIdx],DIO_u8PIN_LOW);

		for(Local_u8RowIdx = 0 ; Local_u8RowIdx < Row_NUM; Local_u8RowIdx++)
		{
			/* Read Current Row */
			DIO_GetPinValue(KPD_PORT,Local_KPD_u8RowNum[Local_u8RowIdx],&Local_u8Pin_State);

			if(DIO_u8PIN_LOW == Local_u8Pin_State)
			{
				Local_u8PressedKey = Local_KPD_u8Arr[Local_u8RowIdx][Local_u8ColumnIdx];
				while(DIO_u8PIN_LOW == Local_u8Pin_State)
				{
					DIO_GetPinValue(KPD_PORT,Local_KPD_u8RowNum[Local_u8RowIdx],&Local_u8Pin_State);
				}
				return Local_u8PressedKey ;
			}

		}

		/* Deactivate Current Column */
		DIO_u8SetPinValue(KPD_PORT,Local_KPD_u8ColumnNum[Local_u8ColumnIdx],DIO_u8PIN_HIGH);

	}


	return Local_u8PressedKey;
}



u8 KPD_u8WaitForKey(void)
{
   u8 Key;
   while((Key =KPD_u8GETPressedKey()) == KPD_No_PressedKey);
   return Key;
}
