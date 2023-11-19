/******************************************************/
/******************************************************/
/***************  Author:Mazen Ibrahim   **************/
/***************  Layer:  HAL            **************/
/***************  SWC: DOT Matrix        **************/
/***************  Version: 1.00          **************/
/******************************************************/
/******************************************************/

#ifndef DOT_CONFIG_H_
#define DOT_CONFIG_H_

/*
 * Options :
 * 1-DIO_u8PORTA
 * 2-DIO_u8PORTB
 * 3-DIO_u8PORTC
 * 4-DIO_u8PORTD
 */


#define DOT_COLUMN_PORT  DIO_u8PORTC
#define DOT_ROW_PORT     DIO_u8PORTB

/*
 * Options :
 * 1- _5X7
 * 2- _8X8
 */

#define DOT_MATRIX_TYPE    _8X8



#endif
