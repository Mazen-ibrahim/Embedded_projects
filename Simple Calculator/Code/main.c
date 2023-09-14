#include "STD_TYPES.h"
#include <util/delay.h>
#include "PORT_interface.h"
#include "CLCD_interface.h"
#include "KEYPAD_interface.h"

#define KPD_No_PressedKey  0xff
#define CLEAR_DISPLAY      0b0000001
#define CLEAR_BUTTON       46
#define Counter_Zero       0
#define True               1
#define False              0



void main()
{

	//Initialize PORTS
	PORT_voidInit();

	//Initialize CLCD
	CLCD_voidInit();

	CLCD_voidSendString("   Calculator  ");
	_delay_ms(200);
	CLCD_voidSendCommand(CLEAR_DISPLAY);


	u8  Index_Num = 0;
	u8  Index_Sign = 0;
	u8  Index = 0;
	u8  Check = True;
	u8  Key = 0;
	u8  Numbers[10] = {0};
	u8  Signs[10] = {0};
	f32 Final_Result = Counter_Zero;
	u32 Integer = 0;
	u32 Fraction = 0;

	while(1)
	{
		Key = KPD_u8GETPressedKey();
		if(Key != KPD_No_PressedKey)
		{
			if(Key == CLEAR_BUTTON)
			{
				CLCD_voidSendCommand(CLEAR_DISPLAY);

				for( Index = 0 ; Index <=Index_Num ; Index++ )
				{
					Numbers[Index] = 0;
					Signs[Index] = 0;
				}

				Index_Num  = Counter_Zero;
				Index_Sign = Counter_Zero;
				Check = True;


			}


			else if(Key != '=')
			{
				CLCD_voidSendData(Key);
				if( Key >= '0' && Key <= '9' )
				{
					Numbers[Index_Num] = Numbers[Index_Num]*10 + (Key-48);

				}
				else
				{
					Signs[Index_Sign] = Key;
					Index_Num++;
					Index_Sign++;

				}

			}


			else
			{

				Final_Result = Numbers[0];
				for( Index = 0 ; Index < Index_Sign ; Index++)
				{

					switch(Signs[Index])
					{
					case '+': Final_Result += Numbers[Index+1]; break;
					case '*': Final_Result *= Numbers[Index+1]; break;
					case '-': Final_Result -= Numbers[Index+1]; break;
					case '/':
						if(Numbers[Index+1] != 0)
						{
							Final_Result /= Numbers[Index+1];
						}
						else
						{
							CLCD_voidSendCommand(CLEAR_DISPLAY);
							CLCD_voidSendString("   Math Error  ");
							Check = False;

						}

						break;

					default:
						CLCD_voidSendCommand(CLEAR_DISPLAY);
						CLCD_voidSendString("   Math Error  ");
						Check = False;
					}
				}

				if(Check == True)
				{
					Integer  = Final_Result;
					Fraction = (Final_Result-Integer)*10;
					CLCD_GoToXY(1,0);
					CLCD_voidSendString("Result:");
					CLCD_voidWriteNumber(Integer);

					if(Fraction != 0)
					{
						CLCD_voidSendData('.');
						CLCD_voidWriteNumber(Fraction);
					}




				}



			}

		}

	}


}


