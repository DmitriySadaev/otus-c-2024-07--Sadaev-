<<<<<<< HEAD
/*!
\file
\defgroup avr_driver_uart
\brief Заголовочный файл avr_driver_uart.h

*/

#ifndef AVR_DRIVER_UART_H_
#define AVR_DRIVER_UART_H_

#include <stdint.h>
#include <avr/io.h>

#ifndef AVR_DRIVER_UART_ASYNC_OPERATION_MODE
#define AVR_DRIVER_UART_ASYNC_OPERATION_MODE 0U
#endif /* AVR_DRIVER_UART_ASYNC_OPERATION_MODE */

#ifndef AVR_DRIVER_UART_SYNC_OPERATION_MODE
#define AVR_DRIVER_UART_SYNC_OPERATION_MODE 1U
#endif /* AVR_DRIVER_UART_SYNC_OPERATION_MODE */

#ifndef AVR_DRIVER_UART_PARITY_DISABLED
#define AVR_DRIVER_UART_PARITY_DISABLED 0U
#endif /* AVR_DRIVER_UART_PARITY_DISABLED */

#ifndef AVR_DRIVER_UART_PARITY_EVEN
#define AVR_DRIVER_UART_PARITY_EVEN 1U
#endif /* AVR_DRIVER_UART_PARITY_EVEN */

#ifndef AVR_DRIVER_UART_PARITY_ODD
#define AVR_DRIVER_UART_PARITY_ODD 2U
#endif /* AVR_DRIVER_UART_PARITY_ODD */

#ifndef AVR_DRIVER_UART_INTERRUPTS_ON
#define AVR_DRIVER_UART_INTERRUPTS_ON 1U
#endif /* AVR_DRIVER_UART_INTERRUPTS_ON */

#ifndef AVR_DRIVER_UART_INTERRUPTS_OFF
#define AVR_DRIVER_UART_INTERRUPTS_OFF 0U
#endif /* AVR_DRIVER_UART_INTERRUPTS_OFF */

#ifndef AVR_DRIVER_UART_SINGLE_SPEED
#define AVR_DRIVER_UART_SINGLE_SPEED 1U
#endif /* AVR_DRIVER_UART_SINGLE_SPEED */

#ifndef AVR_DRIVER_UART_DOUBLE_SPEED
#define AVR_DRIVER_UART_DOUBLE_SPEED 2U
#endif /* AVR_DRIVER_UART_DOUBLE_SPEED */

#ifndef AVR_DRIVER_UART_MULTIPROCESSOR_MODE_ON
#define AVR_DRIVER_UART_MULTIPROCESSOR_MODE_ON 1U
#endif /* AVR_DRIVER_UART_MULTIPROCESSOR_MODE_ON */

#ifndef AVR_DRIVER_UART_MULTIPROCESSOR_MODE_OFF
#define AVR_DRIVER_UART_MULTIPROCESSOR_MODE_OFF 0U
#endif /* AVR_DRIVER_UART_MULTIPROCESSOR_MODE_OFF */

//Основные функции
void avr_driver_uart_init(uint8_t n_uart, uint32_t f_cpu, uint8_t speed_mode, uint32_t baudrate, uint8_t op_mode, uint8_t n_stop_bits, uint8_t n_characters, uint8_t clock_polarity, uint8_t parity, uint8_t interrupts_mode);
void avr_driver_uart_transmitt(uint8_t n_uart, uint8_t data_to_trasmitt);
void avr_driver_uart_transmitt_9bits(uint8_t n_uart, uint16_t data_to_trasmitt);
uint8_t avr_driver_uart_receive(uint8_t n_uart);
uint16_t avr_driver_uart_receive_9bit(uint8_t n_uart);

//Функции для обработки ошибок
uint8_t avr_driver_uart_check_frame_error(uint8_t n_uart);
uint8_t avr_driver_uart_check_data_overrun(uint8_t n_uart);
uint8_t avr_driver_uart_check_parity_error(uint8_t n_uart);

//Функции включения-выключения прерываний
void avr_driver_uart_rx_complete_interrupt_enable(uint8_t n_uart);
void avr_driver_uart_tx_complete_interrupt_enable(uint8_t n_uart);
void avr_driver_uart_data_register_empty_interrupt_enable(uint8_t n_uart);
void avr_driver_uart_rx_complete_interrupt_disable(uint8_t n_uart);
void avr_driver_uart_tx_complete_interrupt_disable(uint8_t n_uart);
void avr_driver_uart_data_register_empty_interrupt_disable(uint8_t n_uart);

