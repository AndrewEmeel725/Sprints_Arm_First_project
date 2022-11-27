

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"
#include "Gpt.h"
#include "IntCtrl.h"
#include "Gpt_regs.h"
#include "Mcu_Hw.h"
#include "Macros.h"

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

void Gpt_Init(const Gpt_ChannelConfigType* ConfigPtr)
{
	if (ConfigPtr->isEnabled == DISABLED)
		return;
	
	/* Should disable all the interrupts until finishing the configurations initializations */
	INTERRUPTS_DISABLE
	
	volatile uint8* channelPtr = NULL_PTR;
	volatile Gpt_TimerInterruptType interruptId = 0;
	
	/* Enable the clock to the dedicated channel */
	switch (ConfigPtr->channelId)
	{
		case TIMER0_16BIT:
			channelPtr = (volatile uint8*)GPT_16BIT_TIMER0_BASE_ADDRESS;
			interruptId = TIMER_16_32_BIT_0A;
			SYSCTL_RCGCTIMER.R0 = 1;
			break;
		case TIMER1_16BIT:
			channelPtr = (volatile uint8*)GPT_16BIT_TIMER1_BASE_ADDRESS;
			interruptId = TIMER_16_32_BIT_1A;
			SYSCTL_RCGCTIMER.R1 = 1;
			break;
		case TIMER2_16BIT:
			channelPtr = (volatile uint8*)GPT_16BIT_TIMER2_BASE_ADDRESS;
			interruptId = TIMER_16_32_BIT_2A;
			SYSCTL_RCGCTIMER.R2 = 1;
			break;
		case TIMER3_16BIT:
			channelPtr = (volatile uint8*)GPT_16BIT_TIMER3_BASE_ADDRESS;
			interruptId = TIMER_16_32_BIT_3A;
			SYSCTL_RCGCTIMER.R3 = 1;
			break;
		case TIMER4_16BIT:
			channelPtr = (volatile uint8*)GPT_16BIT_TIMER4_BASE_ADDRESS;
			interruptId = TIMER_16_32_BIT_4A;
			SYSCTL_RCGCTIMER.R4 = 1;
			break;
		case TIMER5_16BIT:
			channelPtr = (volatile uint8*)GPT_16BIT_TIMER5_BASE_ADDRESS;
			interruptId = TIMER_16_32_BIT_5A;
			SYSCTL_RCGCTIMER.R5 = 1;
			break;
		case TIMER0_32BIT:
			channelPtr = (volatile uint8*)GPT_32BIT_WIDE_TIMER0_BASE_ADDRESS;
			interruptId = TIMER_32_64_BIT_0A;
			SYSCTL_RCGCWTIMER.R0 = 1;
			break;
		case TIMER1_32BIT:
			channelPtr = (volatile uint8*)GPT_32BIT_WIDE_TIMER1_BASE_ADDRESS;
			interruptId = TIMER_32_64_BIT_1A;
			SYSCTL_RCGCWTIMER.R1 = 1;
			break;
		case TIMER2_32BIT:
			channelPtr = (volatile uint8*)GPT_32BIT_WIDE_TIMER2_BASE_ADDRESS;
			interruptId = TIMER_32_64_BIT_2A;
			SYSCTL_RCGCWTIMER.R2 = 1;
			break;
		case TIMER3_32BIT:
			channelPtr = (volatile uint8*)GPT_32BIT_WIDE_TIMER3_BASE_ADDRESS;
			interruptId = TIMER_32_64_BIT_3A;
			SYSCTL_RCGCWTIMER.R3 = 1;
			break;
		case TIMER4_32BIT:
			channelPtr = (volatile uint8*)GPT_32BIT_WIDE_TIMER4_BASE_ADDRESS;
			interruptId = TIMER_32_64_BIT_4A;
			SYSCTL_RCGCWTIMER.R4 = 1;
			break;
		case TIMER5_32BIT:
			channelPtr = (volatile uint8*)GPT_32BIT_WIDE_TIMER5_BASE_ADDRESS;
			interruptId = TIMER_32_64_BIT_5A;
			SYSCTL_RCGCWTIMER.R5 = 1;
			break;
		default:
			/* [TODO] Report an error, then return */
			return;
	}
	
	/* Enable Interrupt for the dedicated channel from IntCtrl Module */
	IntCtrl_EnableInterrupt(interruptId, ConfigPtr->priority);
	
	/* Ensure the timer is disabled (the TnEN bit in the GPTMCTL register is cleared) before making any changes. */
	GPT_GPTMCTL(channelPtr).TAEN = 0;

	/* Choose 16bit or full 32bit timer for 16/32bit timers, and 32bit or 64bit for 32/64bit timers */
	/* [TODO] Make it generic for half or full mode */
	GPT_GPTMCFG(channelPtr) = 0x00000000;
	
	/* Enable match interrupt */
	GPT_GPTMTAMR(channelPtr).TAMIE = 1;
	
	
	
	/* Configure the TnMR field in the GPTM Timer n Mode Register (GPTMTnMR) */
	/*
		a. Write a value of 0x1 for One-Shot mode.
		b. Write a value of 0x2 for Periodic mode.
	*/
	GPT_GPTMTAMR(channelPtr).TAMR = ConfigPtr->mode;
	
	/* Specify the counting direction which is up or down */
	GPT_GPTMTAMR(channelPtr).TACDIR = ConfigPtr->direction;
	
	/* Update the GPTMTAR and GPTMTAV registers with the value in the GPTMTAILR register on the next timeout. */
	GPT_GPTMTAMR(channelPtr).TAILD = 1;
	
	/* Update the GPTMTAMATCHR register and the GPTMTAPR register, if used, on the next timeout. */
	GPT_GPTMTAMR(channelPtr).TAMRSU = 1;
	
	/* Enable Timeout interrupt */
	GPT_GPTMIMR(channelPtr).TATOIM = 1;
	
	/* Should enable all the interrupts again */
	INTERRUPTS_ENABLE
}


