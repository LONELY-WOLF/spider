#include "stm32f4xx.h"
#include "init.h"

int main()
{
	/*Обновляем значение переменной SystemCoreClock - системной тактовой частоты, понадобится при дальнейших вычислениях*/
	SystemCoreClockUpdate();

	spider_init();

	while (1)
	{

	}
}
