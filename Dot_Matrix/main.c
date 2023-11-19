#include<util/delay.h>
#include "DIO_inteface.h"
#include "DIO_register.h"
#include "PORT_interface.h"
#include "DotMatrix_interface.h"


int main(void)
{
	Dot_Matrix_INIT();

	while(1)
	{
		u8 i = 0;
		for( i = 'A' ; i <='Z' ; i++)
			Dot_Draw_Letter(i);

		for( i = '0' ; i <= '9'; i++)
		   Dot_Draw_Number(i);

	}

}


