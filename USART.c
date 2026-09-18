#include "settings.h"

void USART0_init(){
	USART0.BAUD = (uint16_t)USART0_BAUD_RATE(230400);
    USART0.CTRLA = USART_RS485_ENABLE_gc;
	USART0.CTRLB = /*USART_RXEN_bm |*/ USART_TXEN_bm | USART_RXMODE_CLK2X_gc; //for now no needed of receiving function
	USART0.CTRLC = USART_CMODE_ASYNCHRONOUS_gc | USART_CHSIZE_8BIT_gc | USART_PMODE_DISABLED_gc | USART_SBMODE_1BIT_gc;
}

void USART0_sendChar(char c){
	while (!(USART0.STATUS & USART_DREIF_bm));
	USART0.TXDATAL = c;
}

void USART0_sendString(char *str){
	for(size_t i = 0; i < strlen(str); i++){
		USART0_sendChar(str[i]);
	}
}

char USART0_readChar(){ //but still i keep it
	USART0.STATUS = USART_RXCIF_bm;// clear buffer before reading
	while (!(USART0.STATUS & USART_RXCIF_bm));
	return USART0.RXDATAL;
}

void USART0_printf(const char *format, ...) {
	char buffer[30]; // Temporary buffer for formatted message
	va_list args;
	va_start(args, format);
	vsnprintf(buffer, sizeof(buffer), format, args); // Format the message into the buffer
	va_end(args);
	USART0_sendString(buffer); // Use USART0 for sending
}