void Gpt_DisableNotification(Gpt_ChannelType ChannelId)
{
	const Gpt_ChannelConfigType* ConfigPtr = &(Gpt_Config.channels[ChannelId]);
	
	volatile uint8* channelPtr = NULL_PTR;
	volatile Gpt_TimerInterruptType interruptId = 0;
	
	/* Determine the channel address and the interruptId */
	switch (ConfigPtr->channelId)
	{
		case TIMER0_16BIT:
			channelPtr = (volatile uint8*)GPT_16BIT_TIMER0_BASE_ADDRESS;
			interruptId = TIMER_16_32_BIT_0A;
			break;
		case TIMER1_16BIT:
			channelPtr = (volatile uint8*)GPT_16BIT_TIMER1_BASE_ADDRESS;
			interruptId = TIMER_16_32_BIT_1A;
			break;
		case TIMER2_16BIT:
			channelPtr = (volatile uint8*)GPT_16BIT_TIMER2_BASE_ADDRESS;
			interruptId = TIMER_16_32_BIT_2A;
			break;
		case TIMER3_16BIT:
			channelPtr = (volatile uint8*)GPT_16BIT_TIMER3_BASE_ADDRESS;
			interruptId = TIMER_16_32_BIT_3A;
			break;
		case TIMER4_16BIT:
			channelPtr = (volatile uint8*)GPT_16BIT_TIMER4_BASE_ADDRESS;
			interruptId = TIMER_16_32_BIT_4A;
			break;
		case TIMER5_16BIT:
			channelPtr = (volatile uint8*)GPT_16BIT_TIMER5_BASE_ADDRESS;
			interruptId = TIMER_16_32_BIT_5A;
			break;
		case TIMER0_32BIT:
			channelPtr = (volatile uint8*)GPT_32BIT_WIDE_TIMER0_BASE_ADDRESS;
			interruptId = TIMER_32_64_BIT_0A;
			break;
		case TIMER1_32BIT:
			channelPtr = (volatile uint8*)GPT_32BIT_WIDE_TIMER1_BASE_ADDRESS;
			interruptId = TIMER_32_64_BIT_1A;
			break;
		case TIMER2_32BIT:
			channelPtr = (volatile uint8*)GPT_32BIT_WIDE_TIMER2_BASE_ADDRESS;
			interruptId = TIMER_32_64_BIT_2A;
			break;
		case TIMER3_32BIT:
			channelPtr = (volatile uint8*)GPT_32BIT_WIDE_TIMER3_BASE_ADDRESS;
			interruptId = TIMER_32_64_BIT_3A;
			break;
		case TIMER4_32BIT:
			channelPtr = (volatile uint8*)GPT_32BIT_WIDE_TIMER4_BASE_ADDRESS;
			interruptId = TIMER_32_64_BIT_4A;
			break;
		case TIMER5_32BIT:
			channelPtr = (volatile uint8*)GPT_32BIT_WIDE_TIMER5_BASE_ADDRESS;
			interruptId = TIMER_32_64_BIT_5A;
			break;
		default:
			/* [TODO] Report an error, then return */
			return;
	}
	
	/* Disable Timeout interrupt */
	GPT_GPTMIMR(channelPtr).TATOIM = 0;
	
	/* Enable Interrupt for the dedicated channel from IntCtrl Module */
	IntCtrl_DisableInterrupt(interruptId);
}


