
 
 /**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"
#include "Led.h"
#include "Port.h"

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

void Led_Init(void)
{
	Port_Init(&Port_ConfigType);
}
 

void Led_TurnOn(Led_LedChannelType LedChannel)
{
	Dio_WriteChannel(LedChannel, DIO_LEVEL_HIGH);
}
 

void Led_TurnOff(Led_LedChannelType LedChannel)
{
	Dio_WriteChannel(LedChannel, DIO_LEVEL_LOW);
}


void Led_Toggle(Led_LedChannelType LedChannel)
{
	Dio_FlipChannel(LedChannel);
}


void Led_RefreshOutput(Led_LedChannelType LedChannel)
{
	/* Read the current state */
    Dio_LevelType state = Dio_ReadChannel(LedChannel);
	
	/* Re-write the same state */
    Dio_WriteChannel(LedChannel, state);
}
 