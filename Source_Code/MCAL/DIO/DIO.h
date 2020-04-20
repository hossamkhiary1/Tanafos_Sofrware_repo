#ifndef DIO_H
#define DIO_H
#include <stdint.h>
#include "DIO_Cfg.h"
typedef void(*DIO_FnPtrType)(void);
typedef struct
{
uint8_t PortId;
uint8_t PortMask;
/*Mode Control*/
uint8_t UseAlterFun;
uint8_t UseDMATrig;
uint8_t UseACDTrig;
/*Data Control*/
/*input -> 0
 *Output-> 1
 */
uint8_t PortDirection;
/*Pad Control*/
/*Internal Resistor*/
uint8_t UsePullUp;
uint8_t UsePullDown;
uint8_t UseOpenDrain;
/*Output current*/
uint8_t Use2mACrt;
uint8_t Use4mACrt;
uint8_t Use8mACrt;
/*Pin Type*/
/*analog -> 0
 *Digital-> 1
 */
uint8_t SetPinType;
/*interrupt call back pointer*/
DIO_FnPtrType CbkFnPtr;
}DIO_CfgType;
typedef enum {DIO_OK =0, DIO_NOK} DIO_CheckType;
typedef enum {EVENT_FALL_EDGE = 0, EVENT_RISE_EDGE = 0x01, EVENT_BOTH_EDGE = 0x04,
	          EVENT_LOW = 0x02, EVENT_HIGH = 0x03} DIO_IntEventType;
typedef enum {MASK_ENABLED = 0xff,MASK_DISABLED = 0x00} DIO_IntMaskStatus;
typedef enum {INT_PENDING = 0xff,INT_INACTIVE = 0x00}DIO_IntStatus;
extern const DIO_CfgType DIO_ConfigParam [DIO_GROUPS_NUMBER];

/*A function to initialize all the GPIO Groups in the configurations*/
DIO_CheckType DIO_Init(void);
/*A function to Digital Write data to a specific group*/
DIO_CheckType DIO_Write(uint8_t GroupId,uint8_t GroupData);
/*A function to Digital read data from a specific group*/
DIO_CheckType DIO_Read(uint8_t GroupId,uint8_t* GroupDataPtr);
/*A function to select which peripheral will be connected to a GPIO pin*/
DIO_CheckType DIO_SetAlternFuntion(uint8_t GroupId,uint8_t AlternFuncId);
/*A function to Select the interrupt event for a specific GPIO Group*/
DIO_CheckType DIO_SetInterruptEvent(uint8_t GroupId,DIO_IntEventType IntEvent,DIO_IntMaskStatus IntMaskStatus);
/*A function to clear a specific pin interrupt flag*/
DIO_CheckType DIO_ClrInterruptFlag(uint8_t GroupId);
/*A function to Get a specific pin interrupt status*/
DIO_CheckType DIO_GetInterruptStatus(uint8_t GroupId,DIO_IntStatus *IntStatusPtr);
#endif
