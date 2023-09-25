/******************************************************/
/******************************************************/
/***************  Author:Mazen Ibrahim   **************/
/***************  Layer:  MCAL           **************/
/***************  SWC: ADC               **************/
/***************  Version: 1.00           *************/
/******************************************************/
/******************************************************/

#ifndef ADC_CONFIG_H_
#define ADC_CONFIG_H_
/*
 Options:
         1-AVCC
         2-AREF
         3-INTERNAL_VCC
 */
#define ADC_RefVoltage  AVCC

/*
 Options:
         1-Enable_LRA
         2-Disable_LRA
 */
#define ADC_LRA      Disable_LRA


/*
 Options:
         1-Enable
         2-Disable
 */
#define ADC_Enable      Enable


/*
 Options:
         1-two
         2-four
         3-eight
         4-sixthteen
         5-thirtyTwo
         6-Sixthfour
         7-oneTwenyEight
 */
#define ADC_PreScaler    oneTwenyEight

#define SizeOfchannel    4

#endif
