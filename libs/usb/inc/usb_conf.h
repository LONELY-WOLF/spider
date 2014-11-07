/**
  ******************************************************************************
  * @file    usb_conf.h
  * @author  MCD Application Team
  * @version V2.1.0
  * @date    19-March-2012
  * @brief   General low level driver configuration
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USB_CONF__H__
#define __USB_CONF__H__

/* Includes ------------------------------------------------------------------*/

 #include "stm32f4xx.h"
 #include "stm32f4xx_conf.h"
 #include "stm32f4_discovery.h"
 //#include "stm324xg_eval_lcd.h"
// #include "stm324xg_eval_ioe.h"
// #include "stm324xg_eval_sdio_sd.h"

#ifdef USE_USB_OTG_FS 
 #define USB_OTG_FS_CORE
#endif

/****************** USB OTG FS CONFIGURATION **********************************/
#ifdef USB_OTG_FS_CORE
 #define RX_FIFO_FS_SIZE                          128
 #define TXH_NP_FS_FIFOSIZ                         96
 #define TXH_P_FS_FIFOSIZ                          96

// #define USB_OTG_FS_LOW_PWR_MGMT_SUPPORT
// #define USB_OTG_FS_SOF_OUTPUT_ENABLED
#endif

/****************** USB OTG MODE CONFIGURATION ********************************/
#define USE_HOST_MODE
//#define USE_DEVICE_MODE
//#define USE_OTG_MODE

#define __ALIGN_BEGIN
#define __ALIGN_END

#define __packed    __attribute__ ((__packed__))

#endif //__USB_CONF__H__
