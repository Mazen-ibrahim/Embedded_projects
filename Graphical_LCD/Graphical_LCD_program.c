/******************************************************/
/******************************************************/
/***************  Author: Mazen Ibrahim  **************/
/***************  Layer: HAL             **************/
/***************  SWC: GLCD              **************/
/***************  Version: 1.00          **************/
/******************************************************/
/******************************************************/


/********************* Libraries **********************/
#include<util/delay.h>
#include "STD_TYPES.h"
#include "BIT_MATH.h"
/******************************************************/

/********************   MCAL   ************************/
#include "DIO_inteface.h"
#include "DIO_register.h"
#include "DIO_config.h"
#include "Graphical_LCD_interface.h"
#include "Grpahical_LCD_config.h"
#include "Graphical_LCD_private.h"
/******************************************************/


void GLCD_SendCommand(u8 copy_u8Command)
{
	// set DI pin low for command
	DIO_u8SetPinValue(GLCD_CONTROL_PORT,GLCD_DI,DIO_u8PIN_LOW);

	// Send command Data
	DIO_u8SetPortValue(GLCD_DATA_PORT,copy_u8Command);

	// set enable pulse
	DIO_u8SetPinValue(GLCD_CONTROL_PORT,GLCD_EN,DIO_u8PIN_HIGH);
	_delay_ms(2);
	DIO_u8SetPinValue(GLCD_CONTROL_PORT,GLCD_EN,DIO_u8PIN_LOW);

}

void GLCD_SendData(u8 copy_u8Data)
{
	// Set DI pin HIGH for DATA
	DIO_u8SetPinValue(GLCD_CONTROL_PORT,GLCD_DI,DIO_u8PIN_HIGH);

	// Send command Data
	DIO_u8SetPortValue(GLCD_DATA_PORT,copy_u8Data);

	// set enable pulse
	DIO_u8SetPinValue(GLCD_CONTROL_PORT,GLCD_EN,DIO_u8PIN_HIGH);
	_delay_ms(2);
	DIO_u8SetPinValue(GLCD_CONTROL_PORT,GLCD_EN,DIO_u8PIN_LOW);
}

void GLCD_SET_XY(u8 copy_u8_XPOS , u8 copy_u8_YPOS)
{
	u8 Y_Position = 0b01000000 | copy_u8_YPOS ;
	u8 X_Position = 0b10111000 | copy_u8_XPOS ;

	//Send first Page No.
	GLCD_SendCommand(X_Position);

	//Send second Pixel number in Page.
	GLCD_SendCommand(Y_Position);

}

void GLCD_Clear()
{


	for(int i = 0 ; i<16 ; i++)
	{
		if( i%2 == 0)
		{
			DIO_u8SetPinValue(GLCD_CONTROL_PORT,GLCD_CS1,DIO_u8PIN_HIGH);
			DIO_u8SetPinValue(GLCD_CONTROL_PORT,GLCD_CS2,DIO_u8PIN_LOW);
		}
		else
		{
			DIO_u8SetPinValue(GLCD_CONTROL_PORT,GLCD_CS1,DIO_u8PIN_LOW);
			DIO_u8SetPinValue(GLCD_CONTROL_PORT,GLCD_CS2,DIO_u8PIN_HIGH);
		}

		GLCD_SET_XY(i/2,0);

		for(int j = 0 ; j < 64 ; j++)
		{
			GLCD_SendData(0x00);
		}

	}
}

void GLCD_Init()
{
	//Send Display Off Command
	GLCD_SendCommand(DISPLAY_OFF);

	//Set X and Y Position
	GLCD_SET_XY(0,0);

	//Set Start Line
	GLCD_SendCommand(0xC0);

	//Set Reset Pin To HIGH
	DIO_u8SetPinValue(GLCD_CONTROL_PORT,GLCD_RST,DIO_u8PIN_HIGH);

	//Set Display on
	GLCD_SendCommand(DISPLAY_ON);

}

void GLCD_FullImage(u8 *ImageData)
{
	u32 Index = 0;

	for(int i = 0 ; i<16 ; i++)
	{
		if( i%2 == 0)
		{
			DIO_u8SetPinValue(GLCD_CONTROL_PORT,GLCD_CS1,DIO_u8PIN_HIGH);
			DIO_u8SetPinValue(GLCD_CONTROL_PORT,GLCD_CS2,DIO_u8PIN_LOW);
		}
		else
		{
			DIO_u8SetPinValue(GLCD_CONTROL_PORT,GLCD_CS1,DIO_u8PIN_LOW);
			DIO_u8SetPinValue(GLCD_CONTROL_PORT,GLCD_CS2,DIO_u8PIN_HIGH);
		}

		GLCD_SET_XY(i/2,0);

		for(int j = 0 ; j < 64 ; j++)
		{
			GLCD_SendData(ImageData[Index++]);
		}

	}

}

void GLCD_64X64Image(u8 *ImageData, HALF_SELECT Image_Half)
{
	if( Image_Half == GLCD_CS1 )
	{
		DIO_u8SetPinValue(GLCD_CONTROL_PORT,GLCD_CS1,DIO_u8PIN_HIGH);
	}

	else if ( Image_Half == GLCD_CS2 )
	{
		DIO_u8SetPinValue(GLCD_CONTROL_PORT,GLCD_CS2,DIO_u8PIN_HIGH);
	}

	u32 Index = 0;
	for( int i = 0 ; i<8 ; i++ )
	{
		GLCD_SET_XY(i,0);
		for( int j = 0 ; j<64 ; j++ )
		{
			GLCD_SendData(ImageData[Index++]);

		}

	}

}
