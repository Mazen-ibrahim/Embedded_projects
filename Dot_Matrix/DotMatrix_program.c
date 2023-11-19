/******************************************************/
/******************************************************/
/***************  Author:Mazen Ibrahim   **************/
/***************  Layer:  HAL            **************/
/***************  SWC: DOT Matrix        **************/
/***************  Version: 1.00          **************/
/******************************************************/
/******************************************************/


/****************** Include Libraries *****************/
#include <util/delay.h>
#include "STD_TYPES.h"
/******************************************************/

/******************** Include MCAL  *******************/
#include "DIO_inteface.h"
#include "DIO_register.h"
#include "DIO_private.h"
#include "PORT_register.h"
/******************************************************/

/******************** Include HAL *********************/
#include "DotMatrix_interface.h"
#include "DotMatrix_config.h"
#include "DotMatrix_private.h"
/******************************************************/

/*static array of Numbers*/
static u8 Letters[][8] =
{
		{0b11111111,0b11000000,0b10000000,0b10110111,0b10110111,0b10000000,0b11000000,0b11111111}, //A
		{0b11111111,0b10000000,0b10000000,0b10110110,0b10110110,0b10000000,0b11001001,0b11111111}, //B
		{0b11111111,0b11000001,0b10000000,0b10111110,0b10111110,0b10011100,0b11011101,0b11111111}, //C
		{0b11111111,0b10000000,0b10000000,0b10111110,0b10111110,0b10000000,0b11000011,0b11111111}, //D
		{0b11111111,0b10000000,0b10000000,0b10110110,0b10110110,0b10110110,0b10111110,0b11111111}, //E
		{0b11111111,0b10000000,0b10000000,0b10110111,0b10110111,0b10110111,0b10111111,0b11111111}, //F
		{0b11111111,0b11000001,0b10000000,0b10111110,0b10111010,0b10011000,0b11011001,0b11111111}, //G
		{0b11111111,0b10000000,0b10000000,0b11110111,0b11110111,0b10000000,0b10000000,0b11111111}, //H
		{0b11111111,0b11111111,0b10111110,0b10000000,0b10000000,0b10111110,0b11111111,0b11111111}, //I
		{0b11111111,0b11111001,0b11111000,0b10111110,0b10000000,0b10000001,0b10111111,0b11111111}, //J
		{0b11111111,0b10000000,0b10000000,0b11100011,0b11001001,0b10011100,0b10111110,0b11111111}, //K
		{0b11111111,0b10000000,0b10000000,0b11111110,0b11111110,0b11111110,0b11111110,0b11111111}, //L
		{0b11111111,0b10000000,0b10000000,0b11001111,0b11100111,0b11001111,0b10000000,0b10000000}, //M
		{0b11111111,0b10000000,0b10000000,0b11001111,0b11100111,0b11110011,0b10000000,0b10000000}, //N
		{0b11111111,0b11000001,0b10000000,0b10111110,0b10111110,0b10000000,0b11000001,0b11111111}, //O
		{0b11111111,0b10000000,0b10000000,0b10111011,0b10111011,0b10000011,0b11000111,0b11111111}, //P
		{0b11111111,0b11000011,0b10000001,0b10111101,0b10111001,0b10000000,0b11000010,0b11111111}, //Q
		{0b11111111,0b10000000,0b10000000,0b10110011,0b10110001,0b10000100,0b11001110,0b11111111}, //R
		{0b11111111,0b11001101,0b10000100,0b10110110,0b10110110,0b10010000,0b11011001,0b11111111}, //S
		{0b11111111,0b10011111,0b10111111,0b10000000,0b10000000,0b10111111,0b10011111,0b11111111}, //T
		{0b11111111,0b10000001,0b10000000,0b11111110,0b11111110,0b10000000,0b10000000,0b11111111}, //U
		{0b11111111,0b10000011,0b10000001,0b11111100,0b11111100,0b10000001,0b10000011,0b11111111}, //V
		{0b11111111,0b10000000,0b10000000,0b11111001,0b11110011,0b11111001,0b10000000,0b10000000}, //W
		{0b11111111,0b10011100,0b10001000,0b11100011,0b11110111,0b11100011,0b10001000,0b10011100}, //X
		{0b11111111,0b10001111,0b10000111,0b11110000,0b11110000,0b10000111,0b10001111,0b11111111}, //Y
		{0b11111111,0b10111100,0b10111000,0b10110010,0b10100110,0b10001110,0b10011110,0b11111111}  //Z

};


static u8 Numbers[][8] =
{
		{0b11111111,0b10000001,0b01111110,0b01111110,0b01111110,0b10000001,0b111111111,0b111111111}, //0
		{0b11111111,0b11111111,0b10111110,0b00000000,0b11111110,0b11111111,0b111111111,0b111111111}, //1
		{0b11111111,0b10111110,0b01111100,0b01111010,0b01110110,0b10001110,0b111111111,0b111111111}, //2
		{0b11111111,0b10111101,0b01111110,0b01101110,0b01101110,0b10010001,0b111111111,0b111111111}, //3
		{0b11111111,0b11110011,0b11101011,0b11011011,0b10111011,0b00000000,0b111111011,0b111111111}, //4
		{0b11111111,0b00001101,0b01101110,0b01101110,0b01101110,0b01110001,0b111111111,0b111111111}, //5
		{0b11111111,0b10000001,0b01101110,0b01101110,0b01101110,0b10110001,0b111111111,0b111111111}, //6
		{0b11111111,0b01111111,0b01111000,0b01110111,0b01101111,0b00011111,0b111111111,0b111111111}, //7
		{0b11111111,0b10010001,0b01101110,0b01101110,0b01101110,0b10010001,0b111111111,0b111111111}, //8
		{0b11111111,0b10001101,0b01110110,0b01110110,0b01110110,0b10000001,0b111111111,0b111111111}  //9

};





/*static array to toggle Columns of Used Dot Matrix*/

#if DOT_MATRIX_TYPE == _8X8
static u8 Columns_Toggle[8] =
{
		0b10000000,
		0b01000000,
		0b00100000,
		0b00010000,
		0b00001000,
		0b00000100,
		0b00000010,
		0b00000001,
};

#elif DOT_MATRIX_TYPE == _5X7
static u8 Columns_Toggle[5] =
{
		0b00000001,
		0b00000010,
		0b00000100,
		0b00001000,
		0b00010000,
		0b00100000
};
#endif

Init_Status Dot_Matrix_INIT()
{
	Init_Status status = Failed;
#if DOT_COLUMN_PORT != DOT_ROW_PORT
#if DOT_COLUMN_PORT == DIO_u8PORTA
	DDRA = 0xFF;
	status = Success
#elif DOT_COLUMN_PORT == DIO_u8PORTB
			DDRB = 0xFF;
	status = Success
#elif DOT_COLUMN_PORT == DIO_u8PORTC
			DDRC = 0xFF;
	status = Success;
#elif DOT_COLUMN_PORT == DIO_u8PORTD
	DDRD = 0xFF;
	status = Success
#endif


#if DOT_ROW_PORT == DIO_u8PORTA
			DDRA = 0xFF;
#elif DOT_ROW_PORT == DIO_u8PORTB
	DDRB = 0xFF;
#elif DOT_ROW_PORT == DIO_u8PORTC
	DDRC = 0xFF;
#elif DOT_ROW_PORT == DIO_u8PORTD
	DDRD = 0xFF;
#endif

#endif

	return status;

}