=======
/*!
\file
\defgroup avr_driver_uart
\brief Заголовочный файл avr_driver_uart.h

*/

#ifndef AVR_DRIVER_UART_H_
#define AVR_DRIVER_UART_H_

#include <stdint.h>
#include <avr/io.h>

#ifndef AVR_DRIVER_UART_ASYNC_OPERATION_MODE
#define AVR_DRIVER_UART_ASYNC_OPERATION_MODE 0U
#endif /* AVR_DRIVER_UART_ASYNC_OPERATION_MODE */

#ifndef AVR_DRIVER_UART_SYNC_OPERATION_MODE
#define AVR_DRIVER_UART_SYNC_OPERATION_MODE 1U
#endif /* AVR_DRIVER_UART_SYNC_OPERATION_MODE */

#ifndef AVR_DRIVER_UART_PARITY_DISABLED
#define AVR_DRIVER_UART_PARITY_DISABLED 0U
#endif /* AVR_DRIVER_UART_PARITY_DISABLED */

#ifndef AVR_DRIVER_UART_PARITY_EVEN
#define AVR_DRIVER_UART_PARITY_EVEN 1U
#endif /* AVR_DRIVER_UART_PARITY_EVEN */

#ifndef AVR_DRIVER_UART_PARITY_ODD
#define AVR_DRIVER_UART_PARITY_ODD 2U
#endif /* AVR_DRIVER_UART_PARITY_ODD */

#ifndef AVR_DRIVER_UART_INTERRUPTS_ON
#define AVR_DRIVER_UART_INTERRUPTS_ON 1U
#endif /* AVR_DRIVER_UART_INTERRUPTS_ON */

#ifndef AVR_DRIVER_UART_INTERRUPTS_OFF
#define AVR_DRIVER_UART_INTERRUPTS_OFF 0U
#endif /* AVR_DRIVER_UART_INTERRUPTS_OFF */

#ifndef AVR_DRIVER_UART_SINGLE_SPEED
#define AVR_DRIVER_UART_SINGLE_SPEED 1U
#endif /* AVR_DRIVER_UART_SINGLE_SPEED */

#ifndef AVR_DRIVER_UART_DOUBLE_SPEED
#define AVR_DRIVER_UART_DOUBLE_SPEED 2U
#endif /* AVR_DRIVER_UART_DOUBLE_SPEED */

#ifndef AVR_DRIVER_UART_MULTIPROCESSOR_MODE_ON
#define AVR_DRIVER_UART_MULTIPROCESSOR_MODE_ON 1U
#endif /* AVR_DRIVER_UART_MULTIPROCESSOR_MODE_ON */

#ifndef AVR_DRIVER_UART_MULTIPROCESSOR_MODE_OFF
#define AVR_DRIVER_UART_MULTIPROCESSOR_MODE_OFF 0U
#endif /* AVR_DRIVER_UART_MULTIPROCESSOR_MODE_OFF */

//Основные функции
void avr_driver_uart_init(uint8_t n_uart, uint32_t f_cpu, uint8_t speed_mode, uint32_t baudrate, uint8_t op_mode, uint8_t n_stop_bits, uint8_t n_characters, uint8_t clock_polarity, uint8_t parity, uint8_t interrupts_mode);
void avr_driver_uart_transmitt(uint8_t n_uart, uint8_t data_to_trasmitt);
void avr_driver_uart_transmitt_9bits(uint8_t n_uart, uint16_t data_to_trasmitt);
uint8_t avr_driver_uart_receive(uint8_t n_uart);
uint16_t avr_driver_uart_receive_9bit(uint8_t n_uart);

//Функции для обработки ошибок
uint8_t avr_driver_uart_check_frame_error(uint8_t n_uart);
uint8_t avr_driver_uart_check_data_overrun(uint8_t n_uart);
uint8_t avr_driver_uart_check_parity_error(uint8_t n_uart);

//Функции включения-выключения прерываний
void avr_driver_uart_rx_complete_interrupt_enable(uint8_t n_uart);
void avr_driver_uart_tx_complete_interrupt_enable(uint8_t n_uart);
void avr_driver_uart_data_register_empty_interrupt_enable(uint8_t n_uart);
void avr_driver_uart_rx_complete_interrupt_disable(uint8_t n_uart);
void avr_driver_uart_tx_complete_interrupt_disable(uint8_t n_uart);
void avr_driver_uart_data_register_empty_interrupt_disable(uint8_t n_uart);

>>>>>>> f2f8c77ab68784997ceace777433729a63acd840
#endif /* AVR_DRIVER_UART_H_ */