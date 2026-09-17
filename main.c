#include "settings.h"
#include "MCU_Config.h"

int main() {   
    
    CLOCK_INHF_clock_init();
    GPIO_init();
    USART0_init();
    SPI_init();

    while(1){
        //BME680_read_ID();
        //USART_printf("data %x", BME680.ID);
        BME680_read_t_p_rh();
        //BME680_exchange_data(0x00f31073, 3, true);
        //USART_printf("data %lx", BME680_exchange_data(0x007310f3, 3, true));
        //BME680_exchange_data(0x7310, 2, true);
        //BME680_exchange_data(0x73, 1, true);
        //BME680_exchange_data(0x73, 1, false);
        USART_printf("Temperature:%3dC° ", (BME680.temperature + 50) / 100);
        USART_printf("Pressure: %4dhPa ", (BME680.pressure + 50) / 100);
        USART_printf("Humidity: %3d% ", (BME680.humidity + 500) / 1000);
        _delay_ms(300);
    }
}


