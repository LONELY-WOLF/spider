#include "stm32f4xx.h"

extern void spider_init();

int main()
{
	/*Обновляем значение переменной SystemCoreClock - системной тактовой частоты, понадобится при дальнейших вычислениях*/
	SystemCoreClockUpdate();

	spider_init();

	while (1)
		;
}
