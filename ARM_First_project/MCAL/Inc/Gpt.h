
#ifndef Gpt_H_
#define Gpt_H_

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"
#include "Gpt_Types.h"
#include "Gpt_Cfg.h"

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS PROTOTYPES
 *********************************************************************************************************************/

void Gpt_Init(const Gpt_ChannelConfigType* ConfigPtr);


void Gpt_DisableNotification(Gpt_ChannelType ChannelId);


void Gpt_EnableNotification(Gpt_ChannelType ChannelId);


void Gpt_StartTimer(Gpt_ChannelType ChannelId, Gpt_ValueType Value);


void Gpt_StopTimer(Gpt_ChannelType ChannelId);


Gpt_ValueType Gpt_GetTimeElapsed(Gpt_ChannelType ChannelId);

Gpt_ValueType Gpt_GetTimeRemaining(Gpt_ChannelType ChannelId);

Std_ReturnType Gpt_GetPredefTimerValue(Gpt_PredefTimerType PredefTimer, uint32* TimeValuePtr);
 
#endif  /* Gpt_H_ */


