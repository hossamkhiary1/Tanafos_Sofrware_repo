#ifndef DSPMGR_H
#define DSPMGR_H
typedef struct
{
	unsigned char ItemRow;
	unsigned char ItemCol;
	unsigned char ItemNumOfCharecters;
}ItemConfigType;

typedef struct 
{
	unsigned char NumOfItems;
	unsigned char ItemConfigIndex; 
}ScreenConfigType;
void DSPMGR_Init(void);
void DSPMGR_ReqDispItem(unsigned char ItemId,unsigned char* ItemDataPtr);
void DSPMGR_ReqScreen(unsigned char ScreenId);
void DSPMGR_Manager(void); 


#endif