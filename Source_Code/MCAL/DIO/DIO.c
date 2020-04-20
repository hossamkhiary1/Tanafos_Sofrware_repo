#include "DIO.h"
#include "DIO_Cfg.h"
#include "M4MemMap.h"
#include <stdint.h>
typedef volatile uint32_t *const DIO_RegAddType;
#define PORTS_NUMBER 6u
/*Register memory map*/
#define PORTA_BASE_ADDRESS 0x40004000
#define PORTB_BASE_ADDRESS 0x40005000
#define PORTC_BASE_ADDRESS 0x40006000
#define PORTD_BASE_ADDRESS 0x40007000
#define PORTE_BASE_ADDRESS 0x40024000
#define PORTF_BASE_ADDRESS 0x40025000
static const uint32_t PortsBaseAddressLut[PORTS_NUMBER] = { PORTA_BASE_ADDRESS,
PORTB_BASE_ADDRESS,
                                                            PORTC_BASE_ADDRESS,
                                                            PORTD_BASE_ADDRESS,
                                                            PORTE_BASE_ADDRESS,
                                                            PORTF_BASE_ADDRESS };
#define DIO_REG_ADDRESS(CHANNEL_ID,REG_OFFSET)\
(PortsBaseAddressLut[CHANNEL_ID] + REG_OFFSET)

/*Port Control*/
#define GPIODATA_WRITE(DATA,MASK,PORT_ID)  *((DIO_RegAddType)(DIO_REG_ADDRESS(PORT_ID,0x000) + (MASK << 2))) = DATA
#define GPIODATA_READ(MASK,PORT_ID)        *((DIO_RegAddType)(DIO_REG_ADDRESS(PORT_ID,0x000) + (MASK << 2)))
#define GPIODIR_REG(PORT_ID)               *((DIO_RegAddType)DIO_REG_ADDRESS(PORT_ID,0x400))

/*Interrupt Control*/
#define GPIOIS_REG(PORT_ID)               *((DIO_RegAddType)DIO_REG_ADDRESS(PORT_ID,0x404))
#define GPIOIBE_REG(PORT_ID)              *((DIO_RegAddType)DIO_REG_ADDRESS(PORT_ID,0x408))
#define GPIOIEV_REG(PORT_ID)              *((DIO_RegAddType)DIO_REG_ADDRESS(PORT_ID,0x40C))
#define GPIOIM_REG(PORT_ID)               *((DIO_RegAddType)DIO_REG_ADDRESS(PORT_ID,0x410))
#define GPIORIS_REG(PORT_ID)              *((DIO_RegAddType)DIO_REG_ADDRESS(PORT_ID,0x414))
#define GPIOMIS_REG(PORT_ID)              *((DIO_RegAddType)DIO_REG_ADDRESS(PORT_ID,0x418))
#define GPIOICR_REG(PORT_ID)              *((DIO_RegAddType)DIO_REG_ADDRESS(PORT_ID,0x41C))

/*Mode Control*/
#define GPIOAFSEL_REG(PORT_ID)            *((DIO_RegAddType)DIO_REG_ADDRESS(PORT_ID,0x420))
#define GPIOPCTL_REG(PORT_ID)             *((DIO_RegAddType)DIO_REG_ADDRESS(PORT_ID,0x52C))
#define GPIOADCCTL_REG(PORT_ID)           *((DIO_RegAddType)DIO_REG_ADDRESS(PORT_ID,0x530))
#define GPIODMACTL_REG(PORT_ID)           *((DIO_RegAddType)DIO_REG_ADDRESS(PORT_ID,0x534))

