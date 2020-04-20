#include "DIO.h"
#include "DIO_Cfg.h"
const DIO_CfgType DIO_ConfigParam [DIO_GROUPS_NUMBER] =
		{
				{
						0x05,1<<1,
						0,0,0,
						0xff,
						0x00,0xff,0x00,
						0xff,0x00,0x00,
						0xff,
						0


				},
				      {

					0x05,1<<0,
					0,0,0,
					0x00,
					0xff,0x00,0x00,
					0x00,0x00,0x00,
					0xff,
					0


			         },

		           	{
								0x05,1<<4,
								0,0,0,
								0x00,
								0xff,0x00,0x00,
								0x00,0x00,0x00,
								0xff,
								0
				    }
				
		};
