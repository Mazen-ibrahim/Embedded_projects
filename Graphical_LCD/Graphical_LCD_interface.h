/******************************************************/
/******************************************************/
/***************  Author: Mazen Ibrahim  **************/
/***************  Layer: HAL             **************/
/***************  SWC: GLCD              **************/
/***************  Version: 1.00          **************/
/******************************************************/
/******************************************************/

#ifndef GLCD_INTERFACE_H_
#define GLCD_INTERFACE_H_


/*
 * @brief : Define Enum to Hold GLCD_Half
 */
typedef enum
{
  GLCD_CS1,
  GLCD_CS2

}HALF_SELECT;


/*****************************************
 * @brief : Used to Send Command to GLCD *
 * @param : command to send to GLCD      *
 * @return: void                         *
 *                                       *
 ****************************************/

void GLCD_SendCommand(u8 copy_u8Command);

/**************************************
 * @brief : Used to Send Data to GLCD *
 * @param : Data to send to GLCD      *
 * @return: void                      *
 *                                    *
 *************************************/

void GLCD_SendData(u8 copy_u8Data);


/*************************************
 * @brief : Used to Initialize GLCD  *
 * @param : void                     *
 * @return: void                     *
 *                                   *
 ************************************/
void GLCD_Init();


/*****************************************
 * @brief : Used to Set X and Y Position *
 * @param : X and Y Position             *
 * @return: void                         *
 *                                       *
 *****************************************/
void GLCD_SET_XY(u8 copy_u8_XPOS , u8 copy_u8_YPOS);




/*****************************************
 * @brief : Used to Clear GLCD           *
 * @param : void                         *
 * @return: void                         *
 *                                       *
 *****************************************/
void GLCD_Clear();


/*************************************************
 * @brief : Used to Draw Image 128X64 Pixel Size *
 * @param : array of Image Data                  *
 * @return: void                                 *
 *************************************************/
void GLCD_FullImage(u8 *ImageData);



/************************************************
 * @brief : Used to Draw Image 64X64 Pixel Size *
 * @param : array of Image Data                 *
 * @param : select Half (GLCD_CS1,GLCD_CS2)     *
 * @return: void                                *
 ************************************************/
void GLCD_64X64Image(u8 *ImageData, HALF_SELECT Image_Half);


#endif
