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
		uint8_t data = USART_ReceiveData(UART4);
		//USART_SendData(UART4, (uint8_t)uart_cnt + 0x30);
		switch (uart_cnt)
		{
			case 0:
			{
				uart_buf[0] = data;
				if (data == 0x1F)
				{
					uart_cnt = 1;
				}
				break;
			}
			case 1:
			case 2:
			case 3:
			{
				if (data == 0x1F)
				{
					uart_buf[uart_cnt] = data;
					uart_cnt++;
				}
				else
				{
					uart_buf[0] = data;
					uart_cnt = 0;
				}
				break;
			}
			case 4:
			case 5:
			case 6:
			case 7:
			case 8:
			{
				uart_buf[uart_cnt] = data;
				uart_cnt++;
				break;
			}
			case 9:
			{
				uart_buf[9] = data;
				uart_cnt = 0;
				uint16_t ux = *(uint16_t *) (uart_buf + 4);
				uint16_t uy = *(uint16_t *) (uart_buf + 6);
				uint16_t uz = *(uint16_t *) (uart_buf + 8);
				int16_t x = *(int16_t *) (&ux);
				int16_t y = *(int16_t *) (&uy);
				int16_t z = *(int16_t *) (&uz);
				float tan = (float) x / (float) z;
				float a = atanf(tan);
				if (a > 0.25)
				{
					SetRoute(ROUTE_RIGHT);
					STM_EVAL_LEDToggle(LED_Red);
					break;
				}
				if (a < -0.25)
				{
					SetRoute(ROUTE_LEFT);
					STM_EVAL_LEDToggle(LED_Green);
					break;
				}
				if (z > 1200)
				{
					SetRoute(ROUTE_BACK);
					STM_EVAL_LEDToggle(LED_Blue);
					break;
				}
				if (z < 800)
				{
					SetRoute(ROUTE_FORWARD);
					//STM_EVAL_LEDToggle(LED_Orange);
					break;
				}
				SetRoute(ROUTE_STOP);
				break;
			}
		}
	}
}