void Gpt_EnableNotification(Gpt_ChannelType ChannelId)
{
	const Gpt_ChannelConfigType* ConfigPtr = &(Gpt_Config.channels[ChannelId]);
	
	volatile uint8* channelPtr = NULL_PTR;
	volatile Gpt_TimerInterruptType interruptId = 0;
	
	/* Determine the channel address and the interruptId */
	switch (ConfigPtr->channelId)
	{
		case TIMER0_16BIT:
			channelPtr = (volatile uint8*)GPT_16BIT_TIMER0_BASE_ADDRESS;
			interruptId = TIMER_16_32_BIT_0A;
			break;
		case TIMER1_16BIT:
			channelPtr = (volatile uint8*)GPT_16BIT_TIMER1_BASE_ADDRESS;
			interruptId = TIMER_16_32_BIT_1A;
			break;
		case TIMER2_16BIT:
			channelPtr = (volatile uint8*)GPT_16BIT_TIMER2_BASE_ADDRESS;
			interruptId = TIMER_16_32_BIT_2A;
			break;
		case TIMER3_16BIT:
			channelPtr = (volatile uint8*)GPT_16BIT_TIMER3_BASE_ADDRESS;
			interruptId = TIMER_16_32_BIT_3A;
			break;
		case TIMER4_16BIT:
			channelPtr = (volatile uint8*)GPT_16BIT_TIMER4_BASE_ADDRESS;
			interruptId = TIMER_16_32_BIT_4A;
			break;
		case TIMER5_16BIT:
			channelPtr = (volatile uint8*)GPT_16BIT_TIMER5_BASE_ADDRESS;
			interruptId = TIMER_16_32_BIT_5A;
			break;
		case TIMER0_32BIT:
			channelPtr = (volatile uint8*)GPT_32BIT_WIDE_TIMER0_BASE_ADDRESS;
			interruptId = TIMER_32_64_BIT_0A;
			break;
		case TIMER1_32BIT:
			channelPtr = (volatile uint8*)GPT_32BIT_WIDE_TIMER1_BASE_ADDRESS;
			interruptId = TIMER_32_64_BIT_1A;
			break;
		case TIMER2_32BIT:
			channelPtr = (volatile uint8*)GPT_32BIT_WIDE_TIMER2_BASE_ADDRESS;
			interruptId = TIMER_32_64_BIT_2A;
			break;
		case TIMER3_32BIT:
			channelPtr = (volatile uint8*)GPT_32BIT_WIDE_TIMER3_BASE_ADDRESS;
			interruptId = TIMER_32_64_BIT_3A;
			break;
		case TIMER4_32BIT:
			channelPtr = (volatile uint8*)GPT_32BIT_WIDE_TIMER4_BASE_ADDRESS;
			interruptId = TIMER_32_64_BIT_4A;
			break;
		case TIMER5_32BIT:
			channelPtr = (volatile uint8*)GPT_32BIT_WIDE_TIMER5_BASE_ADDRESS;
			interruptId = TIMER_32_64_BIT_5A;
			break;
		default:
			/* [TODO] Report an error, then return */
			return;
	}
	
	/* Enable Timeout interrupt */
	GPT_GPTMIMR(channelPtr).TATOIM = 1;
	
	/* Enable Interrupt for the dedicated channel from IntCtrl Module */
	IntCtrl_EnableInterrupt(interruptId, ConfigPtr->priority);
}


