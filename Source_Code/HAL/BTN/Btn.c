#include "Btn.h"
#include "Dio.h"
static BtnStateType Array_state[BTN_NUM_OF_BUTTONS];
void BTN_Init(void)
{
	/***Initializing first state for all buttons****/
	unsigned char i=0;
	for(i=0;i<BTN_NUM_OF_BUTTONS ;i++)
	{
			 	 Array_state[i] = BUT_OFF;
			
	}
}
void BTN_GetState(BtnStateType *BtnStatePtr, unsigned char BtnId)
{	
	*BtnStatePtr = Array_state[BtnId];
	
}
void BTN_Manager(void)
{
	unsigned char i=0;
	BtnStateType state;
	unsigned char *DataPtr;
	for(i=0;i<BTN_NUM_OF_BUTTONS ;i++) 					//for all buttons
	{	
		state = Array_state[i]; 						//put previous state in state
		DIO_Read(BUT_ConfigParam[i].DioGroupId , &DataPtr);
		switch(BUT_ConfigParam[i].BtnActiveState)		//switching on Btn active state is it active low or active high
			{
			case ActiveLow:
				switch(state)
				{
					case BUT_OFF:
						if((*DataPtr) == HIGH) 				//button is not pressed
							state = BUT_OFF;
						if((*DataPtr) == LOW) 				//button is pressed
							state = BUT_PRSSED;
						break;
					case BUT_PRSSED:
						if((*DataPtr) == HIGH)				//button is not pressed
							state = BUT_OFF;
						if((*DataPtr) == LOW) 				//button is pressed
							state = BUT_ON;
						break;
					case BUT_ON:
						if((*DataPtr) == HIGH) 				//button is not pressed
							state = BUT_RELEASED;
						if((*DataPtr) == LOW)  				//button is pressed
							state = BUT_ON;
						break;
					case BUT_RELEASED:
						if((*DataPtr) == HIGH)				//button is not pressed
							state = BUT_OFF;
						if(((*DataPtr) == LOW)  				//button is pressed
							state = BUT_ON;
						break;	
				}

			break;
			case ActiveHigh:
				switch(state)
				{
					case BUT_OFF:
						if((*DataPtr) == LOW)  				//button is not pressed
							state = BUT_OFF;
						if((*DataPtr) == HIGH) 				//button is pressed
							state = BUT_PRSSED;
						break;
					case BUT_PRSSED:
						if((*DataPtr) == LOW)  				//button is not pressed
							state = BUT_OFF;
						if((*DataPtr) == HIGH)				//button is pressed
							state = BUT_ON;
						break;
					case BUT_ON:
						if((*DataPtr) == LOW) 				//button is not pressed
							state = BUT_RELEASED;
						if((*DataPtr) == HIGH)				//button is pressed
							state = BUT_ON;
						break;
					case BUT_RELEASED:
						if((*DataPtr) == LOW)  				//button is not pressed
							state = BUT_OFF;
						if((*DataPtr) == HIGH)				//button is pressed
							state = BUT_ON;
						break;	
				}

			break;
			}
		Array_state[i] = state;	
	}	
}
