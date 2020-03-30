#ifndef MTRDRV_Cfg_H
#define MTRDRV_Cfg_H

#define DUTY_CYCLE_PER_1_RPM  5
#define GET_DUTY_CYCLE_FROM_RPM(RPM) (DUTY_CYCLE_PER_1_RPM * RPM) % 100

#endif