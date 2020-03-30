#ifndef LED_H
#define LED_H
typedef struct
{
	unsigned char DioGroupId;
	unsigned char LedActiveState;
}LED_ConfigParam;
void LED_Init(void);
void LED_TurnOn(unsigned char LedId);
void LED_TurnOff(unsigned char LedId);
void LED_Blink(unsigned char LedId);


#endif