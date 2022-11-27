
#ifndef SERVICE_TYPES_H_
#define SERVICE_TYPES_H_

/**********************************************************************************************************************
* INCLUDES
*********************************************************************************************************************/
#include "Std_Types.h"
#include "Led.h"
#include "Button.h"
#include "Dio.h"
#include "Gpt.h"

/**********************************************************************************************************************
*  GLOBAL DATA PROTOTYPES
*********************************************************************************************************************/
typedef Led_LedChannelType Service_DeviceChannel; /* We use it as  Button_ButtonChannelType too */

typedef uint16 Service_TimeType;

typedef uint8 Service_HighPeriodType;

typedef uint8 Service_LowPeriodType;

typedef Gpt_ChannelType Service_TimerChannelType;
 
 
#endif /* SERVICE_TYPES_H_ */
