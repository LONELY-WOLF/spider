# Spider firmware
Firmware for hexapod robot based on STM32F4 (STM32F4DISCOVERY board)

## Functions

### Input
* USB gamepad.

:heavy_exclamation_mark: `WARNING! Status packet structure is hardcoded.`
* External commands from USART4. *Under development* You can implement your own protocol. Works great for HC-05 + smartphone.

### Motor control
* Legacy control via precalculated tables. This part was ported from old AVR firmware. Stable. Main type of control for now.
* Onboard math. New feature. *Under development*

## Hardware

### PWM config

| Servo    | TIM | Channel | Pin | | Servo     | TIM | Channel | Pin |
|----------|:---:|:-------:|:---:|-|-----------|:---:|:-------:|:---:|
|**Left 1**|     |         |     | |**Right 1**|     |         |     |
| H1       |  2  |    2    | A1  | | H1        |  9  |    2    | E6  |
| V2       |  2  |    4    | A3  | | V2        |  9  |    1    | E5  |
| V3       |  2  |    3    | A2  | | V3        |  4  |    3    | B8  |
|**Left 2**|     |         |     | |**Right 2**|     |         |     |
| H1       |  3  |    4    | B1  | | H1        |  4  |    2    | B7  |
| V2       |  1  |    1    | E9  | | V2        |  3  |    2    | B5  |
| V3       |  1  |    2    | E11 | | V3        |  3  |    3    | B0  |
|**Left 3**|     |         |     | |**Right 3**|     |         |     |
| H1       |  1  |    3    | E13 | | H1        |  1  |    4    | E14 |
| V2       | 12  |    1    | B14 | | V2        |  2  |    1    | A15 |
| V3       | 12  |    2    | B15 | | V3        |  3  |    1    | C6  |

### UARTs

| UART       | TX   | RX   |Function          |
|------------|:----:|:----:|------------------|
| **USART3** | PB10 | PB11 | Flashing via DFU |
| **USART4** | PA0  | PC11 | Command channel  |

I use DFU because ST-LINK on my Discovery is dead. It's more like "reserved pins".  
Second UART is for external commands. This part is currently under development.
