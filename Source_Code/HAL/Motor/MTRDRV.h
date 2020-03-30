#ifndef MTRDRV_H
#define MTRDRV_H
typedef enum {DIR_FWD, DIR_REV} MotorDirectionType;
void MTRDRV_Init(void);
void MTRDRV_SetDirection(MotorDirectionType Direction);
void MTRDRV_SetSpeed(unsigned long int RotPerMin);
void MTRDRV_Stop(void);

#endif