void Gpt_StartTimer(Gpt_ChannelType ChannelId, Gpt_ValueType Value)
{
	const Gpt_ChannelConfigType* ConfigPtr = &(Gpt_Config.channels[ChannelId]);
	
	volatile uint8* channelPtr = NULL_PTR;
	volatile uint8 timerWidth = 0;
	
	/* Pointing on the dedicated channel module's base address */
	switch (ConfigPtr->channelId)
	{
		case TIMER0_16BIT:
			channelPtr = (volatile uint8*)GPT_16BIT_TIMER0_BASE_ADDRESS;
			timerWidth = 32;
			break;
		case TIMER1_16BIT:
			channelPtr = (volatile uint8*)GPT_16BIT_TIMER1_BASE_ADDRESS;
			timerWidth = 32;
			break;
		case TIMER2_16BIT:
			channelPtr = (volatile uint8*)GPT_16BIT_TIMER2_BASE_ADDRESS;
			timerWidth = 32;
			break;
		case TIMER3_16BIT:
			channelPtr = (volatile uint8*)GPT_16BIT_TIMER3_BASE_ADDRESS;
			timerWidth = 32;
			break;
		case TIMER4_16BIT:
			channelPtr = (volatile uint8*)GPT_16BIT_TIMER4_BASE_ADDRESS;
			timerWidth = 32;
			break;
		case TIMER5_16BIT:
			channelPtr = (volatile uint8*)GPT_16BIT_TIMER5_BASE_ADDRESS;
			timerWidth = 32;
			break;
		case TIMER0_32BIT:
			channelPtr = (volatile uint8*)GPT_32BIT_WIDE_TIMER0_BASE_ADDRESS;
			timerWidth = 64;
			break;
		case TIMER1_32BIT:
			channelPtr = (volatile uint8*)GPT_32BIT_WIDE_TIMER1_BASE_ADDRESS;
			timerWidth = 64;
			break;
		case TIMER2_32BIT:
			channelPtr = (volatile uint8*)GPT_32BIT_WIDE_TIMER2_BASE_ADDRESS;
			timerWidth = 64;
			break;
		case TIMER3_32BIT:
			channelPtr = (volatile uint8*)GPT_32BIT_WIDE_TIMER3_BASE_ADDRESS;
			timerWidth = 64;
			break;
		case TIMER4_32BIT:
			channelPtr = (volatile uint8*)GPT_32BIT_WIDE_TIMER4_BASE_ADDRESS;
			timerWidth = 64;
			break;
		case TIMER5_32BIT:
			channelPtr = (volatile uint8*)GPT_32BIT_WIDE_TIMER5_BASE_ADDRESS;
			timerWidth = 64;
			break;
		default:
			/* [TODO] Report an error, then return */
			return;
	}
	
	Value = Value * F_CPU;		/* value = value x 16 */
	
	switch (timerWidth)
	{
		case 32:
			/* Set the starting count value */
			GPT_GPTMTAILR(channelPtr) = Value & (0x00000000FFFFFFFF);
			
			/* [TODO] Complete prescaler
			uint8 prescaler = 0;
			if (value > (256*256*256*256)-1)	// Overflow => 2^(32), then need prescaler
			{
				// GPT_GPTMTAPR(channelPtr) = prescaler & (0x0000FFFF);
			}
			*/
			break;
		case 64:
			
			/* Set the starting count value */
			GPT_GPTMTBILR(channelPtr) = ((Value) & (0xFFFFFFFF00000000))>>32;
			GPT_GPTMTAILR(channelPtr) = Value & (0x00000000FFFFFFFF);
			
			/* [TODO] Complete prescaler
			uint16 prescaler = 0;
			if (value > (65536*65536*65536*65536)-1)	// Overflow => 2^(64), then need prescaler
			{
				// GPT_GPTMTAPR(channelPtr) = prescaler & (0x0000FFFF);
			}
			*/
			break;
	}
	
	/* Starting the timer */
	GPT_GPTMCTL(channelPtr).TAEN = 1;
}


