#include <util/delay.h>
#include "STD_TYPES.h"
#include "Configuration.h"
#include "PORT_interface.h"
#include "DIO_inteface.h"
#include "SPI_interface.h"
#include "ADC_interface.h"
#include "GIE_interface.h"
#include "CLCD_interface.h"


static u8 SPI_Flag = False;
static u8 ADC_Flag = False;
static u8 SPI_Data = 0;

void SPI_NotifyFunc(void);
void ADC_NotifyFunc(void);
u32 Calc_Temp(u16 ADC_Reading);

u8  Channel_Select[3] = {0,1,2};
u16 Channel_Result[3] = {0,0,0};
ADC_Chain adc_Chain = {
		.Channel = Channel_Select,
		.Result = Channel_Result,
		.Size = 3,
		.NotificationFunc = ADC_NotifyFunc
};



int main(void)
{
	//Initialize PORTS
	PORT_voidInit();

	//Initialize LCD
	CLCD_voidInit();

	//Initialize ADC
    ADC_VoidINIT();

    //Start Chain Conversion
    StartChainConversionAsynch(&adc_Chain);

	//Initialize SPI as Slave
	SPI_void_SlaveInit();

	//Set Global Variable for SPI and CallBack Func
	SPI_NotificationFucntion(&SPI_Data,SPI_NotifyFunc);

	//Enable Global Interrupt
	GIE_voidEnable();


	CLCD_voidSendString("Rooms Temperature");
	CLCD_GoToXY(1,0);
	CLCD_voidSendString("Room (1) : ");
	CLCD_GoToXY(2,0);
	CLCD_voidSendString("Room (2) : ");
	CLCD_GoToXY(3,0);
	CLCD_voidSendString("Room (3) : ");

	while(1)
	{

		if( SPI_Flag == True )
		{
			switch(SPI_Data)
			{
			case 'a':
				DIO_u8SetPinValue(DIO_u8PORTB,DIO_u8PIN0,DIO_u8PIN_HIGH);
				SPI_Flag = False;
				break;
			case 'b':
				DIO_u8SetPinValue(DIO_u8PORTB,DIO_u8PIN0,DIO_u8PIN_LOW);
				SPI_Flag = False;
				break;
			case 'c':
				DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN0,DIO_u8PIN_HIGH);
				SPI_Flag = False;
				break;
			case 'd':
				DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN0,DIO_u8PIN_LOW);
				SPI_Flag = False;
				break;

			case 'e':
				DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN3,DIO_u8PIN_HIGH);
				SPI_Flag = False;
				break;

			case 'f':
				DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN3,DIO_u8PIN_LOW);
				SPI_Flag = False;
				break;

			case 'g':
				DIO_u8SetPinValue(DIO_u8PORTB,DIO_u8PIN1,DIO_u8PIN_HIGH);
				SPI_Flag = False;
				break;

			case 'h':
				DIO_u8SetPinValue(DIO_u8PORTB,DIO_u8PIN1,DIO_u8PIN_LOW);
				SPI_Flag = False;
				break;

			case 'i':
				DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN1,DIO_u8PIN_HIGH);
				SPI_Flag = False;
				break;

			case 'j':
				DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN1,DIO_u8PIN_LOW);
				SPI_Flag = False;
				break;

			case 'k':
				DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN4,DIO_u8PIN_HIGH);
				SPI_Flag = False;
				break;

			case 'l':
				DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN4,DIO_u8PIN_LOW);
				SPI_Flag = False;
				break;

			case 'm':
				DIO_u8SetPinValue(DIO_u8PORTB,DIO_u8PIN2,DIO_u8PIN_HIGH);
				SPI_Flag = False;
				break;

			case 'n':
				DIO_u8SetPinValue(DIO_u8PORTB,DIO_u8PIN2,DIO_u8PIN_LOW);
				SPI_Flag = False;
				break;

			case 'o':
				DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN2,DIO_u8PIN_HIGH);
				SPI_Flag = False;
				break;

			case 'p':
				DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN2,DIO_u8PIN_LOW);
				SPI_Flag = False;
				break;

			case 'q':
				DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN5,DIO_u8PIN_HIGH);
				SPI_Flag = False;
				break;

			case 'r':
				DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN5,DIO_u8PIN_LOW);
				SPI_Flag = False;
				break;


			}

		}


		if( ADC_Flag == True )
		{
			CLCD_GoToXY(1,10);
			CLCD_voidWriteNumber(Channel_Result[0]/2);

			CLCD_GoToXY(2,10);
			CLCD_voidWriteNumber(Channel_Result[1]/2);

			CLCD_GoToXY(3,10);
			CLCD_voidWriteNumber(Channel_Result[2]/2);

			StartChainConversionAsynch(&adc_Chain);
			ADC_Flag = False;
		}


	}

	return 0;
}


void ADC_NotifyFunc(void)
{

	ADC_Flag = True;
}

void SPI_NotifyFunc(void)
{
	SPI_Flag = True;
}

u32 Calc_Temp(u16 ADC_Reading)
{
  u32 Result = (ADC_Reading*5000)/1023;
  Result /= 10;
  return Result;
}