/*Pad control*/
#define GPIODR2R_REG(PORT_ID)           *((DIO_RegAddType)DIO_REG_ADDRESS(PORT_ID,0x500))
#define GPIODR4R_REG(PORT_ID)           *((DIO_RegAddType)DIO_REG_ADDRESS(PORT_ID,0x504))
#define GPIODR8R_REG(PORT_ID)           *((DIO_RegAddType)DIO_REG_ADDRESS(PORT_ID,0x508))
#define GPIOODR_REG(PORT_ID)            *((DIO_RegAddType)DIO_REG_ADDRESS(PORT_ID,0x50C))
#define GPIOPUR_REG(PORT_ID)            *((DIO_RegAddType)DIO_REG_ADDRESS(PORT_ID,0x510))
#define GPIOPDR_REG(PORT_ID)            *((DIO_RegAddType)DIO_REG_ADDRESS(PORT_ID,0x514))
#define GPIOSLR_REG(PORT_ID)            *((DIO_RegAddType)DIO_REG_ADDRESS(PORT_ID,0x518))
#define GPIODEN_REG(PORT_ID)            *((DIO_RegAddType)DIO_REG_ADDRESS(PORT_ID,0x51C))
#define GPIOAMSEL_REG(PORT_ID)          *((DIO_RegAddType)DIO_REG_ADDRESS(PORT_ID,0x528))

/*Commit control*/
#define GPIOLOCK_REG(PORT_ID)          *((DIO_RegAddType)DIO_REG_ADDRESS(PORT_ID,0x520))
#define GPIOCR_REG(PORT_ID)            *((DIO_RegAddType)DIO_REG_ADDRESS(PORT_ID,0x524))

/*Internal symbols*/
#define DIO_PORT_UNLOCK_VALUE 0x4C4F434B
#define DIO_INT_SENCE_BIT_NUM 1
#define DIO_INT_SENCE_MASK (1 << DIO_INT_EVENT_BIT_NUM)
#define DIO_INT_EVENT_BIT_NUM 0
#define DIO_INT_EVENT_MASK (1 << DIO_INT_EVENT_BIT_NUM)
#define DIO_INT_BE_BIT_NUM 2
#define DIO_INT_BR_MASK (1 << DIO_INT_BE_BIT_NUM)

static uint8_t DIO_GroupState[DIO_GROUPS_NUMBER] = { 0 };

/*A function to initialize all the GPIO Groups in the configurations*/
DIO_CheckType DIO_Init(void)
{
    uint8_t LoopIndex;
    uint8_t ErrorFlag = 0;
    DIO_CheckType RetVar;
    const DIO_CfgType *CfgPtr;

    for (LoopIndex = 0; (LoopIndex < DIO_GROUPS_NUMBER) && (ErrorFlag == 0);
            LoopIndex++)
    {
        if (DIO_ConfigParam[LoopIndex].PortId < PORTS_NUMBER)
        {

            /*Enable port clock gate*/
            CfgPtr = &DIO_ConfigParam[LoopIndex];
            RCGCGPIO_REG |= 1 << CfgPtr->PortId;
            /*Unlock the group*/
            GPIOLOCK_REG(CfgPtr->PortId) = DIO_PORT_UNLOCK_VALUE;
            GPIOCR_REG(CfgPtr->PortId) |= (CfgPtr->PortMask);
            /*Data Control*/
            GPIODIR_REG(CfgPtr->PortId) |= (CfgPtr->PortMask
                    & CfgPtr->PortDirection);
            /*Pad Control*/
            GPIODR2R_REG(CfgPtr->PortId) |= (CfgPtr->PortMask
                    & CfgPtr->Use2mACrt);
            GPIODR4R_REG(CfgPtr->PortId) |= (CfgPtr->PortMask
                    & CfgPtr->Use4mACrt);
            GPIODR8R_REG(CfgPtr->PortId) |= (CfgPtr->PortMask
                    & CfgPtr->Use8mACrt);

            GPIOPDR_REG(CfgPtr->PortId) |= (CfgPtr->PortMask
                    & CfgPtr->UsePullDown);
            GPIOPUR_REG(CfgPtr->PortId) |=
                    (CfgPtr->PortMask & CfgPtr->UsePullUp);
            GPIOODR_REG(CfgPtr->PortId) |= (CfgPtr->PortMask
                    & CfgPtr->UseOpenDrain);

            GPIODEN_REG(CfgPtr->PortId) |= (CfgPtr->PortMask
                    & CfgPtr->SetPinType);
            GPIOAMSEL_REG(CfgPtr->PortId) |= (CfgPtr->PortMask
                    & ~CfgPtr->SetPinType);

            /*Mode control*/
            GPIOAFSEL_REG(CfgPtr->PortId) |= (CfgPtr->PortMask
                    & CfgPtr->UseAlterFun);
            GPIOADCCTL_REG(CfgPtr->PortId) |= (CfgPtr->PortMask
                    & CfgPtr->UseACDTrig);
            GPIODMACTL_REG(CfgPtr->PortId) |= (CfgPtr->PortMask
                    & CfgPtr->UseDMATrig);
            DIO_GroupState[LoopIndex] = 1;
            RetVar = DIO_OK;
        }
        else
        {
            /*Invalid GroupId*/
            RetVar = DIO_NOK;
            ErrorFlag = 1;
        }

    }
    return RetVar;
}

