/**
  ******************************************************************************
  * @file    usbh_hid_mouse.c 
  * @author  MCD Application Team
  * @version V2.1.0
  * @date    19-March-2012
  * @brief   This file is the application layer for USB Host HID Mouse Handling.                  
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2012 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "usbh_hid_gamepad.h"

static void  GAMEPAD_Init (void);
static void  GAMEPAD_Decode(uint8_t *data);

/////////////////////////////////
//volatile uint8_t data_mouse_x = 0;
//volatile uint8_t  data_mouse_y = 0;
//volatile uint8_t  data_mouse_buttons = 0;
/////////////////////////////////    
 
HID_GAMEPAD_Data_TypeDef HID_GAMEPAD_Data;
HID_cb_TypeDef HID_GAMEPAD_cb =
{
  GAMEPAD_Init,
  GAMEPAD_Decode,
};

/**
* @brief  GAMEPAD_Init
*         Init Mouse State.
* @param  None
* @retval None
*/
static void  GAMEPAD_Init ( void)
{
 /* Call User Init*/
 USR_GAMEPAD_Init();
}
            
/**
* @brief  GAMEPAD_Decode
*         Decode Mouse data
* @param  data : Pointer to Mouse HID data buffer
* @retval None
*/
static void  GAMEPAD_Decode(uint8_t *data)
{
	for(int i=0;i<8;i++)
	{
		HID_GAMEPAD_Data.data[i] = data[i];
	}
  
  USR_GAMEPAD_ProcessData(&HID_GAMEPAD_Data);
}