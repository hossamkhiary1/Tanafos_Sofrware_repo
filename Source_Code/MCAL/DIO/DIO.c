#include "DIO.h"
#include "DIO_Cfg.h"
#define PIN_REG_OFFSET  0x00
#define DDR_REG_OFFSET  0x01
#define PORT_REG_OFFSET 0x02
#define PORT_SUBSYSTEM_BASE_ADDRESS 0x20

#define PIN_REG(PORT_ID) *((volatile unsigned char*)(PORT_SUBSYSTEM_BASE_ADDRESS + (PORT_ID * 3) + PIN_REG_OFFSET))
#define DDR_REG(PORT_ID) *((volatile unsigned char*)(PORT_SUBSYSTEM_BASE_ADDRESS + (PORT_ID * 3) + DDR_REG_OFFSET))  
#define PORT_REG(PORT_ID) *((volatile unsigned char*)(PORT_SUBSYSTEM_BASE_ADDRESS + (PORT_ID * 3) + PORT_REG_OFFSET))

void DIO_Init(void)
{
	unsigned char loop;
	for(loop = 0; loop < DIO_NUM_OF_GROUPS; loop++)
	{
		DDR_REG(DIO_ConfigParam[loop].Port) &= ~(DIO_ConfigParam[loop].Mask);
		DDR_REG(DIO_ConfigParam[loop].Port) |= (DIO_ConfigParam[loop].Mask & DIO_ConfigParam[loop].Direction);
		PORT_REG(DIO_ConfigParam[loop].Port) &= ~(DIO_ConfigParam[loop].Mask);
		PORT_REG(DIO_ConfigParam[loop].Port) |= (DIO_ConfigParam[loop].Mask & DIO_ConfigParam[loop].UsePullUp);
	}
}
void DIO_Write(unsigned char GroupId, unsigned char Data)
{
	unsigned char TempData;
	TempData = PORT_REG(DIO_ConfigParam[GroupId].Port);
	TempData &= ~(DIO_ConfigParam[GroupId].Mask);
	TempData |= (DIO_ConfigParam[GroupId].Mask & Data);
	PORT_REG(DIO_ConfigParam[GroupId].Port) = TempData;
}
void DIO_Read(unsigned char GroupId, unsigned char * DataPtr)
{
	*DataPtr = PIN_REG(DIO_ConfigParam[GroupId].Port) & DIO_ConfigParam[GroupId].Mask;
}