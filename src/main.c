#include "stm32f4xx.h"
#include "init.h"
#include "legs.h"
#include "usb_bsp.h"
#include "usbh_core.h"
#include "usbh_usr.h"
#include "usbh_hid_core.h"

uint32_t data = 1500;
uint32_t step = 10;
//uint32_t cnt = 0;

USB_OTG_CORE_HANDLE USB_OTG_Core_dev;
USBH_HOST USB_Host;

void Delay(__IO uint32_t nCount) {
  while(nCount--) {
  }
}

int main()
{
	/*Обновляем значение переменной SystemCoreClock - системной тактовой частоты, понадобится при дальнейших вычислениях*/
	SystemCoreClockUpdate();

	spider_init();

	__IO uint32_t i = 0;

	/*!< At this stage the microcontroller clock setting is already configured,
	this is done through SystemInit() function which is called from startup
	file (startup_stm32fxxx_xx.s) before to branch to application main.
	To reconfigure the default setting of SystemInit() function, refer to
	system_stm32fxxx.c file
	*/

	/* Init Host Library */
	USBH_Init(&USB_OTG_Core_dev,
			USB_OTG_FS_CORE_ID,
			&USB_Host,
			&HID_cb,
			&USR_Callbacks);

	/* Initialize User Button */
	STM_EVAL_PBInit(BUTTON_USER, BUTTON_MODE_GPIO);

	while (1)
	{
	/* Host Task handler */
	USBH_Process(&USB_OTG_Core_dev , &USB_Host);

	if (i++ == 0x10000)
	{
	  i = 0;
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

void TIM7_IRQHandler(void)
{
	/*cnt++;
	if(cnt == 49)
	{
		GPIO_ToggleBits(GPIOD, GPIO_Pin_12);
		cnt = 0;
	}*/
	//GPIO_SetBits(GPIOD, GPIO_Pin_12);
	if (TIM_GetITStatus(TIM7, TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit(TIM7, TIM_IT_Update);
		data += step;
		for(int i = 0; i < 6; i++)
		{
			Legs[i].V2 = data;
			Legs[i].V3 = data;
		}
		if((data < 1200) || (data > 1800)) step = -step;
		updateLegs();
	}
	//TIM7->SR &= ~TIM_SR_UIF;
}
