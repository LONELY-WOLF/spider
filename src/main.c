#include "stm32f4xx.h"
#include "init.h"
#include "legs.h"
#include "usb_bsp.h"
#include "usbh_core.h"
#include "usbh_usr.h"
#include "usbh_hid_core.h"
#include "usbh_hid_gamepad.h"
#include "walk_legacy.h"
#include "walk_math.h"
#include <math.h>

uint32_t data = 1500;
uint32_t step = 10;
//uint32_t cnt = 0;

USB_OTG_CORE_HANDLE USB_OTG_Core_dev;
USBH_HOST USB_Host;

void Delay(__IO uint32_t nCount)
{
	while (nCount--)
	{
	}
}

int main()
{
	int delta;

	/*Обновляем значение переменной SystemCoreClock - системной тактовой частоты, понадобится при дальнейших вычислениях*/
	SystemCoreClockUpdate();

	spider_init();
    /* Configure the LEDs */
    STM_EVAL_LEDInit(LED_Green);
    STM_EVAL_LEDInit(LED_Orange);
    STM_EVAL_LEDInit(LED_Red);
    STM_EVAL_LEDInit(LED_Blue);


    STM_EVAL_LEDOn(LED_Orange);

    /*STM_EVAL_LEDOn(LED_Green);
    STM_EVAL_LEDOn(LED_Orange);
    STM_EVAL_LEDOn(LED_Red);
    STM_EVAL_LEDOn(LED_Blue);*/

	/*!< At this stage the microcontroller clock setting is already configured,
	 this is done through SystemInit() function which is called from startup
	 file (startup_stm32fxxx_xx.s) before to branch to application main.
	 To reconfigure the default setting of SystemInit() function, refer to
	 system_stm32fxxx.c file
	 */
	for (int i = 0; i < 5; i++)
	{
		HID_GAMEPAD_Data.Axis[i] = 127;
	}
	for (int i = 0; i < 12; i++)
	{
		HID_GAMEPAD_Data.Button[i] = 127;
	}
	HID_GAMEPAD_Data.HatSwitch = None;

	/* Init Host Library */
	USBH_Init(&USB_OTG_Core_dev, USB_OTG_FS_CORE_ID, &USB_Host, &HID_cb, &USR_Callbacks);

	Init_Work();

	while (1)
	{
		USBH_Process(&USB_OTG_Core_dev, &USB_Host);

		if (LegsUpdated)
		{
			switch (HID_GAMEPAD_Data.HatSwitch)
			{
				case Up:
				{
					SetRoute(1);
					break;
				}
				case Right:
				{
					SetRoute(3);
					break;
				}
				case Down:
				{
					SetRoute(2);
					break;
				}
				case Left:
				{
					SetRoute(4);
					break;
				}
				default:
				{
					SetRoute(0);
					break;
				}
			}
			Step();

			//SetLegPos(LEG_L2, 0, 150, 120);
			//updateServo(RadToPulse(M_PI_4), &Legs[LEG_L2].H1Conf);

			LegsUpdated = 0;
		}
	}

	/*while (1)
	{
		if(LegsUpdated)
		{
			Step();
			LegsUpdated = 0;
		}
	}*/
}

