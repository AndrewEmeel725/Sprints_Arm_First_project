
#ifndef Input_H_
#define Input_H_

/**********************************************************************************************************************
* INCLUDES
*********************************************************************************************************************/
#include "Service_Types.h"
#include "Button.h"
 
/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS PROTOTYPES
 *********************************************************************************************************************/


uint8 Input_GetNumOfPresses(Service_DeviceChannel MasterDeviceChannel, Service_DeviceChannel MasterStatusChannel,\
							Service_DeviceChannel SlaveDeviceChannel, Service_DeviceChannel SlaveStatusChannel,\
							Button_ButtonAttachType ButtonAttach);
 
#endif /* Input_H_ */
