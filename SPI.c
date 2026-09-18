#include "settings.h"

void SPI_init() {
	 SPI0.CTRLA = SPI_ENABLE_bm // Enable SPI
	 | SPI_MASTER_bm        // Master mode
	 | SPI_PRESC_DIV4_gc;    // Clock prescaler
       
	 SPI0.CTRLB = SPI_SSD_bm // Slave select disabled (manual control)
        | SPI_MODE_0_gc; // SPI Mode 0
 }

uint8_t SPI_exchange_data(uint8_t data){
    SPI0.DATA = data; //send
    while (!(SPI0.INTFLAGS & SPI_IF_bm)); //wait transfer
    SPI0.INTFLAGS = SPI_IF_bm;
    return SPI0.DATA; //return answer
}
