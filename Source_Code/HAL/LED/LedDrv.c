
#include "Dio.h"
#include "LedDriv.h"
#include "LED_Cfg.h"

#define LED_STATE_OFF 0x00
#define LED_STATE_ON  0x01



static unsigned char LedsState[LED_NUM_OF_LEDS];
static unsigned int LedsBliningPeriod[LED_NUM_OF_LEDS];
static unsigned int LedsTimeOut[LED_NUM_OF_LEDS];
void LED_Init(void)
{
	unsigned char Loop;
	for(Loop = 0; Loop < LED_NUM_OF_LEDS; Loop++)
	{
		LedsTimeOut[Loop] = 0;
		LedsBliningPeriod[Loop] = 0;
		LedsState[Loop] = LED_STATE_OFF;
		DIO_Write(LED_ConfigParam[Loop].DioGroupId, ~LED_ConfigParam[Loop].LedActiveState);
	}
}
void LED_TurnOn(unsigned char LedId)
{
	LedsState[LedId] = LED_STATE_ON;
	LedsTimeOut[LedId] = 0;
	DIO_Write(LED_ConfigParam[LedId].DioGroupId, LED_ConfigParam[LedId].LedActiveState);
	LedsBliningPeriod[LedId] = 0;
}
void LED_TurnOff(unsigned char LedId)
{
	LedsState[LedId] = LED_STATE_OFF;
	LedsTimeOut[LedId] = 0;
	DIO_Write(LED_ConfigParam[LedId].DioGroupId, ~LED_ConfigParam[LedId].LedActiveState);
	LedsBliningPeriod[LedId] = 0;
}
void LED_Blink(unsigned char LedId, unsigned int BlinkPeriod)
{
	LedsBliningPeriod[LedId] = BlinkPeriod;
}
void LED_Main(void)
{
	unsigned char loop;

	for(loop = 0; loop < LED_NUM_OF_LEDS; loop++)
	{
		if(LedsBliningPeriod[loop] > 0)
		{
			LedsTimeOut[loop] += LED_PERIODIC_TIME;
			switch(LedsState[loop])
			{
				case LED_STATE_OFF:
				{
					if(LedsTimeOut[loop] >= LedsBliningPeriod[loop])
					{
						LedsState[loop] = LED_STATE_ON;
						LedsTimeOut[loop] = 0;
						DIO_Write(LED_ConfigParam[loop].DioGroupId, LED_ConfigParam[loop].LedActiveState);
					}
				}
				break;
				case LED_STATE_ON:
				{
					if(LedsTimeOut[loop] >= LedsBliningPeriod[loop])
					{
						LedsState[loop] = LED_STATE_OFF;
						LedsTimeOut[loop] = 0;
						DIO_Write(LED_ConfigParam[loop].DioGroupId, ~LED_ConfigParam[loop].LedActiveState);
					}
				}
				break;
			}
		}
		else
		{
			LED_TurnOff(loop);
		}
	}
}