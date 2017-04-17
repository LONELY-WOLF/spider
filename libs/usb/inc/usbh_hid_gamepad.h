/* Define to prevent recursive  ----------------------------------------------*/
#ifndef __USBH_HID_GAMEPAD_H
#define __USBH_HID_GAMEPAD_H

/* Includes ------------------------------------------------------------------*/
#include "usbh_hid_core.h"

enum HatSwitchPos
{
	Up = 0, UpRight, Right, DownRight, Down, DownLeft, Left, UpLeft, None = 0x0F
};

typedef struct _HID_GAMEPAD_Data
{
	uint8_t Axis[8];
	enum HatSwitchPos HatSwitch;
	uint8_t Button[32];
} HID_GAMEPAD_Data_TypeDef;

typedef struct _HID_GAMEPAD_DataDesc
{
	int AxisPtr;
	int AxisCnt;
	int ButtonPtr;
	int ButtonCnt;
	int HatPtr;
	int HatCnt;
} HID_GAMEPAD_DataDesc_TypeDef;

extern HID_cb_TypeDef HID_GAMEPAD_cb;
extern HID_GAMEPAD_Data_TypeDef HID_GAMEPAD_Data;
extern HID_GAMEPAD_DataDesc_TypeDef HID_GAMEPAD_DataDesc;

void USR_GAMEPAD_Init(void);
void USR_GAMEPAD_ProcessData(HID_GAMEPAD_Data_TypeDef *data);

#endif /* __USBH_HID_GAMEPAD_H */
