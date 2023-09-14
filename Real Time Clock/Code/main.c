#include <util/delay.h>
#include "STD_TYPES.h"
#include "Configuration.h"
#include "DIO_inteface.h"
#include "DIO_private.h"
#include "PORT_interface.h"
#include "Timer_0_interface.h"
#include "GIE_interface.h"
#include "CLCD_interface.h"
#include "KEYPAD_interface.h"

static u8 Index_1 = 0;
static u8 Index_2 = 0;
static u8 Index_3 = 0;
static u8 Index_4 = 0;
static u8 Index_5 = 0;
static u8 Index_6 = 0;


//define CallBack Function of CTC Mode of Timer
void Clock_Second(void);

int main()
{

	//Initialize Timer
	Timer0_voidInit();

	//Set Compare Math Value
	Timer0_voidSetCompareMatch(250);

	//Set CallBack Function of CTC Mode
	Timer0_CTC_u8SetCallBack(&Clock_Second);

	//Enable Comapre Match Interrupt
	Timer0_EnableCompareMatchInterrupt();

	//Enable Global Interrupt
	GIE_voidEnable();

	//Initialize PORTS
	PORT_voidInit();

	//Initialize CLCD
	CLCD_voidInit();

	CLCD_voidSendString("   Real Clock  ");
	_delay_ms(200);
	CLCD_voidSendCommand(CLEAR_DISPLAY);
	CLCD_voidSendString("1-Set    2-Reset");
	CLCD_GoToXY(1,0);
	CLCD_voidSendString("3-Resume 4-Stop");

	u8 Pattern_Number[] = {0x00,0x10,0x20,0x30,0x40,0x50,0x60,0x70,0x80,0x90};
	u8 Key = 0;

	while(1)
	{


		for(int i = 0 ; i<30; i++)
		{
			PORTB  = 0b11011111;
			PORTC  = Pattern_Number[Index_1];
			_delay_ms(0.5);

			PORTB  = 0b11101111;
			PORTC  = Pattern_Number[Index_2];
			_delay_ms(0.5);

			PORTB  = 0b11110111;
			PORTC  = Pattern_Number[Index_3];
			_delay_ms(0.5);

			PORTB  = 0b11111011;
			PORTC  = Pattern_Number[Index_4];
			_delay_ms(0.5);

			PORTB  = 0b11111101;
			PORTC  = Pattern_Number[Index_5];
			_delay_ms(0.5);

			PORTB  = 0b11111110;
			PORTC  = Pattern_Number[Index_6];
			_delay_ms(0.5);

		}


		Key = KPD_u8GETPressedKey();

		if(Key != KPD_No_PressedKey)
		{
			switch(Key)
			{
			case '1':

				Timer0_DisableCompareMatchInterrupt();

				CLCD_voidSendCommand(CLEAR_DISPLAY);
				CLCD_voidSendString("Hours:");
				while((Key = KPD_u8GETPressedKey()) == KPD_No_PressedKey);
				CLCD_voidSendData(Key);
				Index_6 = Key-48;
				while((Key = KPD_u8GETPressedKey()) == KPD_No_PressedKey);
				CLCD_voidSendData(Key);
				Index_5 = Key-48;

				CLCD_voidSendCommand(CLEAR_DISPLAY);
				CLCD_voidSendString("Minutes:");
				while((Key = KPD_u8GETPressedKey()) == KPD_No_PressedKey);
				CLCD_voidSendData(Key);
				Index_4 = Key-48;
				while((Key = KPD_u8GETPressedKey()) == KPD_No_PressedKey);
				CLCD_voidSendData(Key);
				Index_3 = Key-48;

				CLCD_voidSendCommand(CLEAR_DISPLAY);
				CLCD_voidSendString("Seconds:");
				while((Key = KPD_u8GETPressedKey()) == KPD_No_PressedKey);
				CLCD_voidSendData(Key);
				Index_2 = Key-48;
				while((Key = KPD_u8GETPressedKey()) == KPD_No_PressedKey);
				CLCD_voidSendData(Key);
				Index_1 = Key-48;

				CLCD_voidSendCommand(CLEAR_DISPLAY);
				CLCD_voidSendString("1-Set    2-Reset");
				CLCD_GoToXY(1,0);
				CLCD_voidSendString("3-Resume 4-Stop");

				Timer0_EnableCompareMatchInterrupt();


				break;


			case '2':

				Timer0_DisableCompareMatchInterrupt();

				Index_1 = 0;
				Index_2 = 0;
				Index_3 = 0;
				Index_4 = 0;
				Index_5 = 0;
				Index_6 = 0;

				Timer0_EnableCompareMatchInterrupt();

				break;


			case '3':

				Timer0_EnableCompareMatchInterrupt();

				break;


			case '4':

				Timer0_DisableCompareMatchInterrupt();

				break;



			}

		}

	}







}

void Clock_Second(void)
{
	static u32 Counter = 0;

	Counter++;

	if( Counter == 1000)
	{

		Index_1++;
		if(Index_1 == 10)
		{
			Index_2++;
			Index_1 = 0;
		}

		if(Index_2 == 6)
		{
			Index_3++;
			Index_2 = 0;
			Index_1 = 0;
		}

		if(Index_3 == 10)
		{

			Index_4++;
			Index_3 = 0;
			Index_2 = 0;
			Index_1 = 0;
		}

		if( Index_4 == 6)
		{
			Index_5++;
			Index_4 = 0;
			Index_3 = 0;
			Index_2 = 0;
			Index_1 = 0;

		}

		if( Index_5 == 10)
		{
			Index_6++;
			Index_5 = 0;
			Index_4 = 0;
			Index_3 = 0;
			Index_2 = 0;
			Index_1 = 0;

		}

		if( Index_6 == 2 && Index_5 == 4)
		{
			Index_6 = 0;
			Index_5 = 0;
			Index_4 = 0;
			Index_3 = 0;
			Index_2 = 0;
			Index_1 = 0;

		}

		Counter = 0;
	}



}



