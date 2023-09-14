/******************************************************/
/******************************************************/
/***************  Author:Mazen Ibrahim   **************/
/***************  Layer:  HAL            **************/
/***************  SWC: CLCD              **************/
/***************  Version: 1.00           *************/
/******************************************************/
/******************************************************/


#ifndef CLCD_INTERFACE_H_
#define CLCD_INTERFACE_H_

void CLCD_voidSendCommand(u8 Copy_u8Command);
void CLCD_voidSendData(u8 Copy_u8Data);
void CLCD_voidInit(void);
void CLCD_voidSendString(const char* Copy_pcString);
void CLCD_GoToXY(u8 Copy_u8XPos, u8 Copy_u8YPos);
void CLCD_voidWriteSpecialCharater(u8 *Copy_u8Pattern, u8 Copy_u8PatternNumber,u8 XPos , u8 YPos);
void CLCD_voidWriteNumber(u32 Copy_u32Number);



#endif
