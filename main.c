#include "settings.h"
#include "MCU_Config.h"

int main() {   
    
    CLOCK_INHF_clock_init();
    GPIO_init();
    USART0_init();
    SPI_init();
    ADC0_init();

    while(1){
        ADC_read_ws_wd_sl();
        BME680_read_t_p_rh();
        USART_printf("Temperature:%3dC° ", (BME680.temperature + 50) / 100);
        USART_printf("Pressure: %4dhPa ", (BME680.pressure + 50) / 100);
        USART_printf("Humidity: %3d% ", (BME680.humidity + 500) / 1000);
        
        USART_printf("MCU: %dmV", ADC0_sensors[3]->result );
        USART_printf("WS: %dmV", ADC0_sensors[0]->result );
        USART_printf("WD: %dmV", ADC0_sensors[1]->result );
        USART_printf("SL: %dmV", ADC0_sensors[2]->result );
        
        _delay_ms(1000);
    }
}


