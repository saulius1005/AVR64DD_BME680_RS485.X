#include "settings.h"
#include "MCU_Config.h"

int main() {   
    
    CLOCK_INHF_clock_init();//use internal clock
    GPIO_init();
    USART0_init();
    SPI_init();
    ADC0_init();
            
    while(1){
        RS485_RX();
    }
}