void Gpt_StopTimer(Gpt_ChannelType ChannelId)
{
	const Gpt_ChannelConfigType* ConfigPtr = &(Gpt_Config.channels[ChannelId]);
	
	volatile uint8* channelPtr = NULL_PTR;
	volatile uint8 timerWidth = 0;
	
	/* Pointing on the dedicated channel module's base address */
	switch (ConfigPtr->channelId)
	{
		case TIMER0_16BIT:
			channelPtr = (volatile uint8*)GPT_16BIT_TIMER0_BASE_ADDRESS;
			break;
		case TIMER1_16BIT:
			channelPtr = (volatile uint8*)GPT_16BIT_TIMER1_BASE_ADDRESS;
			break;
		case TIMER2_16BIT:
			channelPtr = (volatile uint8*)GPT_16BIT_TIMER2_BASE_ADDRESS;
			break;
		case TIMER3_16BIT:
			channelPtr = (volatile uint8*)GPT_16BIT_TIMER3_BASE_ADDRESS;
			break;
		case TIMER4_16BIT:
			channelPtr = (volatile uint8*)GPT_16BIT_TIMER4_BASE_ADDRESS;
			break;
		case TIMER5_16BIT:
			channelPtr = (volatile uint8*)GPT_16BIT_TIMER5_BASE_ADDRESS;
			break;
		case TIMER0_32BIT:
			channelPtr = (volatile uint8*)GPT_32BIT_WIDE_TIMER0_BASE_ADDRESS;
			break;
		case TIMER1_32BIT:
			channelPtr = (volatile uint8*)GPT_32BIT_WIDE_TIMER1_BASE_ADDRESS;
			break;
		case TIMER2_32BIT:
			channelPtr = (volatile uint8*)GPT_32BIT_WIDE_TIMER2_BASE_ADDRESS;
			break;
		case TIMER3_32BIT:
			channelPtr = (volatile uint8*)GPT_32BIT_WIDE_TIMER3_BASE_ADDRESS;
			break;
		case TIMER4_32BIT:
			channelPtr = (volatile uint8*)GPT_32BIT_WIDE_TIMER4_BASE_ADDRESS;
			break;
		case TIMER5_32BIT:
			channelPtr = (volatile uint8*)GPT_32BIT_WIDE_TIMER5_BASE_ADDRESS;
			break;
		default:
			/* [TODO] Report an error, then return */
			return;
	}
	
	/* Clear Timer enable bit in GPTM control register */
	GPT_GPTMCTL(channelPtr).TAEN = 0;
}


