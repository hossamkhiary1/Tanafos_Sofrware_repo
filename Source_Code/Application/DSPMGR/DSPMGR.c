
#include "DSPMGR.h"
#include "DSPMGR_Cfg.h"
#include "lcd_4bit.h"
static unsigned char ItemsLastData[DSPMGR_NUM_OF_ITEMS][DSPMGR_MAX_ITEM_SIZE];
static unsigned char CurrentScreen;
static unsigned char lastScreen;
void DSPMGR_Init(void)
{
	unsigned char loop1, loop2;
	for(loop1 = 0; loop1 < DSPMGR_NUM_OF_ITEMS; loop1 ++)
	{
		for(loop2 = 0; loop2 < DSPMGR_MAX_ITEM_SIZE; loop2 ++)
		{
			ItemsLastData[loop1][loop2] = '\0';
		}
	}
	CurrentScreen = 0;
	lastScreen = 0xff;
}
void DSPMGR_ReqDispItem(unsigned char ItemId,unsigned char* ItemDataPtr)
{
	unsigned char loop = 0;
	unsigned char maxAllowedLength = DSPMGR_MAX_ROW_WIDTH - DSPMGR_ItemConfig[ItemId].ItemCol;
	while((*(ItemDataPtr + loop) != '\0') && (loop < maxAllowedLength) && (loop < DSPMGR_ItemConfig[ItemId].ItemNumOfCharecters))
	{
		ItemsLastData[ItemId][loop] = *(ItemDataPtr + loop);
		loop ++;
	}
	while(loop < DSPMGR_MAX_ITEM_SIZE)
	{
		ItemsLastData[ItemId][loop] = '\0';
		loop ++;
	}
}
void DSPMGR_ReqScreen(unsigned char ScreenId)
{
	CurrentScreen = ScreenId;
}
void DSPMGR_Manager(void)
{
	unsigned char loop;
	unsigned char itemindex;
	if(lastScreen != CurrentScreen)
	{
		lastScreen = CurrentScreen;
		lcd_clrScreen();
		for(loop = 0; loop < DSPMGR_ScreenConfig[CurrentScreen].NumOfItems; loop++)
		{
			itemindex = loop + DSPMGR_ScreenConfig[CurrentScreen].ItemConfigIndex;
			lcd_gotoxy(DSPMGR_ItemConfig[itemindex].ItemRow,DSPMGR_ItemConfig[itemindex].ItemCol);
			lcd_dispString(ItemsLastData[itemindex]);
		}
	}
}
