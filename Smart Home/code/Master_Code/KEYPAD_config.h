/******************************************************/
/******************************************************/
/***************  Author:Mazen Ibrahim   **************/
/***************  Layer:  MCAL           **************/
/***************  SWC: KEYPAD            **************/
/***************  Version: 1.00          **************/
/******************************************************/
/******************************************************/

#ifndef  KEYPAD_CONFIG_H
#define  KEYPAD_CONFIG_H

#define KPD_PORT           DIO_u8PORTC

#define KPD_COLUMN0_PIN    DIO_u8PIN0
#define KPD_COLUMN1_PIN    DIO_u8PIN1
#define KPD_COLUMN2_PIN    DIO_u8PIN2

#define KPD_ROW0_PIN       DIO_u8PIN4
#define KPD_ROW1_PIN       DIO_u8PIN5
#define KPD_ROW2_PIN       DIO_u8PIN6
#define KPD_ROW3_PIN       DIO_u8PIN7

#define KPD_No_PressedKey  0xff

#define KPD_ARR          {{49,50,51},{52,53,54},{55,56,57},{42,48,35}}


#endif