Gpt_ValueType Gpt_GetTimeElapsed(Gpt_ChannelType ChannelId)
{
	const Gpt_ChannelConfigType* ConfigPtr = &(Gpt_Config.channels[ChannelId]);
	
	volatile uint8* channelPtr = NULL_PTR;
	volatile uint8 timerWidth = 0;
	
	/* Pointing on the dedicated channel module's base address */
	switch (ConfigPtr->channelId)
	{
		case TIMER0_16BIT:
			channelPtr = (volatile uint8*)GPT_16BIT_TIMER0_BASE_ADDRESS;
			timerWidth = 32;
			break;
		case TIMER1_16BIT:
			channelPtr = (volatile uint8*)GPT_16BIT_TIMER1_BASE_ADDRESS;
			timerWidth = 32;
			break;
		case TIMER2_16BIT:
			channelPtr = (volatile uint8*)GPT_16BIT_TIMER2_BASE_ADDRESS;
			timerWidth = 32;
			break;
		case TIMER3_16BIT:
			channelPtr = (volatile uint8*)GPT_16BIT_TIMER3_BASE_ADDRESS;
			timerWidth = 32;
			break;
		case TIMER4_16BIT:
			channelPtr = (volatile uint8*)GPT_16BIT_TIMER4_BASE_ADDRESS;
			timerWidth = 32;
			break;
		case TIMER5_16BIT:
			channelPtr = (volatile uint8*)GPT_16BIT_TIMER5_BASE_ADDRESS;
			timerWidth = 32;
			break;
		case TIMER0_32BIT:
			channelPtr = (volatile uint8*)GPT_32BIT_WIDE_TIMER0_BASE_ADDRESS;
			timerWidth = 64;
			break;
		case TIMER1_32BIT:
			channelPtr = (volatile uint8*)GPT_32BIT_WIDE_TIMER1_BASE_ADDRESS;
			timerWidth = 64;
			break;
		case TIMER2_32BIT:
			channelPtr = (volatile uint8*)GPT_32BIT_WIDE_TIMER2_BASE_ADDRESS;
			timerWidth = 64;
			break;
		case TIMER3_32BIT:
			channelPtr = (volatile uint8*)GPT_32BIT_WIDE_TIMER3_BASE_ADDRESS;
			timerWidth = 64;
			break;
		case TIMER4_32BIT:
			channelPtr = (volatile uint8*)GPT_32BIT_WIDE_TIMER4_BASE_ADDRESS;
			timerWidth = 64;
			break;
		case TIMER5_32BIT:
			channelPtr = (volatile uint8*)GPT_32BIT_WIDE_TIMER5_BASE_ADDRESS;
			timerWidth = 64;
			break;
		default:
			/* [TODO] Report an error, then return */
			break;
	}
	
	if (timerWidth == 32)
	{
		uint32 elapsedTime = GPT_GPTMTAV(channelPtr);
		elapsedTime = elapsedTime / F_CPU;		/* elapsedTime = elapsedTime / 16 */
		
		return elapsedTime;
	}
	else if (timerWidth == 64)
	{
		uint64 elapsedTime = ((uint64)GPT_GPTMTBV(channelPtr) & (0x00000000FFFFFFFF))<<32;
		elapsedTime |= GPT_GPTMTAV(channelPtr) & (0x00000000FFFFFFFF);
		elapsedTime = elapsedTime / F_CPU;		/* elapsedTime = elapsedTime / 16 */
		
		return elapsedTime;
	}
	
	/* [TODO] Find another efficient way to indicate an error */
	return 0;
}