void Dot_Draw_Pattern(u8 *Copy_pu8Pattern)
{
#if DOT_MATRIX_TYPE == _8X8
#if DOT_COLUMN_PORT == DIO_u8PORTA && DOT_ROW_PORT == DIO_u8PORTB
	for(int i = 0 ; i < 50 ; i++ )
	{
		PORTA = Columns_Toggle[0];
		PORTB = Copy_pu8Pattern[0];
		_delay_ms(0.2);


		PORTA = Columns_Toggle[1];
		PORTB = Copy_pu8Pattern[1];
		_delay_ms(0.2);

		PORTA = Columns_Toggle[2];
		PORTB = Copy_pu8Pattern[2];
		_delay_ms(0.2);


		PORTA = Columns_Toggle[3];
		PORTB = Copy_pu8Pattern[3];
		_delay_ms(0.2);


		PORTA = Columns_Toggle[4];
		PORTB = Copy_pu8Pattern[4];
		_delay_ms(0.2);

		PORTA = Columns_Toggle[5];
		PORTB = Copy_pu8Pattern[5];
		_delay_ms(0.2);

		PORTA = Columns_Toggle[6];
		PORTB =Copy_pu8Pattern[6];
		_delay_ms(0.2);

		PORTA = Columns_Toggle[7];
		PORTB = Copy_pu8Pattern[7];
		_delay_ms(0.2);
	}
#elif DOT_COLUMN_PORT == DIO_u8PORTA && DOT_ROW_PORT == DIO_u8PORTC
	for(int i = 0 ; i < 50 ; i++ )
	{
		PORTA = Columns_Toggle[0];
		PORTC = Copy_pu8Pattern[0];
		_delay_ms(0.2);


		PORTA = Columns_Toggle[1];
		PORTC = Copy_pu8Pattern[1];
		_delay_ms(0.2);

		PORTA = Columns_Toggle[2];
		PORTC = Copy_pu8Pattern[2];
		_delay_ms(0.2);


		PORTA = Columns_Toggle[3];
		PORTC = Copy_pu8Pattern[3];
		_delay_ms(0.2);


		PORTA = Columns_Toggle[4];
		PORTC = Copy_pu8Pattern[4];
		_delay_ms(0.2);

		PORTA = Columns_Toggle[5];
		PORTC = Copy_pu8Pattern[5];
		_delay_ms(0.2);

		PORTA = Columns_Toggle[6];
		PORTC =Copy_pu8Pattern[6];
		_delay_ms(0.2);

		PORTA = Columns_Toggle[7];
		PORTC = Copy_pu8Pattern[7];
		_delay_ms(0.2);
	}

#elif DOT_COLUMN_PORT == DIO_u8PORTA && DOT_ROW_PORT == DIO_u8PORTD
	for(int i = 0 ; i < 50 ; i++ )
	{
		PORTA = Columns_Toggle[0];
		PORTD = Copy_pu8Pattern[0];
		_delay_ms(0.2);


		PORTA = Columns_Toggle[1];
		PORTD = Copy_pu8Pattern[1];
		_delay_ms(0.2);

		PORTA = Columns_Toggle[2];
		PORTD = Copy_pu8Pattern[2];
		_delay_ms(0.2);


		PORTA = Columns_Toggle[3];
		PORTD = Copy_pu8Pattern[3];
		_delay_ms(0.2);


		PORTA = Columns_Toggle[4];
		PORTD = Copy_pu8Pattern[4];
		_delay_ms(0.2);

		PORTA = Columns_Toggle[5];
		PORTD = Copy_pu8Pattern[5];
		_delay_ms(0.2);

		PORTA = Columns_Toggle[6];
		PORTD =Copy_pu8Pattern[6];
		_delay_ms(0.2);

		PORTA = Columns_Toggle[7];
		PORTD = Copy_pu8Pattern[7];
		_delay_ms(0.2);
	}
#elif DOT_COLUMN_PORT == DIO_u8PORTB && DOT_ROW_PORT == DIO_u8PORTA
	for(int i = 0 ; i < 50 ; i++ )
	{
		PORTB = Columns_Toggle[0];
		PORTA = Copy_pu8Pattern[0];
		_delay_ms(0.2);


		PORTB = Columns_Toggle[1];
		PORTA = Copy_pu8Pattern[1];
		_delay_ms(0.2);

		PORTB = Columns_Toggle[2];
		PORTA = Copy_pu8Pattern[2];
		_delay_ms(0.2);


		PORTB = Columns_Toggle[3];
		PORTA = Copy_pu8Pattern[3];
		_delay_ms(0.2);


		PORTB = Columns_Toggle[4];
		PORTA = Copy_pu8Pattern[4];
		_delay_ms(0.2);

		PORTB = Columns_Toggle[5];
		PORTA = Copy_pu8Pattern[5];
		_delay_ms(0.2);

		PORTB = Columns_Toggle[6];
		PORTA =Copy_pu8Pattern[6];
		_delay_ms(0.2);

		PORTB = Columns_Toggle[7];
		PORTA = Copy_pu8Pattern[7];
		_delay_ms(0.2);
	}
#elif DOT_COLUMN_PORT == DIO_u8PORTB && DOT_ROW_PORT == DIO_u8PORTC
	for(int i = 0 ; i < 50 ; i++ )
	{
		PORTB = Columns_Toggle[0];
		PORTC = Copy_pu8Pattern[0];
		_delay_ms(0.2);


		PORTB = Columns_Toggle[1];
		PORTC = Copy_pu8Pattern[1];
		_delay_ms(0.2);

		PORTB = Columns_Toggle[2];
		PORTC = Copy_pu8Pattern[2];
		_delay_ms(0.2);


		PORTB = Columns_Toggle[3];
		PORTC = Copy_pu8Pattern[3];
		_delay_ms(0.2);


		PORTB = Columns_Toggle[4];
		PORTC = Copy_pu8Pattern[4];
		_delay_ms(0.2);

		PORTB = Columns_Toggle[5];
		PORTC = Copy_pu8Pattern[5];
		_delay_ms(0.2);

		PORTB = Columns_Toggle[6];
		PORTC =Copy_pu8Pattern[6];
		_delay_ms(0.2);

		PORTB = Columns_Toggle[7];
		PORTC = Copy_pu8Pattern[7];
		_delay_ms(0.2);
	}
#elif DOT_COLUMN_PORT == DIO_u8PORTB && DOT_ROW_PORT == DIO_u8PORTD
	for(int i = 0 ; i < 50 ; i++ )
	{
		PORTB = Columns_Toggle[0];
		PORTD = Copy_pu8Pattern[0];
		_delay_ms(0.2);


		PORTB = Columns_Toggle[1];
		PORTD = Copy_pu8Pattern[1];
		_delay_ms(0.2);

		PORTB = Columns_Toggle[2];
		PORTD = Copy_pu8Pattern[2];
		_delay_ms(0.2);


		PORTB = Columns_Toggle[3];
		PORTD = Copy_pu8Pattern[3];
		_delay_ms(0.2);


		PORTB = Columns_Toggle[4];
		PORTD = Copy_pu8Pattern[4];
		_delay_ms(0.2);

		PORTB = Columns_Toggle[5];
		PORTD = Copy_pu8Pattern[5];
		_delay_ms(0.2);

		PORTB = Columns_Toggle[6];
		PORTD =Copy_pu8Pattern[6];
		_delay_ms(0.2);

		PORTB = Columns_Toggle[7];
		PORTD = Copy_pu8Pattern[7];
		_delay_ms(0.2);
	}
#elif DOT_COLUMN_PORT == DIO_u8PORTC && DOT_ROW_PORT == DIO_u8PORTA
	for(int i = 0 ; i < 50 ; i++ )
	{
		PORTC = Columns_Toggle[0];
		PORTA = Copy_pu8Pattern[0];
		_delay_ms(0.2);


		PORTC = Columns_Toggle[1];
		PORTA = Copy_pu8Pattern[1];
		_delay_ms(0.2);

		PORTC = Columns_Toggle[2];
		PORTA = Copy_pu8Pattern[2];
		_delay_ms(0.2);


		PORTC = Columns_Toggle[3];
		PORTA = Copy_pu8Pattern[3];
		_delay_ms(0.2);


		PORTC = Columns_Toggle[4];
		PORTA = Copy_pu8Pattern[4];
		_delay_ms(0.2);

		PORTC = Columns_Toggle[5];
		PORTA = Copy_pu8Pattern[5];
		_delay_ms(0.2);

		PORTC = Columns_Toggle[6];
		PORTA =Copy_pu8Pattern[6];
		_delay_ms(0.2);

		PORTC = Columns_Toggle[7];
		PORTA = Copy_pu8Pattern[7];
		_delay_ms(0.2);
	}
#elif DOT_COLUMN_PORT == DIO_u8PORTC && DOT_ROW_PORT == DIO_u8PORTB
	for(int i = 0 ; i < 50 ; i++ )
	{
		PORTC = Columns_Toggle[0];
		PORTB = Copy_pu8Pattern[0];
		_delay_ms(0.2);


		PORTC = Columns_Toggle[1];
		PORTB = Copy_pu8Pattern[1];
		_delay_ms(0.2);

		PORTC = Columns_Toggle[2];
		PORTB = Copy_pu8Pattern[2];
		_delay_ms(0.2);


		PORTC = Columns_Toggle[3];
		PORTB = Copy_pu8Pattern[3];
		_delay_ms(0.2);


		PORTC = Columns_Toggle[4];
		PORTB = Copy_pu8Pattern[4];
		_delay_ms(0.2);

		PORTC = Columns_Toggle[5];
		PORTB = Copy_pu8Pattern[5];
		_delay_ms(0.2);

		PORTC = Columns_Toggle[6];
		PORTB =Copy_pu8Pattern[6];
		_delay_ms(0.2);

		PORTC = Columns_Toggle[7];
		PORTB = Copy_pu8Pattern[7];
		_delay_ms(0.2);
	}
#elif DOT_COLUMN_PORT == DIO_u8PORTC && DOT_ROW_PORT == DIO_u8PORTD
	for(int i = 0 ; i < 50 ; i++ )
	{
		PORTC = Columns_Toggle[0];
		PORTD = Copy_pu8Pattern[0];
		_delay_ms(0.2);


		PORTC = Columns_Toggle[1];
		PORTD = Copy_pu8Pattern[1];
		_delay_ms(0.2);

		PORTC = Columns_Toggle[2];
		PORTD = Copy_pu8Pattern[2];
		_delay_ms(0.2);


		PORTC = Columns_Toggle[3];
		PORTD = Copy_pu8Pattern[3];
		_delay_ms(0.2);


		PORTC = Columns_Toggle[4];
		PORTD = Copy_pu8Pattern[4];
		_delay_ms(0.2);

		PORTC = Columns_Toggle[5];
		PORTD = Copy_pu8Pattern[5];
		_delay_ms(0.2);

		PORTC = Columns_Toggle[6];
		PORTD =Copy_pu8Pattern[6];
		_delay_ms(0.2);

		PORTC = Columns_Toggle[7];
		PORTD = Copy_pu8Pattern[7];
		_delay_ms(0.2);
	}
#elif DOT_COLUMN_PORT == DIO_u8PORTD && DOT_ROW_PORT == DIO_u8PORTA
	for(int i = 0 ; i < 50 ; i++ )
	{
		PORTD = Columns_Toggle[0];
		PORTA = Copy_pu8Pattern[0];
		_delay_ms(0.2);


		PORTD = Columns_Toggle[1];
		PORTA = Copy_pu8Pattern[1];
		_delay_ms(0.2);

		PORTD = Columns_Toggle[2];
		PORTA = Copy_pu8Pattern[2];
		_delay_ms(0.2);


		PORTD = Columns_Toggle[3];
		PORTA = Copy_pu8Pattern[3];
		_delay_ms(0.2);


		PORTD = Columns_Toggle[4];
		PORTA = Copy_pu8Pattern[4];
		_delay_ms(0.2);

		PORTD = Columns_Toggle[5];
		PORTA = Copy_pu8Pattern[5];
		_delay_ms(0.2);

		PORTD = Columns_Toggle[6];
		PORTA =Copy_pu8Pattern[6];
		_delay_ms(0.2);

		PORTD = Columns_Toggle[7];
		PORTA = Copy_pu8Pattern[7];
		_delay_ms(0.2);
	}
#elif DOT_COLUMN_PORT == DIO_u8PORTD && DOT_ROW_PORT == DIO_u8PORTB
	for(int i = 0 ; i < 50 ; i++ )
	{
		PORTD = Columns_Toggle[0];
		PORTB = Copy_pu8Pattern[0];
		_delay_ms(0.2);


		PORTD = Columns_Toggle[1];
		PORTB = Copy_pu8Pattern[1];
		_delay_ms(0.2);

		PORTD = Columns_Toggle[2];
		PORTB = Copy_pu8Pattern[2];
		_delay_ms(0.2);


		PORTD = Columns_Toggle[3];
		PORTB = Copy_pu8Pattern[3];
		_delay_ms(0.2);


		PORTD = Columns_Toggle[4];
		PORTB = Copy_pu8Pattern[4];
		_delay_ms(0.2);

		PORTD = Columns_Toggle[5];
		PORTB = Copy_pu8Pattern[5];
		_delay_ms(0.2);

		PORTD = Columns_Toggle[6];
		PORTB =Copy_pu8Pattern[6];
		_delay_ms(0.2);

		PORTD = Columns_Toggle[7];
		PORTB = Copy_pu8Pattern[7];
		_delay_ms(0.2);
	}
#elif DOT_COLUMN_PORT == DIO_u8PORTD && DOT_ROW_PORT == DIO_u8PORTC
	for(int i = 0 ; i < 50 ; i++ )
	{
		PORTD = Columns_Toggle[0];
		PORTC = Copy_pu8Pattern[0];
		_delay_ms(0.2);


		PORTD = Columns_Toggle[1];
		PORTC = Copy_pu8Pattern[1];
		_delay_ms(0.2);

		PORTD = Columns_Toggle[2];
		PORTC = Copy_pu8Pattern[2];
		_delay_ms(0.2);


		PORTD = Columns_Toggle[3];
		PORTC = Copy_pu8Pattern[3];
		_delay_ms(0.2);


		PORTD = Columns_Toggle[4];
		PORTC = Copy_pu8Pattern[4];
		_delay_ms(0.2);

		PORTD = Columns_Toggle[5];
		PORTC = Copy_pu8Pattern[5];
		_delay_ms(0.2);

		PORTD = Columns_Toggle[6];
		PORTC =Copy_pu8Pattern[6];
		_delay_ms(0.2);

		PORTD = Columns_Toggle[7];
		PORTC = Copy_pu8Pattern[7];
		_delay_ms(0.2);
	}
#endif

#elif DOT_MATRIX_TYPE == _5X7
#if DOT_COLUMN_PORT == DIO_u8PORTA && DOT_ROW_PORT == DIO_u8PORTB
	for(int i = 0 ; i < 50 ; i++ )
	{
		PORTA = Columns_Toggle[0];
		PORTB = Copy_pu8Pattern[0];
		_delay_ms(0.2);


		PORTA = Columns_Toggle[1];
		PORTB = Copy_pu8Pattern[1];
		_delay_ms(0.2);

		PORTA = Columns_Toggle[2];
		PORTB = Copy_pu8Pattern[2];
		_delay_ms(0.2);


		PORTA = Columns_Toggle[3];
		PORTB = Copy_pu8Pattern[3];
		_delay_ms(0.2);


		PORTA = Columns_Toggle[4];
		PORTB = Copy_pu8Pattern[4];
		_delay_ms(0.2);

	}
#elif DOT_COLUMN_PORT == DIO_u8PORTA && DOT_ROW_PORT == DIO_u8PORTC
	for(int i = 0 ; i < 50 ; i++ )
	{
		PORTA = Columns_Toggle[0];
		PORTC = Copy_pu8Pattern[0];
		_delay_ms(0.2);


		PORTA = Columns_Toggle[1];
		PORTC = Copy_pu8Pattern[1];
		_delay_ms(0.2);

		PORTA = Columns_Toggle[2];
		PORTC = Copy_pu8Pattern[2];
		_delay_ms(0.2);


		PORTA = Columns_Toggle[3];
		PORTC = Copy_pu8Pattern[3];
		_delay_ms(0.2);


		PORTA = Columns_Toggle[4];
		PORTC = Copy_pu8Pattern[4];
		_delay_ms(0.2);
	}

#elif DOT_COLUMN_PORT == DIO_u8PORTA && DOT_ROW_PORT == DIO_u8PORTD
	for(int i = 0 ; i < 50 ; i++ )
	{
		PORTA = Columns_Toggle[0];
		PORTD = Copy_pu8Pattern[0];
		_delay_ms(0.2);


		PORTA = Columns_Toggle[1];
		PORTD = Copy_pu8Pattern[1];
		_delay_ms(0.2);

		PORTA = Columns_Toggle[2];
		PORTD = Copy_pu8Pattern[2];
		_delay_ms(0.2);


		PORTA = Columns_Toggle[3];
		PORTD = Copy_pu8Pattern[3];
		_delay_ms(0.2);


		PORTA = Columns_Toggle[4];
		PORTD = Copy_pu8Pattern[4];
		_delay_ms(0.2);


	}
#elif DOT_COLUMN_PORT == DIO_u8PORTB && DOT_ROW_PORT == DIO_u8PORTA
	for(int i = 0 ; i < 50 ; i++ )
	{
		PORTB = Columns_Toggle[0];
		PORTA = Copy_pu8Pattern[0];
		_delay_ms(0.2);


		PORTB = Columns_Toggle[1];
		PORTA = Copy_pu8Pattern[1];
		_delay_ms(0.2);

		PORTB = Columns_Toggle[2];
		PORTA = Copy_pu8Pattern[2];
		_delay_ms(0.2);


		PORTB = Columns_Toggle[3];
		PORTA = Copy_pu8Pattern[3];
		_delay_ms(0.2);


		PORTB = Columns_Toggle[4];
		PORTA = Copy_pu8Pattern[4];
		_delay_ms(0.2);

	}
#elif DOT_COLUMN_PORT == DIO_u8PORTB && DOT_ROW_PORT == DIO_u8PORTC
	for(int i = 0 ; i < 50 ; i++ )
	{
		PORTB = Columns_Toggle[0];
		PORTC = Copy_pu8Pattern[0];
		_delay_ms(0.2);


		PORTB = Columns_Toggle[1];
		PORTC = Copy_pu8Pattern[1];
		_delay_ms(0.2);

		PORTB = Columns_Toggle[2];
		PORTC = Copy_pu8Pattern[2];
		_delay_ms(0.2);


		PORTB = Columns_Toggle[3];
		PORTC = Copy_pu8Pattern[3];
		_delay_ms(0.2);


		PORTB = Columns_Toggle[4];
		PORTC = Copy_pu8Pattern[4];
		_delay_ms(0.2);

	}
#elif DOT_COLUMN_PORT == DIO_u8PORTB && DOT_ROW_PORT == DIO_u8PORTD
	for(int i = 0 ; i < 50 ; i++ )
	{
		PORTB = Columns_Toggle[0];
		PORTD = Copy_pu8Pattern[0];
		_delay_ms(0.2);


		PORTB = Columns_Toggle[1];
		PORTD = Copy_pu8Pattern[1];
		_delay_ms(0.2);

		PORTB = Columns_Toggle[2];
		PORTD = Copy_pu8Pattern[2];
		_delay_ms(0.2);


		PORTB = Columns_Toggle[3];
		PORTD = Copy_pu8Pattern[3];
		_delay_ms(0.2);


		PORTB = Columns_Toggle[4];
		PORTD = Copy_pu8Pattern[4];
		_delay_ms(0.2);

	}
#elif DOT_COLUMN_PORT == DIO_u8PORTC && DOT_ROW_PORT == DIO_u8PORTA
	for(int i = 0 ; i < 50 ; i++ )
	{
		PORTC = Columns_Toggle[0];
		PORTA = Copy_pu8Pattern[0];
		_delay_ms(0.2);


		PORTC = Columns_Toggle[1];
		PORTA = Copy_pu8Pattern[1];
		_delay_ms(0.2);

		PORTC = Columns_Toggle[2];
		PORTA = Copy_pu8Pattern[2];
		_delay_ms(0.2);


		PORTC = Columns_Toggle[3];
		PORTA = Copy_pu8Pattern[3];
		_delay_ms(0.2);


		PORTC = Columns_Toggle[4];
		PORTA = Copy_pu8Pattern[4];
		_delay_ms(0.2);

	}
#elif DOT_COLUMN_PORT == DIO_u8PORTC && DOT_ROW_PORT == DIO_u8PORTB
	for(int i = 0 ; i < 50 ; i++ )
	{
		PORTC = Columns_Toggle[0];
		PORTB = Copy_pu8Pattern[0];
		_delay_ms(0.2);


		PORTC = Columns_Toggle[1];
		PORTB = Copy_pu8Pattern[1];
		_delay_ms(0.2);

		PORTC = Columns_Toggle[2];
		PORTB = Copy_pu8Pattern[2];
		_delay_ms(0.2);


		PORTC = Columns_Toggle[3];
		PORTB = Copy_pu8Pattern[3];
		_delay_ms(0.2);


		PORTC = Columns_Toggle[4];
		PORTB = Copy_pu8Pattern[4];
		_delay_ms(0.2);

	}
#elif DOT_COLUMN_PORT == DIO_u8PORTC && DOT_ROW_PORT == DIO_u8PORTD
	for(int i = 0 ; i < 50 ; i++ )
	{
		PORTC = Columns_Toggle[0];
		PORTD = Copy_pu8Pattern[0];
		_delay_ms(0.2);


		PORTC = Columns_Toggle[1];
		PORTD = Copy_pu8Pattern[1];
		_delay_ms(0.2);

		PORTC = Columns_Toggle[2];
		PORTD = Copy_pu8Pattern[2];
		_delay_ms(0.2);


		PORTC = Columns_Toggle[3];
		PORTD = Copy_pu8Pattern[3];
		_delay_ms(0.2);


		PORTC = Columns_Toggle[4];
		PORTD = Copy_pu8Pattern[4];
		_delay_ms(0.2);

	}
#elif DOT_COLUMN_PORT == DIO_u8PORTD && DOT_ROW_PORT == DIO_u8PORTA
	for(int i = 0 ; i < 50 ; i++ )
	{
		PORTD = Columns_Toggle[0];
		PORTA = Copy_pu8Pattern[0];
		_delay_ms(0.2);


		PORTD = Columns_Toggle[1];
		PORTA = Copy_pu8Pattern[1];
		_delay_ms(0.2);

		PORTD = Columns_Toggle[2];
		PORTA = Copy_pu8Pattern[2];
		_delay_ms(0.2);


		PORTD = Columns_Toggle[3];
		PORTA = Copy_pu8Pattern[3];
		_delay_ms(0.2);


		PORTD = Columns_Toggle[4];
		PORTA = Copy_pu8Pattern[4];
		_delay_ms(0.2);

	}
#elif DOT_COLUMN_PORT == DIO_u8PORTD && DOT_ROW_PORT == DIO_u8PORTB
	for(int i = 0 ; i < 50 ; i++ )
	{
		PORTD = Columns_Toggle[0];
		PORTB = Copy_pu8Pattern[0];
		_delay_ms(0.2);


		PORTD = Columns_Toggle[1];
		PORTB = Copy_pu8Pattern[1];
		_delay_ms(0.2);

		PORTD = Columns_Toggle[2];
		PORTB = Copy_pu8Pattern[2];
		_delay_ms(0.2);


		PORTD = Columns_Toggle[3];
		PORTB = Copy_pu8Pattern[3];
		_delay_ms(0.2);


		PORTD = Columns_Toggle[4];
		PORTB = Copy_pu8Pattern[4];
		_delay_ms(0.2);

	}
#elif DOT_COLUMN_PORT == DIO_u8PORTD && DOT_ROW_PORT == DIO_u8PORTC
	for(int i = 0 ; i < 50 ; i++ )
	{
		PORTD = Columns_Toggle[0];
		PORTC = Copy_pu8Pattern[0];
		_delay_ms(0.2);


		PORTD = Columns_Toggle[1];
		PORTC = Copy_pu8Pattern[1];
		_delay_ms(0.2);

		PORTD = Columns_Toggle[2];
		PORTC = Copy_pu8Pattern[2];
		_delay_ms(0.2);


		PORTD = Columns_Toggle[3];
		PORTC = Copy_pu8Pattern[3];
		_delay_ms(0.2);


		PORTD = Columns_Toggle[4];
		PORTC = Copy_pu8Pattern[4];
		_delay_ms(0.2);

	}
#endif

#endif


}

