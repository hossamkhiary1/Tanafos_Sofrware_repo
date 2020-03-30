#ifndef PWM_H
#define PWM_H
typedef struct
{
	unsigned char TimerId;
	unsigned char TimerFrequence;
}TimerConfigType;

void PWM_Init(void);
void PWM_SetFrequence(unsigned char ChannelId,unsigned long int Freequency);
void PWM_SetDutyCycle(unsigned char ChannelId,unsigned char DutyCycle);
#endif