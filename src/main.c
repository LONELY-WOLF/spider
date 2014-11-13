#include "stm32f4xx.h"
#include "init.h"
#include "legs.h"
#include "usb_bsp.h"
#include "usbh_core.h"
#include "usbh_usr.h"
#include "usbh_hid_core.h"
#include "usbh_hid_gamepad.h"
#include "walk_legacy.h"

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
	USBH_Init(&USB_OTG_Core_dev,
			USB_OTG_FS_CORE_ID,
			&USB_Host,
			&HID_cb,
			&USR_Callbacks);

	/* Initialize User Button */
	STM_EVAL_PBInit(BUTTON_USER, BUTTON_MODE_GPIO);

	Init_Work();

	while (1)
	{
		/* Host Task handler */
		USBH_Process(&USB_OTG_Core_dev, &USB_Host);

		if (LegsUpdated)
		{
			switch (HID_GAMEPAD_Data.HatSwitch)
			{
				case Up:
				{
					Now_Route = 1;
					break;
				}
				case Right:
				{
					Now_Route = 3;
					break;
				}
				case Down:
				{
					Now_Route = 2;
					break;
				}
				case Left:
				{
					Now_Route = 4;
					break;
				}
				default:
				{
					Now_Route = 0;
					break;
				}
			}
			Step();
			/*if (step)
			{
				data += step;
				if (data < 1200) data = 1200;
				if (data > 1800) data = 1800;
				for (int i = 0; i < 6; i++)
				{
					Legs[i].V2 = data;
					Legs[i].V3 = data;
				}
				LegsUpdated = 0;
			}*/
			/*data = 1500 - ((HID_GAMEPAD_Data.Axis[3] - 127) * 1);
			 if (data < 1200) data = 1200;
			 if (data > 1800) data = 1800;
			 for (int i = 0; i < 6; i++)
			 {
			 Legs[i].V2 = data;
			 Legs[i].V3 = data;
			 }
			 delta = ((HID_GAMEPAD_Data.Axis[4] - 127) * 2);
			 Legs[0].V2 += delta;
			 Legs[0].V3 += delta;
			 Legs[5].V2 -= delta;
			 Legs[5].V3 -= delta;

			 Legs[2].V2 -= delta;
			 Legs[2].V3 -= delta;
			 Legs[3].V2 += delta;
			 Legs[3].V3 += delta;*/

			LegsUpdated = 0;
		}
	}

	while (1)
	{
		GPIO_SetBits(GPIOD, GPIO_Pin_13);
		Delay(10000000);
		GPIO_ResetBits(GPIOD, GPIO_Pin_13);
		Delay(10000000);
	}
}

