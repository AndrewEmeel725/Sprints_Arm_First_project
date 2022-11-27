
#ifndef LED_H_
#define LED_H_

/**********************************************************************************************************************
* INCLUDES
*********************************************************************************************************************/
#include "Std_Types.h"
#include "Dio.h"
 
/**********************************************************************************************************************
*  GLOBAL DATA PROTOTYPES
*********************************************************************************************************************/
typedef Dio_ChannelType Led_LedChannelType;
 
 /**********************************************************************************************************************
 *  GLOBAL FUNCTIONS PROTOTYPES
 *********************************************************************************************************************/

 void Led_Init(void);
 

 void Led_TurnOn(Led_LedChannelType LedChannel);
 
 
 void Led_TurnOff(Led_LedChannelType LedChannel);
 
 
void Led_Toggle(Led_LedChannelType LedChannel);


void Led_RefreshOutput(Led_LedChannelType LedChannel);
 
 #endif /* LED_H_ */
 