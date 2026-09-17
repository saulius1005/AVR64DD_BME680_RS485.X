/* 
 * File:   USART.h
 * Author: Saulius
 *
 * Created on Penktadienis, 2026, vasaris 27, 11.13
 */

#ifndef USART_H
#define	USART_H

#ifdef	__cplusplus
extern "C" {
#endif

#define USART0_BAUD_RATE(BAUD_RATE) ((float)(F_CPU * 64 / (8 *(float)BAUD_RATE)) + 0.5) //UART baud calculation
void USART0_init();
void USART_printf(const char *format, ...);

#ifdef	__cplusplus
}
#endif

#endif	/* USART_H */

