#include "settings.h"
#include "MCU_Config.h"

int main() {   
    
    CLOCK_INHF_clock_init();
    GPIO_init();
    USART0_init();
    SPI_init();
    uint32_t test = 0;
    while(1){
        test = BME680_exchange_data(0x50 | 0x80, 1 , true);
        
        USART_printf("data: %lx",  test);
        _delay_ms(1000);
    }
}


