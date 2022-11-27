

/**********************************************************************************************************************
*  INCLUDES
*********************************************************************************************************************/
#include "Input.h"
#include "Led.h"
#include "Macros.h"

/**********************************************************************************************************************
 *  STATIC GLOBAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

uint8 Input_GetNumOfPresses(Service_DeviceChannel MasterDeviceChannel, Service_DeviceChannel MasterStatusChannel, Service_DeviceChannel SlaveDeviceChannel, Service_DeviceChannel SlaveStatusChannel, Button_ButtonAttachType ButtonAttach)
{
	/* Initialize all the devices */
	Led_Init();
	Button_Init();
	
	uint8 pulses = 0;
	
	/* Don't advance until the user give an acka that he will enter an input */
	while (Button_GetState(MasterDeviceChannel, ButtonAttach) == BUTTON_RELEASED);
	
	/* Let the user now, we were listening to him */
	Led_TurnOn(MasterStatusChannel);
	
	/* wait a little bit */
	for(int i = 0; i < 1000000; i++);
	
	/* Revert all changes */
	Led_TurnOff(MasterStatusChannel);
	
	for(;;)
	{
		if (Button_GetState(MasterDeviceChannel, ButtonAttach) == BUTTON_PRESSED)
		{
			/* Let the user now, we were listening to him */
			Led_TurnOn(MasterStatusChannel);
			
			/* wait a little bit */
			for(int i = 0; i < 1000000; i++);
			
			/* Revert all changes */
			Led_TurnOff(MasterStatusChannel);
			
			break;
		}
		else if (Button_GetState(SlaveDeviceChannel, ButtonAttach) == BUTTON_PRESSED)
		{
			/* Let the user now, we are listening to him */
			Led_TurnOn(SlaveStatusChannel);
			
			/* wait a little bit */
			for(int i = 0; i < 1000000; i++);
			
			/* Revert all changes */
			Led_TurnOff(SlaveStatusChannel);
			
			/* Accumulate the number of pulses */
			pulses++;
		}
	}
	
	/* wait a little bit */
	for(int i = 0; i < 1000000; i++);
	
	/* Pass the number of pulses */
	return pulses;
}

