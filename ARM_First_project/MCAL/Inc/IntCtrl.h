
#ifndef INTCTRL_H_
#define INTCTRL_H_

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"
#include "IntCtrl_Cfg.h"
 
/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

void IntCrtl_Init(void);


void IntCtrl_EnableInterrupt(IntCtrl_InterruptType InterruptId, IntCtrl_PriorityLevel Priority);

void IntCtrl_DisableInterrupt(IntCtrl_InterruptType InterruptId);
 
#endif  /* INTCTRL_H_ */

