/******************************************************/
/******************************************************/
/***************  Author:Mazen Ibrahim   **************/
/***************  Layer:  MCAL           **************/
/***************  SWC: ADC               **************/
/***************  Version: 1.00           *************/
/******************************************************/
/******************************************************/

#ifndef ADC_REGISTER_H
#define ADC_REGISTER_H

//***********************************
#define ADMUX    *((volatile u8*)0x27)             //ADC  Multiplexer selection Register
#define ADMUX_REFS1  7                             //ADC  Reference Selection bit_1
#define ADMUX_REFS0  6                             //ADC  Reference Selection bit_0
#define ADMUX_ADLRA  5                             //ADC Left Right Adjust
//***********************************             

//***********************************
#define ADCSRA   *((volatile u8*)0x26)             //ADC control and status register
#define ADCSRA_ADEN   7                            //ADC enable
#define ADCSRA_ADSC   6                            //ADC start conversion
#define ADCSRA_ADATE  5                            //ADC Auto trigger enable
#define ADCSRA_ADIF   4                            //ADC interrupt flag
#define ADCSRA_ADIE   3                            //ADC interrupt enable
#define ADCSRA_ADPS2  2                            //prescaler bit2
#define ADCSRA_ADPS1  1                            //prescaler bit1
#define ADCSRA_ADPS0  0                            //prescaler bit0
//***********************************


#define ADCH     *((volatile u8*)0x25)             //ADC High register
#define ADCL     *((volatile u8*)0x24)             //ADC LOW register
#define ADC      *((volatile u16*)0x24)            //ADC 10 bits


#endif