/*A function to Digital Write data to a specific group*/
DIO_CheckType DIO_Write(uint8_t GroupId, uint8_t GroupData)
{
    const DIO_CfgType *CfgWrhit;
    DIO_CheckType RetVar;

    if ((GroupId < DIO_GROUPS_NUMBER))
    {

        CfgWrhit = &DIO_ConfigParam[GroupId];

        if ((CfgWrhit->PortDirection != 0x00) && (CfgWrhit->SetPinType != 0x00)
                && (CfgWrhit->UseAlterFun == 0x00)
                && (DIO_GroupState[GroupId] == 1))
        {

            GPIODATA_WRITE(GroupData, CfgWrhit->PortMask, CfgWrhit->PortId);
            RetVar = DIO_OK;

        }
        else
        {
            RetVar = DIO_NOK;
        }

    }
    else
    {
        RetVar = DIO_NOK;
    }

    return RetVar;
}

/*A function to Digital read data from a specific group*/
DIO_CheckType DIO_Read(uint8_t GroupId, uint8_t *GroupDataPtr)
{
    const DIO_CfgType *CfgWrhit;
    DIO_CheckType RetVar;

    if ((GroupId < DIO_GROUPS_NUMBER))
    {

        CfgWrhit = &DIO_ConfigParam[GroupId];

        if ((CfgWrhit->PortDirection == 0x00) && (CfgWrhit->SetPinType != 0x00)
                && (CfgWrhit->UseAlterFun == 0x00)
                && (DIO_GroupState[GroupId] == 1))
        {

            *GroupDataPtr = GPIODATA_READ(CfgWrhit->PortMask, CfgWrhit->PortId);
            RetVar = DIO_OK;

        }
        else
        {
            RetVar = DIO_NOK;
        }

    }
    else
    {
        RetVar = DIO_NOK;
    }

    return RetVar;
}

/*A function to select which peripheral will be connected to a GPIO pin*/
DIO_CheckType DIO_SetAlternFuntion(uint8_t GroupId, uint8_t AlternFuncId)
{

}
/*A function to Select the interrupt event for a specific GPIO Group*/
DIO_CheckType DIO_SetInterruptEvent(uint8_t GroupId, DIO_IntEventType IntEvent,
                                    DIO_IntMaskStatus IntMaskStatus)
{

}
/*A function to clear a specific pin interrupt flag*/
DIO_CheckType DIO_ClrInterruptFlag(uint8_t GroupId)
{

}
/*A function to Get a specific pin interrupt status*/
DIO_CheckType DIO_GetInterruptStatus(uint8_t GroupId,
                                     DIO_IntStatus *IntStatusPtr)
{

}

static uint8_t GetPinNumber(uint8_t PinMask)
{

}