void Dot_Draw_Letter(u8 copy_u8Letter)
{

	u32 index = (u32)(copy_u8Letter - 65);

#if DOT_MATRIX_TYPE == _8X8
#if DOT_COLUMN_PORT == DIO_u8PORTA && DOT_ROW_PORT == DIO_u8PORTB
	for(int i = 0 ; i < 50 ; i++ )
	{
		PORTA = Columns_Toggle[0];
		PORTB = Letters[index][0];
		_delay_ms(0.2);


		PORTA = Columns_Toggle[1];
		PORTB = Letters[index][1];
		_delay_ms(0.2);

		PORTA = Columns_Toggle[2];
		PORTB = Letters[index][2];
		_delay_ms(0.2);


		PORTA = Columns_Toggle[3];
		PORTB = Letters[index][3];
		_delay_ms(0.2);


		PORTA = Columns_Toggle[4];
		PORTB = Letters[index][4];
		_delay_ms(0.2);

		PORTA = Columns_Toggle[5];
		PORTB = Letters[index][5];
		_delay_ms(0.2);

		PORTA = Columns_Toggle[6];
		PORTB = Letters[index][6];
		_delay_ms(0.2);

		PORTA = Columns_Toggle[7];
		PORTB = Letters[index][7];
		_delay_ms(0.2);
	}
#elif DOT_COLUMN_PORT == DIO_u8PORTA && DOT_ROW_PORT == DIO_u8PORTC
	for(int i = 0 ; i < 50 ; i++ )
	{
		PORTA = Columns_Toggle[0];
		PORTC = Letters[index][0];
		_delay_ms(0.2);


		PORTA = Columns_Toggle[1];
		PORTC = Letters[index][1];
		_delay_ms(0.2);

		PORTA = Columns_Toggle[2];
		PORTC = Letters[index][2];
		_delay_ms(0.2);


		PORTA = Columns_Toggle[3];
		PORTC = Letters[index][3];
		_delay_ms(0.2);


		PORTA = Columns_Toggle[4];
		PORTC = Letters[index][4];
		_delay_ms(0.2);

		PORTA = Columns_Toggle[5];
		PORTC = Letters[index][5];
		_delay_ms(0.2);

		PORTA = Columns_Toggle[6];
		PORTC = Letters[index][6];
		_delay_ms(0.2);

		PORTA = Columns_Toggle[7];
		PORTC = Letters[index][7];
		_delay_ms(0.2);
	}

#elif DOT_COLUMN_PORT == DIO_u8PORTA && DOT_ROW_PORT == DIO_u8PORTD
	for(int i = 0 ; i < 50 ; i++ )
	{
		PORTA = Columns_Toggle[0];
		PORTD = Letters[index][0];
		_delay_ms(0.2);


		PORTA = Columns_Toggle[1];
		PORTD = Letters[index][1];
		_delay_ms(0.2);

		PORTA = Columns_Toggle[2];
		PORTD = Letters[index][2];
		_delay_ms(0.2);


		PORTA = Columns_Toggle[3];
		PORTD = Letters[index][3];
		_delay_ms(0.2);


		PORTA = Columns_Toggle[4];
		PORTD = Letters[index][4];
		_delay_ms(0.2);

		PORTA = Columns_Toggle[5];
		PORTD = Letters[index][5];
		_delay_ms(0.2);

		PORTA = Columns_Toggle[6];
		PORTD =Letters[index][6];
		_delay_ms(0.2);

		PORTA = Columns_Toggle[7];
		PORTD = Letters[index][7];
		_delay_ms(0.2);
	}
#elif DOT_COLUMN_PORT == DIO_u8PORTB && DOT_ROW_PORT == DIO_u8PORTA
	for(int i = 0 ; i < 50 ; i++ )
	{
		PORTB = Columns_Toggle[0];
		PORTA = Letters[index][0];
		_delay_ms(0.2);


		PORTB = Columns_Toggle[1];
		PORTA = Letters[index][1];
		_delay_ms(0.2);

		PORTB = Columns_Toggle[2];
		PORTA = Letters[index][2];
		_delay_ms(0.2);


		PORTB = Columns_Toggle[3];
		PORTA = Letters[index][3];
		_delay_ms(0.2);


		PORTB = Columns_Toggle[4];
		PORTA = Letters[index][4];
		_delay_ms(0.2);

		PORTB = Columns_Toggle[5];
		PORTA = Letters[index][5];
		_delay_ms(0.2);

		PORTB = Columns_Toggle[6];
		PORTA =Letters[index][6];
		_delay_ms(0.2);

		PORTB = Columns_Toggle[7];
		PORTA = Letters[index][7];
		_delay_ms(0.2);
	}
#elif DOT_COLUMN_PORT == DIO_u8PORTB && DOT_ROW_PORT == DIO_u8PORTC
	for(int i = 0 ; i < 50 ; i++ )
	{
		PORTB = Columns_Toggle[0];
		PORTC = Letters[index][0];
		_delay_ms(0.2);


		PORTB = Columns_Toggle[1];
		PORTC = Letters[index][1];
		_delay_ms(0.2);

		PORTB = Columns_Toggle[2];
		PORTC = Letters[index][2];
		_delay_ms(0.2);


		PORTB = Columns_Toggle[3];
		PORTC = Letters[index][3];
		_delay_ms(0.2);


		PORTB = Columns_Toggle[4];
		PORTC = Letters[index][4];
		_delay_ms(0.2);

		PORTB = Columns_Toggle[5];
		PORTC = Letters[index][5];
		_delay_ms(0.2);

		PORTB = Columns_Toggle[6];
		PORTC =Letters[index][6];
		_delay_ms(0.2);

		PORTB = Columns_Toggle[7];
		PORTC = Letters[index][7];
		_delay_ms(0.2);
	}
#elif DOT_COLUMN_PORT == DIO_u8PORTB && DOT_ROW_PORT == DIO_u8PORTD
	for(int i = 0 ; i < 50 ; i++ )
	{
		PORTB = Columns_Toggle[0];
		PORTD = Letters[index][0];
		_delay_ms(0.2);


		PORTB = Columns_Toggle[1];
		PORTD = Letters[index][1];
		_delay_ms(0.2);

		PORTB = Columns_Toggle[2];
		PORTD = Letters[index][2];
		_delay_ms(0.2);


		PORTB = Columns_Toggle[3];
		PORTD = Letters[index][3];
		_delay_ms(0.2);


		PORTB = Columns_Toggle[4];
		PORTD = Letters[index][4];
		_delay_ms(0.2);

		PORTB = Columns_Toggle[5];
		PORTD = Letters[index][5];
		_delay_ms(0.2);

		PORTB = Columns_Toggle[6];
		PORTD =Letters[index][6];
		_delay_ms(0.2);

		PORTB = Columns_Toggle[7];
		PORTD = Letters[index][7];
		_delay_ms(0.2);
	}
#elif DOT_COLUMN_PORT == DIO_u8PORTC && DOT_ROW_PORT == DIO_u8PORTA
	for(int i = 0 ; i < 50 ; i++ )
	{
		PORTC = Columns_Toggle[0];
		PORTA = Letters[index][0];
		_delay_ms(0.2);


		PORTC = Columns_Toggle[1];
		PORTA = Letters[index][1];
		_delay_ms(0.2);

		PORTC = Columns_Toggle[2];
		PORTA = Letters[index][2];
		_delay_ms(0.2);


		PORTC = Columns_Toggle[3];
		PORTA = Letters[index][3];
		_delay_ms(0.2);


		PORTC = Columns_Toggle[4];
		PORTA = Letters[index][4];
		_delay_ms(0.2);

		PORTC = Columns_Toggle[5];
		PORTA = Letters[index][5];
		_delay_ms(0.2);

		PORTC = Columns_Toggle[6];
		PORTA =Letters[index][6];
		_delay_ms(0.2);

		PORTC = Columns_Toggle[7];
		PORTA = Letters[index][7];
		_delay_ms(0.2);
	}
#elif DOT_COLUMN_PORT == DIO_u8PORTC && DOT_ROW_PORT == DIO_u8PORTB
	for(int i = 0 ; i < 50 ; i++ )
	{
		PORTC = Columns_Toggle[0];
		PORTB = Letters[index][0];
		_delay_ms(0.2);


		PORTC = Columns_Toggle[1];
		PORTB = Letters[index][1];
		_delay_ms(0.2);

		PORTC = Columns_Toggle[2];
		PORTB = Letters[index][2];
		_delay_ms(0.2);


		PORTC = Columns_Toggle[3];
		PORTB = Letters[index][3];
		_delay_ms(0.2);


		PORTC = Columns_Toggle[4];
		PORTB = Letters[index][4];
		_delay_ms(0.2);

		PORTC = Columns_Toggle[5];
		PORTB = Letters[index][5];
		_delay_ms(0.2);

		PORTC = Columns_Toggle[6];
		PORTB = Letters[index][6];
		_delay_ms(0.2);

		PORTC = Columns_Toggle[7];
		PORTB = Letters[index][7];
		_delay_ms(0.2);
	}
#elif DOT_COLUMN_PORT == DIO_u8PORTC && DOT_ROW_PORT == DIO_u8PORTD
	for(int i = 0 ; i < 50 ; i++ )
	{
		PORTC = Columns_Toggle[0];
		PORTD = Letters[index][0];
		_delay_ms(0.2);


		PORTC = Columns_Toggle[1];
		PORTD = Letters[index][1];
		_delay_ms(0.2);

		PORTC = Columns_Toggle[2];
		PORTD = Letters[index][2];
		_delay_ms(0.2);


		PORTC = Columns_Toggle[3];
		PORTD = Letters[index][3];
		_delay_ms(0.2);


		PORTC = Columns_Toggle[4];
		PORTD = Letters[index][4];
		_delay_ms(0.2);

		PORTC = Columns_Toggle[5];
		PORTD = Letters[index][5];
		_delay_ms(0.2);

		PORTC = Columns_Toggle[6];
		PORTD =Letters[index][6];
		_delay_ms(0.2);

		PORTC = Columns_Toggle[7];
		PORTD = Letters[index][7];
		_delay_ms(0.2);
	}
#elif DOT_COLUMN_PORT == DIO_u8PORTD && DOT_ROW_PORT == DIO_u8PORTA
	for(int i = 0 ; i < 50 ; i++ )
	{
		PORTD = Columns_Toggle[0];
		PORTA = Letters[index][0];
		_delay_ms(0.2);


		PORTD = Columns_Toggle[1];
		PORTA = Letters[index][1];
		_delay_ms(0.2);

		PORTD = Columns_Toggle[2];
		PORTA = Letters[index][2];
		_delay_ms(0.2);


		PORTD = Columns_Toggle[3];
		PORTA = Letters[index][3];
		_delay_ms(0.2);


		PORTD = Columns_Toggle[4];
		PORTA = Letters[index][4];
		_delay_ms(0.2);

		PORTD = Columns_Toggle[5];
		PORTA = Letters[index][5];
		_delay_ms(0.2);

		PORTD = Columns_Toggle[6];
		PORTA =Letters[index][6];
		_delay_ms(0.2);

		PORTD = Columns_Toggle[7];
		PORTA = Letters[index][7];
		_delay_ms(0.2);
	}
#elif DOT_COLUMN_PORT == DIO_u8PORTD && DOT_ROW_PORT == DIO_u8PORTB
	for(int i = 0 ; i < 50 ; i++ )
	{
		PORTD = Columns_Toggle[0];
		PORTB = Letters[index][0];
		_delay_ms(0.2);


		PORTD = Columns_Toggle[1];
		PORTB = Letters[index][1];
		_delay_ms(0.2);

		PORTD = Columns_Toggle[2];
		PORTB = Letters[index][2];
		_delay_ms(0.2);


		PORTD = Columns_Toggle[3];
		PORTB = Letters[index][3];
		_delay_ms(0.2);


		PORTD = Columns_Toggle[4];
		PORTB = Letters[index][4];
		_delay_ms(0.2);

		PORTD = Columns_Toggle[5];
		PORTB = Letters[index][5];
		_delay_ms(0.2);

		PORTD = Columns_Toggle[6];
		PORTB =Letters[index][6];
		_delay_ms(0.2);

		PORTD = Columns_Toggle[7];
		PORTB = Letters[index][7];
		_delay_ms(0.2);
	}
#elif DOT_COLUMN_PORT == DIO_u8PORTD && DOT_ROW_PORT == DIO_u8PORTC
	for(int i = 0 ; i < 50 ; i++ )
	{
		PORTD = Columns_Toggle[0];
		PORTC = Letters[index][0];
		_delay_ms(0.2);


		PORTD = Columns_Toggle[1];
		PORTC = Letters[index][1];
		_delay_ms(0.2);

		PORTD = Columns_Toggle[2];
		PORTC = Letters[index][2];
		_delay_ms(0.2);


		PORTD = Columns_Toggle[3];
		PORTC = Letters[index][3];
		_delay_ms(0.2);


		PORTD = Columns_Toggle[4];
		PORTC = Letters[index][4];
		_delay_ms(0.2);

		PORTD = Columns_Toggle[5];
		PORTC = Letters[index][5];
		_delay_ms(0.2);

		PORTD = Columns_Toggle[6];
		PORTC =Letters[index][6];
		_delay_ms(0.2);

		PORTD = Columns_Toggle[7];
		PORTC = Letters[index][7];
		_delay_ms(0.2);
	}
#endif

#elif DOT_MATRIX_TYPE == _5X7
#if DOT_COLUMN_PORT == DIO_u8PORTA && DOT_ROW_PORT == DIO_u8PORTB
	for(int i = 0 ; i < 50 ; i++ )
	{
		PORTA = Columns_Toggle[0];
		PORTB = Letters[index][0];
		_delay_ms(0.2);


		PORTA = Columns_Toggle[1];
		PORTB = Letters[index][1];
		_delay_ms(0.2);

		PORTA = Columns_Toggle[2];
		PORTB = Letters[index][2];
		_delay_ms(0.2);


		PORTA = Columns_Toggle[3];
		PORTB = Letters[index][3];
		_delay_ms(0.2);


		PORTA = Columns_Toggle[4];
		PORTB = Letters[index][4];
		_delay_ms(0.2);

	}
#elif DOT_COLUMN_PORT == DIO_u8PORTA && DOT_ROW_PORT == DIO_u8PORTC
	for(int i = 0 ; i < 50 ; i++ )
	{
		PORTA = Columns_Toggle[0];
		PORTC = Letters[index][0];
		_delay_ms(0.2);


		PORTA = Columns_Toggle[1];
		PORTC = Letters[index][1];
		_delay_ms(0.2);

		PORTA = Columns_Toggle[2];
		PORTC = Letters[index][2];
		_delay_ms(0.2);


		PORTA = Columns_Toggle[3];
		PORTC = Letters[index][3];
		_delay_ms(0.2);


		PORTA = Columns_Toggle[4];
		PORTC = Letters[index][4];
		_delay_ms(0.2);
	}

#elif DOT_COLUMN_PORT == DIO_u8PORTA && DOT_ROW_PORT == DIO_u8PORTD
	for(int i = 0 ; i < 50 ; i++ )
	{
		PORTA = Columns_Toggle[0];
		PORTD = Letters[index][0];
		_delay_ms(0.2);


		PORTA = Columns_Toggle[1];
		PORTD = Letters[index][1];
		_delay_ms(0.2);

		PORTA = Columns_Toggle[2];
		PORTD = Letters[index][2];
		_delay_ms(0.2);


		PORTA = Columns_Toggle[3];
		PORTD = Letters[index][3];
		_delay_ms(0.2);


		PORTA = Columns_Toggle[4];
		PORTD = Letters[index][4];
		_delay_ms(0.2);


	}
#elif DOT_COLUMN_PORT == DIO_u8PORTB && DOT_ROW_PORT == DIO_u8PORTA
	for(int i = 0 ; i < 50 ; i++ )
	{
		PORTB = Columns_Toggle[0];
		PORTA = Letters[index][0];
		_delay_ms(0.2);


		PORTB = Columns_Toggle[1];
		PORTA = Letters[index][1];
		_delay_ms(0.2);

		PORTB = Columns_Toggle[2];
		PORTA = Letters[index][2];
		_delay_ms(0.2);


		PORTB = Columns_Toggle[3];
		PORTA = Letters[index][3];
		_delay_ms(0.2);


		PORTB = Columns_Toggle[4];
		PORTA = Letters[index][4];
		_delay_ms(0.2);

	}
#elif DOT_COLUMN_PORT == DIO_u8PORTB && DOT_ROW_PORT == DIO_u8PORTC
	for(int i = 0 ; i < 50 ; i++ )
	{
		PORTB = Columns_Toggle[0];
		PORTC = Letters[index][0];
		_delay_ms(0.2);


		PORTB = Columns_Toggle[1];
		PORTC = Letters[index][1];
		_delay_ms(0.2);

		PORTB = Columns_Toggle[2];
		PORTC = Letters[index][2];
		_delay_ms(0.2);


		PORTB = Columns_Toggle[3];
		PORTC = Letters[index][3];
		_delay_ms(0.2);


		PORTB = Columns_Toggle[4];
		PORTC = Letters[index][4];
		_delay_ms(0.2);

	}
#elif DOT_COLUMN_PORT == DIO_u8PORTB && DOT_ROW_PORT == DIO_u8PORTD
	for(int i = 0 ; i < 50 ; i++ )
	{
		PORTB = Columns_Toggle[0];
		PORTD = Letters[index][0];
		_delay_ms(0.2);


		PORTB = Columns_Toggle[1];
		PORTD = Letters[index][1];
		_delay_ms(0.2);

		PORTB = Columns_Toggle[2];
		PORTD = Letters[index][2];
		_delay_ms(0.2);


		PORTB = Columns_Toggle[3];
		PORTD = Letters[index][3];
		_delay_ms(0.2);


		PORTB = Columns_Toggle[4];
		PORTD = Letters[index][4];
		_delay_ms(0.2);

	}
#elif DOT_COLUMN_PORT == DIO_u8PORTC && DOT_ROW_PORT == DIO_u8PORTA
	for(int i = 0 ; i < 50 ; i++ )
	{
		PORTC = Columns_Toggle[0];
		PORTA = Letters[index][0];
		_delay_ms(0.2);


		PORTC = Columns_Toggle[1];
		PORTA = Letters[index][1];
		_delay_ms(0.2);

		PORTC = Columns_Toggle[2];
		PORTA = Letters[index][2];
		_delay_ms(0.2);


		PORTC = Columns_Toggle[3];
		PORTA = Letters[index][3];
		_delay_ms(0.2);


		PORTC = Columns_Toggle[4];
		PORTA = Letters[index][4];
		_delay_ms(0.2);

	}
#elif DOT_COLUMN_PORT == DIO_u8PORTC && DOT_ROW_PORT == DIO_u8PORTB
	for(int i = 0 ; i < 50 ; i++ )
	{
		PORTC = Columns_Toggle[0];
		PORTB = Letters[index][0];
		_delay_ms(0.2);


		PORTC = Columns_Toggle[1];
		PORTB = Letters[index][1];
		_delay_ms(0.2);

		PORTC = Columns_Toggle[2];
		PORTB = Letters[index][2];
		_delay_ms(0.2);


		PORTC = Columns_Toggle[3];
		PORTB = Letters[index][3];
		_delay_ms(0.2);


		PORTC = Columns_Toggle[4];
		PORTB = Letters[index][4];
		_delay_ms(0.2);

	}
#elif DOT_COLUMN_PORT == DIO_u8PORTC && DOT_ROW_PORT == DIO_u8PORTD
	for(int i = 0 ; i < 50 ; i++ )
	{
		PORTC = Columns_Toggle[0];
		PORTD = Letters[index][0];
		_delay_ms(0.2);


		PORTC = Columns_Toggle[1];
		PORTD = Letters[index][1];
		_delay_ms(0.2);

		PORTC = Columns_Toggle[2];
		PORTD = Letters[index][2];
		_delay_ms(0.2);


		PORTC = Columns_Toggle[3];
		PORTD = Letters[index][3];
		_delay_ms(0.2);


		PORTC = Columns_Toggle[4];
		PORTD = Letters[index][4];
		_delay_ms(0.2);

	}
#elif DOT_COLUMN_PORT == DIO_u8PORTD && DOT_ROW_PORT == DIO_u8PORTA
	for(int i = 0 ; i < 50 ; i++ )
	{
		PORTD = Columns_Toggle[0];
		PORTA = Letters[index][0];
		_delay_ms(0.2);


		PORTD = Columns_Toggle[1];
		PORTA = Letters[index][1];
		_delay_ms(0.2);

		PORTD = Columns_Toggle[2];
		PORTA = Letters[index][2];
		_delay_ms(0.2);


		PORTD = Columns_Toggle[3];
		PORTA = Letters[index][3];
		_delay_ms(0.2);


		PORTD = Columns_Toggle[4];
		PORTA = Letters[index][4];
		_delay_ms(0.2);

	}
#elif DOT_COLUMN_PORT == DIO_u8PORTD && DOT_ROW_PORT == DIO_u8PORTB
	for(int i = 0 ; i < 50 ; i++ )
	{
		PORTD = Columns_Toggle[0];
		PORTB = Letters[index][0];
		_delay_ms(0.2);


		PORTD = Columns_Toggle[1];
		PORTB = Letters[index][1];
		_delay_ms(0.2);

		PORTD = Columns_Toggle[2];
		PORTB = Letters[index][2];
		_delay_ms(0.2);


		PORTD = Columns_Toggle[3];
		PORTB = Letters[index][3];
		_delay_ms(0.2);


		PORTD = Columns_Toggle[4];
		PORTB = Letters[index][4];
		_delay_ms(0.2);

	}
#elif DOT_COLUMN_PORT == DIO_u8PORTD && DOT_ROW_PORT == DIO_u8PORTC
	for(int i = 0 ; i < 50 ; i++ )
	{
		PORTD = Columns_Toggle[0];
		PORTC = Letters[index][0];
		_delay_ms(0.2);


		PORTD = Columns_Toggle[1];
		PORTC = Letters[index][1];
		_delay_ms(0.2);

		PORTD = Columns_Toggle[2];
		PORTC = Letters[index][2];
		_delay_ms(0.2);


		PORTD = Columns_Toggle[3];
		PORTC = Letters[index][3];
		_delay_ms(0.2);


		PORTD = Columns_Toggle[4];
		PORTC = Letters[index][4];
		_delay_ms(0.2);

	}
#endif

#endif

}

