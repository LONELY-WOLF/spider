/* Define to prevent recursive  ----------------------------------------------*/
#ifndef __USBH_HID_GAMEPAD_H
#define __USBH_HID_GAMEPAD_H

/* Includes ------------------------------------------------------------------*/
#include "usbh_hid_core.h"

typedef struct _HID_GAMEPAD_Data
{
  uint8_t data[9];
}
HID_GAMEPAD_Data_TypeDef;

extern HID_cb_TypeDef HID_GAMEPAD_cb;
extern HID_GAMEPAD_Data_TypeDef	 HID_GAMEPAD_Data;

void  USR_GAMEPAD_Init (void);
void  USR_GAMEPAD_ProcessData (HID_GAMEPAD_Data_TypeDef *data);

#endif /* __USBH_HID_GAMEPAD_H */
