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
#include "usbh_hid_mouse.h"

static void  MOUSE_Init (void);
static void  MOUSE_Decode(uint8_t *data);

/////////////////////////////////
volatile uint8_t data_mouse_x = 0;
volatile uint8_t  data_mouse_y = 0;
volatile uint8_t  data_mouse_buttons = 0;
/////////////////////////////////    
 
HID_MOUSE_Data_TypeDef HID_MOUSE_Data;
HID_cb_TypeDef HID_MOUSE_cb = 
{
  MOUSE_Init,
  MOUSE_Decode,
};

/**
* @brief  MOUSE_Init
*         Init Mouse State.
* @param  None
* @retval None
*/
static void  MOUSE_Init ( void)
{
 /* Call User Init*/
 USR_MOUSE_Init();
}
            
/**
* @brief  MOUSE_Decode
*         Decode Mouse data
* @param  data : Pointer to Mouse HID data buffer
* @retval None
*/
static void  MOUSE_Decode(uint8_t *data)
{
  HID_MOUSE_Data.button = data[0];

  HID_MOUSE_Data.x      = data[1];
  HID_MOUSE_Data.y      = data[2];
  
//////////////////////////////////////////  added by "STM32"
  data_mouse_x = HID_MOUSE_Data.y;
  data_mouse_y = HID_MOUSE_Data.x;
  
  if(HID_MOUSE_Data.button != 0)
  {
    data_mouse_buttons = HID_MOUSE_Data.button;  
  }
////////////////////////////////
  
  USR_MOUSE_ProcessData(&HID_MOUSE_Data);

}
