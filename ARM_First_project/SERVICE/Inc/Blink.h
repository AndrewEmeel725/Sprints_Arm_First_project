

 *********************************************************************************************************************/
#ifndef BLINK_H_
#define BLINK_H_

/**********************************************************************************************************************
* INCLUDES
*********************************************************************************************************************/
#include "Service_Types.h"
 
/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS PROTOTYPES
 *********************************************************************************************************************/

void Start_Blink(Service_TimerChannelType TimerChannle, Service_DeviceChannel DeviceChannel, Service_TimeType Time, Service_HighPeriodType HighPeriod, Service_LowPeriodType LowPeriod);
 

void Stop_Blink(Service_DeviceChannel DeviceChannel);
 
#endif /* LED_H_ */
