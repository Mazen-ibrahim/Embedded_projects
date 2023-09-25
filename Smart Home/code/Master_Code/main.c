#include <util/delay.h>
#include "STD_TYPES.h"
#include "Configuration.h"
#include "DIO_inteface.h"
#include "DIO_private.h"
#include "PORT_interface.h"
#include "SPI_interface.h"
#include "GIE_interface.h"
#include "CLCD_interface.h"
#include "KEYPAD_interface.h"







int main(void)
{


	u8 Key = 0;
	u8 Default_Pass[] = {'8','1','5','2'};
	u8 Attempts = 3;
	u8 Counter = 0;
	u8 Index = 0;
	u8 CheckExit = False;


	//Initialize PORTS
	PORT_voidInit();

	//Initialize SPI
	SPI_void_MasterInit();

	//Initialize CLCD
	CLCD_voidInit();

	CLCD_voidSendString("     * Welcome *      ");
	CLCD_GoToXY(1,0);
	CLCD_voidSendString("  ** Smart Home **  ");
	CLCD_GoToXY(2,0);
	CLCD_voidSendString("Enter Password:");
	CLCD_GoToXY(3,0);
	CLCD_voidSendData(Attempts+48);
	CLCD_voidSendString(" attempts:");

	while(1)
	{

		// 1-Get Password From User and Check it
		CheckExit = False;
		CLCD_GoToXY(3,11);
		for( Index = 0 ; Index < PASS_Num ; Index++ )
		{
			Key =  KPD_u8WaitForKey();
			CLCD_voidSendData('*');
			if(Default_Pass[Index] == Key)
				Counter++;

		}


		while( Counter == PASS_Num)
		{

			CLCD_voidWrite_4Lines(" 1) Room (1)"," 2) Room (2)"," 3) Room (3)"," 4) Exit");
			Key =  KPD_u8WaitForKey();

			if( Key == '1' )
			{
				while(1)
				{
					CLCD_voidWrite_4Lines(" 1) Light "," 2) Heater "," 3) Air Conditioner "," 4) Return  ");


					Key =  KPD_u8WaitForKey();
					if( '1' == Key )
					{
						while(1)
						{
							CLCD_voidWrite_4Lines("Room (1) Light"," 1) Light On"," 2) Light Off"," 3) Return");

							Key =  KPD_u8WaitForKey();
							if( '1' == Key )
							{

								SPI_u8_Synctransceive('a');
							}

							else if( '2' ==  Key )
							{

								SPI_u8_Synctransceive('b');

							}

							else if ( '3' == Key )
							{
								break;
							}
						}


					}

					else if( '2' == Key)
					{
						while(1)
						{
							CLCD_voidWrite_4Lines("Room (1) Heater"," 1) Heater On"," 2) Heater Off"," 3) Return");
							Key =  KPD_u8WaitForKey();
							if( '1' == Key )
							{
								SPI_u8_Synctransceive('c');
							}

							else if( '2' ==  Key )
							{

								SPI_u8_Synctransceive('d');

							}
							else if ( '3' == Key )
							{
								break;
							}

						}

					}

					else if ( '3' == Key )
					{
						while(1)
						{
							CLCD_voidWrite_4Lines("Room (1) Air"," 1) Air On"," 2) Air Off"," 3) Return");
							Key =  KPD_u8WaitForKey();
							if( '1' == Key )
							{
								SPI_u8_Synctransceive('e');

							}

							else if( '2' ==  Key )
							{

								SPI_u8_Synctransceive('f');

							}

							else if ( '3' == Key )
							{
								break;
							}

						}

					}

					else if( '4' == Key )
					{
						break;

					}
				}



			}

			else if ( Key == '2' )
			{

				while(1)
				{
					CLCD_voidWrite_4Lines(" 1) Light "," 2) Heater "," 3) Air Conditioner "," 4) Return  ");

					Key =  KPD_u8WaitForKey();
					if( '1' == Key )
					{
						while(1)
						{
							CLCD_voidWrite_4Lines("Room (2) Light"," 1) Light On"," 2) Light Off"," 3) Return");
							Key =  KPD_u8WaitForKey();
							if( '1' == Key )
							{

								SPI_u8_Synctransceive('g');
							}

							else if( '2' ==  Key )
							{

								SPI_u8_Synctransceive('h');

							}

							else if( '3' == Key )
							{
								break;
							}
						}

					}

					else if( '2' == Key)
					{

						while(1)
						{

							CLCD_voidWrite_4Lines("Room (2) Heater"," 1) Heater On"," 2) Heater Off", " 3) Return");
							Key =  KPD_u8WaitForKey();
							if( '1' == Key )
							{
								SPI_u8_Synctransceive('i');

							}

							else if( '2' ==  Key )
							{


								SPI_u8_Synctransceive('j');
							}

							else if ( '3' == Key )
							{
								break;
							}
						}

					}

					else if ( '3' == Key )
					{
						while(1)
						{

							CLCD_voidWrite_4Lines("Room (2) Air "," 1) Air On "," 2) Air Off "," 3) Return");
							Key =  KPD_u8WaitForKey();
							if( '1' == Key )
							{

								SPI_u8_Synctransceive('k');
							}

							else if( '2' ==  Key )
							{

								SPI_u8_Synctransceive('l');

							}

							else if( '3' == Key )
							{
								break;
							}

						}

					}

					else if ( '4' == Key)
					{
						break;

					}
				}
			}

			else if( Key == '3' )
			{
				while(1)
				{
					CLCD_voidWrite_4Lines(" 1) Light "," 2) Heater "," 3) Air Conditioner "," 4) Return  ");

					Key =  KPD_u8WaitForKey();
					if( '1' == Key )
					{
						while(1)
						{
							CLCD_voidWrite_4Lines("Room (3) Light"," 1) Light On"," 2) Light Off"," 3) Return");
							Key =  KPD_u8WaitForKey();
							if( '1' == Key )
							{

								SPI_u8_Synctransceive('m');
							}

							else if( '2' ==  Key )
							{
								SPI_u8_Synctransceive('n');

							}

							else if( '3' == Key)
							{
								break;
							}
						}

					}

					else if( '2' == Key)
					{
						while(1)
						{
							CLCD_voidWrite_4Lines("Room (3) Heater"," 1) Heater On"," 2) Heater Off"," 3) Return");
							Key =  KPD_u8WaitForKey();
							if( '1' == Key )
							{

								SPI_u8_Synctransceive('o');
							}

							else if( '2' ==  Key )
							{

								SPI_u8_Synctransceive('p');
							}

							else if ( '3' == Key )
							{
								break;
							}
						}

					}

					else if ( '3' == Key )
					{
						while(1)
						{
							CLCD_voidWrite_4Lines("Room (3) Air"," 1) Air On"," 2) Air Off"," 3) Return");
							Key =  KPD_u8WaitForKey();
							if( '1' == Key )
							{

								SPI_u8_Synctransceive('q');
							}

							else if( '2' ==  Key )
							{

								SPI_u8_Synctransceive('r');

							}

							else if ( '3' == Key)
							{
								break;
							}
						}

					}

					else if ( '4' == Key)
					{
						break;

					}
				}

			}


			else
			{
				Counter = 0;
				Attempts = 3;
				CheckExit = True;
				CLCD_voidSendCommand(CLEAR_DISPLAY);
				CLCD_voidSendString("     * Welcome *      ");
				CLCD_GoToXY(1,0);
				CLCD_voidSendString("  ** Smart Home **  ");
				CLCD_GoToXY(2,0);
				CLCD_voidSendString("Enter Password:");
				CLCD_GoToXY(3,0);
				CLCD_voidSendData(Attempts+48);
				CLCD_voidSendString(" attempts:");

			}


		}

		if(Counter !=  PASS_Num && CheckExit == False )
		{
			CLCD_GoToXY(2,0);
			CLCD_voidSendString("Enter Password:");
			CLCD_GoToXY(3,0);
			CLCD_voidSendData(--Attempts+48);
			CLCD_voidSendString(" attempts:      ");
			if(Attempts == 0)
			{
				CLCD_voidSendCommand(CLEAR_DISPLAY);
				CLCD_GoToXY(2,0);
				CLCD_voidSendString("  **System Locked**  ");
				while(1);
			}

			Counter = 0;

		}





	}


	return 0;

}