void Dot_Draw_Number(u8 copy_u8Number)
{

	u32 index = (u32)(copy_u8Number - 48);

#if DOT_MATRIX_TYPE == _8X8
#if DOT_COLUMN_PORT == DIO_u8PORTA && DOT_ROW_PORT == DIO_u8PORTB
	for(int i = 0 ; i < 50 ; i++ )
	{
		PORTA = Columns_Toggle[0];
		PORTB = Numbers[index][0];
		_delay_ms(0.2);


		PORTA = Columns_Toggle[1];
		PORTB = Numbers[index][1];
		_delay_ms(0.2);

		PORTA = Columns_Toggle[2];
		PORTB = Numbers[index][2];
		_delay_ms(0.2);


		PORTA = Columns_Toggle[3];
		PORTB = Numbers[index][3];
		_delay_ms(0.2);


		PORTA = Columns_Toggle[4];
		PORTB = Numbers[index][4];
		_delay_ms(0.2);

		PORTA = Columns_Toggle[5];
		PORTB = Numbers[index][5];
		_delay_ms(0.2);

		PORTA = Columns_Toggle[6];
		PORTB = Numbers[index][6];
		_delay_ms(0.2);

		PORTA = Columns_Toggle[7];
		PORTB = Numbers[index][7];
		_delay_ms(0.2);
	}
#elif DOT_COLUMN_PORT == DIO_u8PORTA && DOT_ROW_PORT == DIO_u8PORTC
	for(int i = 0 ; i < 50 ; i++ )
	{
		PORTA = Columns_Toggle[0];
		PORTC = Numbers[index][0];
		_delay_ms(0.2);


		PORTA = Columns_Toggle[1];
		PORTC = Numbers[index][1];
		_delay_ms(0.2);

		PORTA = Columns_Toggle[2];
		PORTC = Numbers[index][2];
		_delay_ms(0.2);


		PORTA = Columns_Toggle[3];
		PORTC = Numbers[index][3];
		_delay_ms(0.2);


		PORTA = Columns_Toggle[4];
		PORTC = Numbers[index][4];
		_delay_ms(0.2);

		PORTA = Columns_Toggle[5];
		PORTC = Numbers[index][5];
		_delay_ms(0.2);

		PORTA = Columns_Toggle[6];
		PORTC = Numbers[index][6];
		_delay_ms(0.2);

		PORTA = Columns_Toggle[7];
		PORTC = Numbers[index][7];
		_delay_ms(0.2);
	}

#elif DOT_COLUMN_PORT == DIO_u8PORTA && DOT_ROW_PORT == DIO_u8PORTD
	for(int i = 0 ; i < 50 ; i++ )
	{
		PORTA = Columns_Toggle[0];
		PORTD = Numbers[index][0];
		_delay_ms(0.2);


		PORTA = Columns_Toggle[1];
		PORTD = Numbers[index][1];
		_delay_ms(0.2);

		PORTA = Columns_Toggle[2];
		PORTD = Numbers[index][2];
		_delay_ms(0.2);


		PORTA = Columns_Toggle[3];
		PORTD = Numbers[index][3];
		_delay_ms(0.2);


		PORTA = Columns_Toggle[4];
		PORTD = Numbers[index][4];
		_delay_ms(0.2);

		PORTA = Columns_Toggle[5];
		PORTD = Numbers[index][5];
		_delay_ms(0.2);

		PORTA = Columns_Toggle[6];
		PORTD =Numbers[index][6];
		_delay_ms(0.2);

		PORTA = Columns_Toggle[7];
		PORTD = Numbers[index][7];
		_delay_ms(0.2);
	}
#elif DOT_COLUMN_PORT == DIO_u8PORTB && DOT_ROW_PORT == DIO_u8PORTA
	for(int i = 0 ; i < 50 ; i++ )
	{
		PORTB = Columns_Toggle[0];
		PORTA = Numbers[index][0];
		_delay_ms(0.2);


		PORTB = Columns_Toggle[1];
		PORTA = Numbers[index][1];
		_delay_ms(0.2);

		PORTB = Columns_Toggle[2];
		PORTA = Numbers[index][2];
		_delay_ms(0.2);


		PORTB = Columns_Toggle[3];
		PORTA = Numbers[index][3];
		_delay_ms(0.2);


		PORTB = Columns_Toggle[4];
		PORTA = Numbers[index][4];
		_delay_ms(0.2);

		PORTB = Columns_Toggle[5];
		PORTA = Numbers[index][5];
		_delay_ms(0.2);

		PORTB = Columns_Toggle[6];
		PORTA =Numbers[index][6];
		_delay_ms(0.2);

		PORTB = Columns_Toggle[7];
		PORTA = Numbers[index][7];
		_delay_ms(0.2);
	}
#elif DOT_COLUMN_PORT == DIO_u8PORTB && DOT_ROW_PORT == DIO_u8PORTC
	for(int i = 0 ; i < 50 ; i++ )
	{
		PORTB = Columns_Toggle[0];
		PORTC = Numbers[index][0];
		_delay_ms(0.2);


		PORTB = Columns_Toggle[1];
		PORTC = Numbers[index][1];
		_delay_ms(0.2);

		PORTB = Columns_Toggle[2];
		PORTC = Numbers[index][2];
		_delay_ms(0.2);


		PORTB = Columns_Toggle[3];
		PORTC = Numbers[index][3];
		_delay_ms(0.2);


		PORTB = Columns_Toggle[4];
		PORTC = Numbers[index][4];
		_delay_ms(0.2);

		PORTB = Columns_Toggle[5];
		PORTC = Numbers[index][5];
		_delay_ms(0.2);

		PORTB = Columns_Toggle[6];
		PORTC =Numbers[index][6];
		_delay_ms(0.2);

		PORTB = Columns_Toggle[7];
		PORTC = Numbers[index][7];
		_delay_ms(0.2);
	}
#elif DOT_COLUMN_PORT == DIO_u8PORTB && DOT_ROW_PORT == DIO_u8PORTD
	for(int i = 0 ; i < 50 ; i++ )
	{
		PORTB = Columns_Toggle[0];
		PORTD = Numbers[index][0];
		_delay_ms(0.2);


		PORTB = Columns_Toggle[1];
		PORTD = Numbers[index][1];
		_delay_ms(0.2);

		PORTB = Columns_Toggle[2];
		PORTD = Numbers[index][2];
		_delay_ms(0.2);


		PORTB = Columns_Toggle[3];
		PORTD = Numbers[index][3];
		_delay_ms(0.2);


		PORTB = Columns_Toggle[4];
		PORTD = Numbers[index][4];
		_delay_ms(0.2);

		PORTB = Columns_Toggle[5];
		PORTD = Numbers[index][5];
		_delay_ms(0.2);

		PORTB = Columns_Toggle[6];
		PORTD =Numbers[index][6];
		_delay_ms(0.2);

		PORTB = Columns_Toggle[7];
		PORTD = Numbers[index][7];
		_delay_ms(0.2);
	}
#elif DOT_COLUMN_PORT == DIO_u8PORTC && DOT_ROW_PORT == DIO_u8PORTA
	for(int i = 0 ; i < 50 ; i++ )
	{
		PORTC = Columns_Toggle[0];
		PORTA = Numbers[index][0];
		_delay_ms(0.2);


		PORTC = Columns_Toggle[1];
		PORTA = Numbers[index][1];
		_delay_ms(0.2);

		PORTC = Columns_Toggle[2];
		PORTA = Numbers[index][2];
		_delay_ms(0.2);


		PORTC = Columns_Toggle[3];
		PORTA = Numbers[index][3];
		_delay_ms(0.2);


		PORTC = Columns_Toggle[4];
		PORTA = Numbers[index][4];
		_delay_ms(0.2);

		PORTC = Columns_Toggle[5];
		PORTA = Numbers[index][5];
		_delay_ms(0.2);

		PORTC = Columns_Toggle[6];
		PORTA =Numbers[index][6];
		_delay_ms(0.2);

		PORTC = Columns_Toggle[7];
		PORTA = Numbers[index][7];
		_delay_ms(0.2);
	}
#elif DOT_COLUMN_PORT == DIO_u8PORTC && DOT_ROW_PORT == DIO_u8PORTB
	for(int i = 0 ; i < 50 ; i++ )
	{
		PORTC = Columns_Toggle[0];
		PORTB = Numbers[index][0];
		_delay_ms(0.2);


		PORTC = Columns_Toggle[1];
		PORTB = Numbers[index][1];
		_delay_ms(0.2);

		PORTC = Columns_Toggle[2];
		PORTB = Numbers[index][2];
		_delay_ms(0.2);


		PORTC = Columns_Toggle[3];
		PORTB = Numbers[index][3];
		_delay_ms(0.2);


		PORTC = Columns_Toggle[4];
		PORTB = Numbers[index][4];
		_delay_ms(0.2);

		PORTC = Columns_Toggle[5];
		PORTB = Numbers[index][5];
		_delay_ms(0.2);

		PORTC = Columns_Toggle[6];
		PORTB = Numbers[index][6];
		_delay_ms(0.2);

		PORTC = Columns_Toggle[7];
		PORTB = Numbers[index][7];
		_delay_ms(0.2);
	}
#elif DOT_COLUMN_PORT == DIO_u8PORTC && DOT_ROW_PORT == DIO_u8PORTD
	for(int i = 0 ; i < 50 ; i++ )
	{
		PORTC = Columns_Toggle[0];
		PORTD = Numbers[index][0];
		_delay_ms(0.2);


		PORTC = Columns_Toggle[1];
		PORTD = Numbers[index][1];
		_delay_ms(0.2);

		PORTC = Columns_Toggle[2];
		PORTD = Numbers[index][2];
		_delay_ms(0.2);


		PORTC = Columns_Toggle[3];
		PORTD = Numbers[index][3];
		_delay_ms(0.2);


		PORTC = Columns_Toggle[4];
		PORTD = Numbers[index][4];
		_delay_ms(0.2);

		PORTC = Columns_Toggle[5];
		PORTD = Numbers[index][5];
		_delay_ms(0.2);

		PORTC = Columns_Toggle[6];
		PORTD =Numbers[index][6];
		_delay_ms(0.2);

		PORTC = Columns_Toggle[7];
		PORTD = Numbers[index][7];
		_delay_ms(0.2);
	}
#elif DOT_COLUMN_PORT == DIO_u8PORTD && DOT_ROW_PORT == DIO_u8PORTA
	for(int i = 0 ; i < 50 ; i++ )
	{
		PORTD = Columns_Toggle[0];
		PORTA = Numbers[index][0];
		_delay_ms(0.2);


		PORTD = Columns_Toggle[1];
		PORTA = Numbers[index][1];
		_delay_ms(0.2);

		PORTD = Columns_Toggle[2];
		PORTA = Numbers[index][2];
		_delay_ms(0.2);


		PORTD = Columns_Toggle[3];
		PORTA = Numbers[index][3];
		_delay_ms(0.2);


		PORTD = Columns_Toggle[4];
		PORTA = Numbers[index][4];
		_delay_ms(0.2);

		PORTD = Columns_Toggle[5];
		PORTA = Numbers[index][5];
		_delay_ms(0.2);

		PORTD = Columns_Toggle[6];
		PORTA =Numbers[index][6];
		_delay_ms(0.2);

		PORTD = Columns_Toggle[7];
		PORTA = Numbers[index][7];
		_delay_ms(0.2);
	}
#elif DOT_COLUMN_PORT == DIO_u8PORTD && DOT_ROW_PORT == DIO_u8PORTB
	for(int i = 0 ; i < 50 ; i++ )
	{
		PORTD = Columns_Toggle[0];
		PORTB = Numbers[index][0];
		_delay_ms(0.2);


		PORTD = Columns_Toggle[1];
		PORTB = Numbers[index][1];
		_delay_ms(0.2);

		PORTD = Columns_Toggle[2];
		PORTB = Numbers[index][2];
		_delay_ms(0.2);


		PORTD = Columns_Toggle[3];
		PORTB = Numbers[index][3];
		_delay_ms(0.2);


		PORTD = Columns_Toggle[4];
		PORTB = Numbers[index][4];
		_delay_ms(0.2);

		PORTD = Columns_Toggle[5];
		PORTB = Numbers[index][5];
		_delay_ms(0.2);

		PORTD = Columns_Toggle[6];
		PORTB =Numbers[index][6];
		_delay_ms(0.2);

		PORTD = Columns_Toggle[7];
		PORTB = Numbers[index][7];
		_delay_ms(0.2);
	}
#elif DOT_COLUMN_PORT == DIO_u8PORTD && DOT_ROW_PORT == DIO_u8PORTC
	for(int i = 0 ; i < 50 ; i++ )
	{
		PORTD = Columns_Toggle[0];
		PORTC = Numbers[index][0];
		_delay_ms(0.2);


		PORTD = Columns_Toggle[1];
		PORTC = Numbers[index][1];
		_delay_ms(0.2);

		PORTD = Columns_Toggle[2];
		PORTC = Numbers[index][2];
		_delay_ms(0.2);


		PORTD = Columns_Toggle[3];
		PORTC = Numbers[index][3];
		_delay_ms(0.2);


		PORTD = Columns_Toggle[4];
		PORTC = Numbers[index][4];
		_delay_ms(0.2);

		PORTD = Columns_Toggle[5];
		PORTC = Numbers[index][5];
		_delay_ms(0.2);

		PORTD = Columns_Toggle[6];
		PORTC =Numbers[index][6];
		_delay_ms(0.2);

		PORTD = Columns_Toggle[7];
		PORTC = Numbers[index][7];
		_delay_ms(0.2);
	}
#endif

#elif DOT_MATRIX_TYPE == _5X7
#if DOT_COLUMN_PORT == DIO_u8PORTA && DOT_ROW_PORT == DIO_u8PORTB
	for(int i = 0 ; i < 50 ; i++ )
	{
		PORTA = Columns_Toggle[0];
		PORTB = Numbers[index][0];
		_delay_ms(0.2);


		PORTA = Columns_Toggle[1];
		PORTB = Numbers[index][1];
		_delay_ms(0.2);

		PORTA = Columns_Toggle[2];
		PORTB = Numbers[index][2];
		_delay_ms(0.2);


		PORTA = Columns_Toggle[3];
		PORTB = Numbers[index][3];
		_delay_ms(0.2);


		PORTA = Columns_Toggle[4];
		PORTB = Numbers[index][4];
		_delay_ms(0.2);

	}
#elif DOT_COLUMN_PORT == DIO_u8PORTA && DOT_ROW_PORT == DIO_u8PORTC
	for(int i = 0 ; i < 50 ; i++ )
	{
		PORTA = Columns_Toggle[0];
		PORTC = Numbers[index][0];
		_delay_ms(0.2);


		PORTA = Columns_Toggle[1];
		PORTC = Numbers[index][1];
		_delay_ms(0.2);

		PORTA = Columns_Toggle[2];
		PORTC = Numbers[index][2];
		_delay_ms(0.2);


		PORTA = Columns_Toggle[3];
		PORTC = Numbers[index][3];
		_delay_ms(0.2);


		PORTA = Columns_Toggle[4];
		PORTC = Numbers[index][4];
		_delay_ms(0.2);
	}

#elif DOT_COLUMN_PORT == DIO_u8PORTA && DOT_ROW_PORT == DIO_u8PORTD
	for(int i = 0 ; i < 50 ; i++ )
	{
		PORTA = Columns_Toggle[0];
		PORTD = Numbers[index][0];
		_delay_ms(0.2);


		PORTA = Columns_Toggle[1];
		PORTD = Numbers[index][1];
		_delay_ms(0.2);

		PORTA = Columns_Toggle[2];
		PORTD = Numbers[index][2];
		_delay_ms(0.2);


		PORTA = Columns_Toggle[3];
		PORTD = Numbers[index][3];
		_delay_ms(0.2);


		PORTA = Columns_Toggle[4];
		PORTD = Numbers[index][4];
		_delay_ms(0.2);


	}
#elif DOT_COLUMN_PORT == DIO_u8PORTB && DOT_ROW_PORT == DIO_u8PORTA
	for(int i = 0 ; i < 50 ; i++ )
	{
		PORTB = Columns_Toggle[0];
		PORTA = Numbers[index][0];
		_delay_ms(0.2);


		PORTB = Columns_Toggle[1];
		PORTA = Numbers[index][1];
		_delay_ms(0.2);

		PORTB = Columns_Toggle[2];
		PORTA = Numbers[index][2];
		_delay_ms(0.2);


		PORTB = Columns_Toggle[3];
		PORTA = Numbers[index][3];
		_delay_ms(0.2);


		PORTB = Columns_Toggle[4];
		PORTA = Numbers[index][4];
		_delay_ms(0.2);

	}
#elif DOT_COLUMN_PORT == DIO_u8PORTB && DOT_ROW_PORT == DIO_u8PORTC
	for(int i = 0 ; i < 50 ; i++ )
	{
		PORTB = Columns_Toggle[0];
		PORTC = Numbers[index][0];
		_delay_ms(0.2);


		PORTB = Columns_Toggle[1];
		PORTC = Numbers[index][1];
		_delay_ms(0.2);

		PORTB = Columns_Toggle[2];
		PORTC = Numbers[index][2];
		_delay_ms(0.2);


		PORTB = Columns_Toggle[3];
		PORTC = Numbers[index][3];
		_delay_ms(0.2);


		PORTB = Columns_Toggle[4];
		PORTC = Numbers[index][4];
		_delay_ms(0.2);

	}
#elif DOT_COLUMN_PORT == DIO_u8PORTB && DOT_ROW_PORT == DIO_u8PORTD
	for(int i = 0 ; i < 50 ; i++ )
	{
		PORTB = Columns_Toggle[0];
		PORTD = Numbers[index][0];
		_delay_ms(0.2);


		PORTB = Columns_Toggle[1];
		PORTD = Numbers[index][1];
		_delay_ms(0.2);

		PORTB = Columns_Toggle[2];
		PORTD = Numbers[index][2];
		_delay_ms(0.2);


		PORTB = Columns_Toggle[3];
		PORTD = Numbers[index][3];
		_delay_ms(0.2);


		PORTB = Columns_Toggle[4];
		PORTD = Numbers[index][4];
		_delay_ms(0.2);

	}
#elif DOT_COLUMN_PORT == DIO_u8PORTC && DOT_ROW_PORT == DIO_u8PORTA
	for(int i = 0 ; i < 50 ; i++ )
	{
		PORTC = Columns_Toggle[0];
		PORTA = Numbers[index][0];
		_delay_ms(0.2);


		PORTC = Columns_Toggle[1];
		PORTA = Numbers[index][1];
		_delay_ms(0.2);

		PORTC = Columns_Toggle[2];
		PORTA = Numbers[index][2];
		_delay_ms(0.2);


		PORTC = Columns_Toggle[3];
		PORTA = Numbers[index][3];
		_delay_ms(0.2);


		PORTC = Columns_Toggle[4];
		PORTA = Numbers[index][4];
		_delay_ms(0.2);

	}
#elif DOT_COLUMN_PORT == DIO_u8PORTC && DOT_ROW_PORT == DIO_u8PORTB
	for(int i = 0 ; i < 50 ; i++ )
	{
		PORTC = Columns_Toggle[0];
		PORTB = Numbers[index][0];
		_delay_ms(0.2);


		PORTC = Columns_Toggle[1];
		PORTB = Numbers[index][1];
		_delay_ms(0.2);

		PORTC = Columns_Toggle[2];
		PORTB = Numbers[index][2];
		_delay_ms(0.2);


		PORTC = Columns_Toggle[3];
		PORTB = Numbers[index][3];
		_delay_ms(0.2);


		PORTC = Columns_Toggle[4];
		PORTB = Numbers[index][4];
		_delay_ms(0.2);

	}
#elif DOT_COLUMN_PORT == DIO_u8PORTC && DOT_ROW_PORT == DIO_u8PORTD
	for(int i = 0 ; i < 50 ; i++ )
	{
		PORTC = Columns_Toggle[0];
		PORTD = Numbers[index][0];
		_delay_ms(0.2);


		PORTC = Columns_Toggle[1];
		PORTD = Numbers[index][1];
		_delay_ms(0.2);

		PORTC = Columns_Toggle[2];
		PORTD = Numbers[index][2];
		_delay_ms(0.2);


		PORTC = Columns_Toggle[3];
		PORTD = Numbers[index][3];
		_delay_ms(0.2);


		PORTC = Columns_Toggle[4];
		PORTD = Numbers[index][4];
		_delay_ms(0.2);

	}
#elif DOT_COLUMN_PORT == DIO_u8PORTD && DOT_ROW_PORT == DIO_u8PORTA
	for(int i = 0 ; i < 50 ; i++ )
	{
		PORTD = Columns_Toggle[0];
		PORTA = Numbers[index][0];
		_delay_ms(0.2);


		PORTD = Columns_Toggle[1];
		PORTA = Numbers[index][1];
		_delay_ms(0.2);

		PORTD = Columns_Toggle[2];
		PORTA = Numbers[index][2];
		_delay_ms(0.2);


		PORTD = Columns_Toggle[3];
		PORTA = Numbers[index][3];
		_delay_ms(0.2);


		PORTD = Columns_Toggle[4];
		PORTA = Numbers[index][4];
		_delay_ms(0.2);

	}
#elif DOT_COLUMN_PORT == DIO_u8PORTD && DOT_ROW_PORT == DIO_u8PORTB
	for(int i = 0 ; i < 50 ; i++ )
	{
		PORTD = Columns_Toggle[0];
		PORTB = Numbers[index][0];
		_delay_ms(0.2);


		PORTD = Columns_Toggle[1];
		PORTB = Numbers[index][1];
		_delay_ms(0.2);

		PORTD = Columns_Toggle[2];
		PORTB = Numbers[index][2];
		_delay_ms(0.2);


		PORTD = Columns_Toggle[3];
		PORTB = Numbers[index][3];
		_delay_ms(0.2);


		PORTD = Columns_Toggle[4];
		PORTB = Numbers[index][4];
		_delay_ms(0.2);

	}
#elif DOT_COLUMN_PORT == DIO_u8PORTD && DOT_ROW_PORT == DIO_u8PORTC
	for(int i = 0 ; i < 50 ; i++ )
	{
		PORTD = Columns_Toggle[0];
		PORTC = Numbers[index][0];
		_delay_ms(0.2);


		PORTD = Columns_Toggle[1];
		PORTC = Numbers[index][1];
		_delay_ms(0.2);

		PORTD = Columns_Toggle[2];
		PORTC = Numbers[index][2];
		_delay_ms(0.2);


		PORTD = Columns_Toggle[3];
		PORTC = Numbers[index][3];
		_delay_ms(0.2);


		PORTD = Columns_Toggle[4];
		PORTC = Numbers[index][4];
		_delay_ms(0.2);

	}
#endif

#endif

}

