
 #ifndef BUTTON_H_
 #define BUTTON_H_
 
/**********************************************************************************************************************
* INCLUDES
*********************************************************************************************************************/
#include "Std_Types.h"
#include "Port.h"
#include "Dio.h"

/**********************************************************************************************************************
*  GLOBAL DATA PROTOTYPES
*********************************************************************************************************************/
typedef Dio_ChannelType Button_ButtonChannelType;
typedef Port_PinInternalAttachType Button_ButtonAttachType;

typedef enum
{
	BUTTON_RELEASED = 0,
	BUTTON_PRESSED = 1
} Button_State;

/**********************************************************************************************************************
*  GLOBAL FUNCTIONS PROTOTYPES
*********************************************************************************************************************/

void Button_Init(void);
 

Button_State Button_GetState(Button_ButtonChannelType ButtonChannel, Button_ButtonAttachType ButtonAttach);

 #endif /* BUTTON_H_ */
 