#include "settings.h"

void SPI_init() { //speed = f_cpu / 4 * 2 = 
	 SPI0.CTRLA = SPI_ENABLE_bm        // Enable SPI
	 | SPI_MASTER_bm        // Master mode
	 | SPI_PRESC_DIV4_gc    // Clock prescaler
	 /*| SPI_CLK2X_bm*/;			// Double speed
       
	 SPI0.CTRLB = SPI_SSD_bm // Slave select disabled (manual control)
        | SPI_MODE_0_gc; // SPI Mode 3
 }

uint8_t SPI_exchange_data(uint8_t data){
    SPI0.DATA = data;
    while (!(SPI0.INTFLAGS & SPI_IF_bm));
    SPI0.INTFLAGS = SPI_IF_bm;
    return SPI0.DATA;
}

void SPI_write(uint8_t data) { //write only
	 SPI0.DATA = data;
	 while (!(SPI0.INTFLAGS & SPI_IF_bm)); // Wait for transfer complete
	 //(void)SPI0.DATA; // Read to clear interrupt flag
     SPI0.INTFLAGS = SPI_IF_bm;
 }
