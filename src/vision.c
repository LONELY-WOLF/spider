#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "legs.h"
#include "walk_legacy.h"
#include <math.h>

uint8_t uart_buf[32];
int uart_cnt = 0;

void UART4_IRQHandler()
{
	if (USART_GetITStatus(UART4, USART_IT_RXNE) != RESET)
	{
		USART_ClearITPendingBit(UART4, USART_IT_RXNE);
		STM_EVAL_LEDToggle(LED_Blue);
		uint8_t data = USART_ReceiveData(UART4);
		if(LegsUpdated)
		{
			switch (uart_cnt)
			{
				case 0:
				{
					uart_buf[0] = data;
					uart_cnt++;
					break;
				}
				case 1:
				{
					if ((uart_buf[0] == 0x1F) && (data == 0x1F))
					{
						uart_buf[1] = data;
						uart_cnt++;
					}
					else
					{
						uart_buf[0] = data;
						uart_cnt = (data == 0x1F) ? 1 : 0;
					}
					break;
				}
				case 2:
				case 3:
				case 4:
				case 5:
				case 6:
				{
					uart_buf[uart_cnt] = data;
					break;
				}
				case 7:
				{
					uart_buf[7] = data;
					uint16_t ux = *(uint16_t *) (uart_buf + 2);
					uint16_t uy = *(uint16_t *) (uart_buf + 4);
					uint16_t uz = *(uint16_t *) (uart_buf + 6);
					int16_t x = *(int16_t *) (&ux);
					int16_t y = *(int16_t *) (&uy);
					int16_t z = *(int16_t *) (&uz);
					float a = atanf(((float) x) / (float) z);
					if (a > 0.25)
					{
						Now_Route = ROUTE_RIGHT;
						break;
					}
					if (a < -0.25)
					{
						Now_Route = ROUTE_LEFT;
						break;
					}
					if (z > 1200)
					{
						Now_Route = ROUTE_BACK;
						break;
					}
					if (z < 800)
					{
						Now_Route = ROUTE_FORWARD;
						break;
					}
					Now_Route = ROUTE_STOP;
					break;
				}
				Step();
				LegsUpdated = 0;
			}
		}
	}
}
