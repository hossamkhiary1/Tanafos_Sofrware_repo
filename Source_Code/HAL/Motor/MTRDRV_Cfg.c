#include "MTRDRV.h"
#include "MTRDRV_Cfg.h"
#include "PWM.h"

const MTRConfigType MOTOR_ConfigParam[MTR_NUM_OF_MOTORS] = 
{
	{
		0x00,
		0x00,
		Freq_488Hz
	}
};
