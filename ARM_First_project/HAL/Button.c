
 /**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"
#include "Button.h"

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

void Button_Init(void)
{
	Port_Init(&Port_ConfigType);
}
 

Button_State Button_GetState(Button_ButtonChannelType ButtonChannel, Button_ButtonAttachType ButtonAttach)
{
	Dio_LevelType testLevel = DIO_LEVEL_LOW;
	
	if (ButtonAttach == PULL_UP)
		testLevel = DIO_LEVEL_LOW;
	else if (ButtonAttach == PULL_DOWN)
		testLevel = DIO_LEVEL_HIGH;
	
	if (Dio_ReadChannel(ButtonChannel) == testLevel)
	{
		/* Random short delay */
		for(int i = 0; i < 1000; i++);
		
		if (Dio_ReadChannel(ButtonChannel) == testLevel)
		{
			return BUTTON_PRESSED;
		}
		else
		{
			return BUTTON_RELEASED;
		}
	}
	else
	{
		return BUTTON_RELEASED;
	}
}

 