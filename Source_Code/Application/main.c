/*
* GccApplication1.c
*
* Created: 04/04/2020 14:28:11
* Author : sony
*/

#include "DIO.h"
#include "FreeRTOS.h"
#include "task.h"
#include "LedDriv.h"
#include "Btn.h"
#include "lcd_4bit.h"
#include "DSPMGR.h"
void TestTask(void* pv)
{
	portTickType xLastWakeTime;
	const portTickType xPeriod = 10;
	BtnStateType BtnState;
	int BlinkingTime = 0;
	static int LedData = 0x00;
	static int ScreenIdx = 1;
	xLastWakeTime = xTaskGetTickCount();
	while(1)
	{
		vTaskDelayUntil( &xLastWakeTime, xPeriod );
		BTN_Manager();
		BTN_GetState(&BtnState,0);
		if(BtnState == BUT_PRSSED)
		{
			BlinkingTime += 100;
			if(BlinkingTime > 1000)
			{
			BlinkingTime = 0;
			}
			LED_Blink(0,BlinkingTime);
			DSPMGR_ReqScreen(ScreenIdx);
			ScreenIdx = !ScreenIdx;
		
		}
		LED_Main();
		DSPMGR_Manager();
	}
}
int main(void)
{

	DIO_Init();
	LED_Init();
	BTN_Init();
	lcd_init();
	DSPMGR_Init();
	DSPMGR_ReqDispItem(0,"Hi");
	DSPMGR_ReqDispItem(1,"Hossam");
	DSPMGR_ReqDispItem(2,"Hello");
	DSPMGR_ReqDispItem(3,"Sayof");
	
	

	/* Replace with your application code */
	xTaskCreate( TestTask,NULL, configMINIMAL_STACK_SIZE, NULL, 1, NULL );

	
	//Start FreeRTOS
	vTaskStartScheduler();
	while (1)
	{
		
	}
}

