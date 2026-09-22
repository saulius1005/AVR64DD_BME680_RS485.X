/* 
 * File:   RS485.h
 * Author: Saulius
 *
 * Created on Penktadienis, 2026, rugs?jis 18, 21.40
 */

#ifndef RS485_H
#define	RS485_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#define RS485_CMD_LENGTH 10 // usart command length received from weather station 
    
#define RX_LED_ON()    (PORTA.OUTCLR = PIN3_bm)
#define RX_LED_OFF()    (PORTA.OUTSET = PIN3_bm)
    
#define TX_LED_ON()    (PORTA.OUTCLR = PIN2_bm)
#define TX_LED_OFF()    (PORTA.OUTSET = PIN2_bm) 

void RS485_TX(); //data send to weather station function   
void RS485_RX(); //infinite wait for command from weather station until  receive "{GET}"    

#ifdef	__cplusplus
}
#endif

#endif	/* RS485_H */