Gpt_ValueType Gpt_GetTimeRemaining(Gpt_ChannelType ChannelId)
{
	const Gpt_ChannelConfigType* ConfigPtr = &(Gpt_Config.channels[ChannelId]);
	
	volatile uint8* channelPtr = NULL_PTR;
	volatile uint8 timerWidth = 0;
	
	/* Pointing on the dedicated channel module's base address */
	switch (ConfigPtr->channelId)
	{
		case TIMER0_16BIT:
			channelPtr = (volatile uint8*)GPT_16BIT_TIMER0_BASE_ADDRESS;
			timerWidth = 32;
			break;
		case TIMER1_16BIT:
			channelPtr = (volatile uint8*)GPT_16BIT_TIMER1_BASE_ADDRESS;
			timerWidth = 32;
			break;
		case TIMER2_16BIT:
			channelPtr = (volatile uint8*)GPT_16BIT_TIMER2_BASE_ADDRESS;
			timerWidth = 32;
			break;
		case TIMER3_16BIT:
			channelPtr = (volatile uint8*)GPT_16BIT_TIMER3_BASE_ADDRESS;
			timerWidth = 32;
			break;
		case TIMER4_16BIT:
			channelPtr = (volatile uint8*)GPT_16BIT_TIMER4_BASE_ADDRESS;
			timerWidth = 32;
			break;
		case TIMER5_16BIT:
			channelPtr = (volatile uint8*)GPT_16BIT_TIMER5_BASE_ADDRESS;
			timerWidth = 32;
			break;
		case TIMER0_32BIT:
			channelPtr = (volatile uint8*)GPT_32BIT_WIDE_TIMER0_BASE_ADDRESS;
			timerWidth = 64;
			break;
		case TIMER1_32BIT:
			channelPtr = (volatile uint8*)GPT_32BIT_WIDE_TIMER1_BASE_ADDRESS;
			timerWidth = 64;
			break;
		case TIMER2_32BIT:
			channelPtr = (volatile uint8*)GPT_32BIT_WIDE_TIMER2_BASE_ADDRESS;
			timerWidth = 64;
			break;
		case TIMER3_32BIT:
			channelPtr = (volatile uint8*)GPT_32BIT_WIDE_TIMER3_BASE_ADDRESS;
			timerWidth = 64;
			break;
		case TIMER4_32BIT:
			channelPtr = (volatile uint8*)GPT_32BIT_WIDE_TIMER4_BASE_ADDRESS;
			timerWidth = 64;
			break;
		case TIMER5_32BIT:
			channelPtr = (volatile uint8*)GPT_32BIT_WIDE_TIMER5_BASE_ADDRESS;
			timerWidth = 64;
			break;
		default:
			/* [TODO] Report an error, then return */
			break;
	}
	
	if (timerWidth == 32)
	{
		uint32 elapsedTime = GPT_GPTMTAV(channelPtr);
		elapsedTime = elapsedTime / F_CPU;		/* elapsedTime = elapsedTime / 16 */
		
		uint32 targetingTime = GPT_GPTMTAILR(channelPtr);
		
		uint32 remainingTime = targetingTime - elapsedTime;
		
		return remainingTime;
	}
	else if (timerWidth == 64)
	{
		uint64 elapsedTime = ((uint64)GPT_GPTMTBV(channelPtr) & (0x00000000FFFFFFFF))<<32;
		elapsedTime |= GPT_GPTMTAV(channelPtr) & (0x00000000FFFFFFFF);
		elapsedTime = elapsedTime / F_CPU;		/* elapsedTime = elapsedTime / 16 */
		
		uint64 targetingTime = ((uint64)GPT_GPTMTBILR(channelPtr) & (0x00000000FFFFFFFF))<<32;
		targetingTime |= GPT_GPTMTAILR(channelPtr) & (0x00000000FFFFFFFF);
		
		uint64 remainingTime = targetingTime - elapsedTime;
		
		return remainingTime;
	}
	
	/* [TODO] Find another efficient way to indicate an error */
	return 0;
}


Std_ReturnType Gpt_GetPredefTimerValue(Gpt_PredefTimerType PredefTimer, uint32* TimeValuePtr)
{
	return 0;
}
