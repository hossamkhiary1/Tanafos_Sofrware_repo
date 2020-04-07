#ifndef MTRDRV_H
#define MTRDRV_H
typedef enum {DIR_FWD, DIR_REV} MotorDirectionType;
typedef enum {LOW, HIGH} Level;
typedef struct 
{
	unsigned char DioGroupId_DIR;
	unsigned char ChannelId_PWM;
	unsigned long int Motor_Frequency;
}MTRConfigType;
void MTRDRV_Init(void);
void MTRDRV_SetDirection(unsigned char Motor_Index, MotorDirectionType Direction);
void MTRDRV_SetSpeed(unsigned char Motor_Index, unsigned long int RotPerMin);
void MTRDRV_Stop(unsigned char Motor_Index);

#endif
