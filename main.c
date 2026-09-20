#include "settings.h"
#include "MCU_Config.h"

int main() {   
    
    CLOCK_INHF_clock_init();//use internal clock
    GPIO_init();
    USART0_init();
    SPI_init();
    ADC0_init();
    RTC_ON(1000); //set update time to one second
            
    while(1){
        //data collecting , computing and send took about 210ms (active time)
        if (RTC.INTFLAGS & RTC_OVF_bm){ // once time is end (Led will glow about ~2ms) 
            RTC.INTFLAGS = RTC_OVF_bm; //clear flag
            TX_LED_ON(); //turn on tx led
            ADC_read_ws_wd_sl(); //measure analog sensors data (Wind speed, direction and light level)
            BME680_read_t_p_rh(); //measure bme680 temperature, pressure and humidity
            RS485_TX(); //send all data to weather station
            TX_LED_OFF(); // turn off TX led
        }
    }
}


