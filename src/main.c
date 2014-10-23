#include "stm32f4xx.h"
#include "init.h"
#include "legs.h"

uint32_t data = 1500;
uint32_t step = 10;
//uint32_t cnt = 0;

void Delay(__IO uint32_t nCount) {
  while(nCount--) {
  }
}

int main()
{
	/*Обновляем значение переменной SystemCoreClock - системной тактовой частоты, понадобится при дальнейших вычислениях*/
	SystemCoreClockUpdate();

	spider_init();

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
