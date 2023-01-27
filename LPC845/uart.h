#include <stdint.h>

#define USART0_BASE            (0x40064000u)
/** Peripheral USART0 base pointer */
#define USART0      ((USART_Type *)USART0_BASE)
/** Peripheral USART1 base address */

#define		NVIC_ISER0					(*((volatile uint32_t *)(0xE000E100)))
#define		NVIC_CLR0					(*((volatile uint32_t *)(0xE000E180)))

#define		SYSCON_SYSAHBCLKCTRL0		(*((volatile uint32_t *)(0x40048080)))
#define		SYSCON_PRESETCTRL0			(*((volatile uint32_t *)(0x40048088)))
#define		SYSCON_UART0CLKSEL			(*((volatile uint32_t *)(0x40048090)))

#define 	USART_STAT_RXRDY_MASK		(1 << 0)
#define		USART_STAT_TXRDY_MASK		(1 << 2)

#define		RXBUFFER_SIZE				(64)
#define		TXBUFFER_SIZE				(64)

#define     START_TX                    (USART0->INTENSET = (1 << 2))

void pushTx (uint8_t dato);
uint16_t popTx(void);
uint16_t popTx(void);
int16_t Transmitir (const void * datos , uint8_t cant);
void UART_Init(void);