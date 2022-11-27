
#ifndef DIO_H_
#define DIO_H_

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"
#include "Dio_Cfg.h"

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS PROTOTYPES
 *********************************************************************************************************************/

Dio_LevelType Dio_ReadChannel(Dio_ChannelType ChannelId);


void Dio_WriteChannel(Dio_ChannelType ChannelId, Dio_LevelType Level);


Dio_LevelType Dio_FlipChannel(Dio_ChannelType ChannelId);


Dio_PortLevelType Dio_ReadPort(Dio_PortType PortId);


 
#endif  /* DIO_H_ */
