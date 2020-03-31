#ifndef MTRDRV_Cfg_H
#define MTRDRV_Cfg_H
#define DUTY_CYCLE_PER_1_RPM  5
#define GET_DUTY_CYCLE_FROM_RPM(RPM) (DUTY_CYCLE_PER_1_RPM * RPM) % 100
#define MTR_NUM_OF_MOTORS 1
extern const MTRConfigType BUT_ConfigParam[MTR_NUM_OF_MOTORS];
#endif





