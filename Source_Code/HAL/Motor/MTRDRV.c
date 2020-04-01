#include "MTRDRV.h"
#include "Pwm.h"

void MTRDRV_Init(void)
{
	unsigned char i;
	for(i = 0 ; i < MTR_NUM_OF_MOTORS ; i++)
	{
		MTRDRV_Stop(i);
	}
	
}
void MTRDRV_SetDirection(unsigned char Motor_Index, MotorDirectionType Direction)
{
	switch(Direction)
	{
		case DIR_FWD:
				DIO_Write(BUT_ConfigParam[Motor_Index].DioGroupId_IN1, HIGH);
				DIO_Write(BUT_ConfigParam[Motor_Index].DioGroupId_IN2, LOW);
				break;
		case DIR_REV:
				DIO_Write(BUT_ConfigParam[Motor_Index].DioGroupId_IN1, LOW);
				DIO_Write(BUT_ConfigParam[Motor_Index].DioGroupId_IN2, HIGH);
				break;
	}
	
	
}
void MTRDRV_SetSpeed(unsigned char Motor_Index, unsigned long int RotPerMin)
{
	PWM_SetDutyCycle(BUT_ConfigParam[Motor_Index].ChannelId_EN, GET_DUTY_CYCLE_FROM_RPM(RotPerMin));
}
void MTRDRV_Stop(unsigned char Motor_Index);
{
	DIO_Write(BUT_ConfigParam[Motor_Index].DioGroupId_IN1, LOW);
	DIO_Write(BUT_ConfigParam[Motor_Index].DioGroupId_IN2, LOW);
	PWM_SetDutyCycle(BUT_ConfigParam[Motor_Index].ChannelId_EN, LOW);
}

