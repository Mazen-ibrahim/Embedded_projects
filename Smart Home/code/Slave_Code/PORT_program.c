/******************************************************/
/******************************************************/
/***************  Author:Mazen Ibrahim   **************/
/***************  Layer:  MCAL           **************/
/***************  SWC: PORT              **************/
/***************  Version: 1.00           *************/
/******************************************************/
/******************************************************/

#include "STD_TYPES.h"
#include "PORT_config.h"
#include "PORT_private.h"
#include "PORT_interface.h"
#include "PORT_register.h"

void PORT_voidInit(void)
{
     DDRA = PORTA_DIR ;
     DDRB = PORTB_DIR ;
     DDRC = PORTC_DIR ;
     DDRD = PORTD_DIR ;

     PORTA = PORTA_VALUES;
     PORTB = PORTB_VALUES;
     PORTC = PORTC_VALUES;
     PORTD = PORTD_VALUES;

}
