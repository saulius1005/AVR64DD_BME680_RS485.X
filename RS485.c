#include "settings.h"
#include "RS485Var.h"

void RS485_TX() {   
        
    USART0_printf("[%02x%04x%02x%02x%02x%04x%02x]",
        (uint8_t)BME680.temperature,
        (uint16_t)BME680.pressure,
        (uint8_t)BME680.humidity,
        (uint8_t)ADC0_sensors[WSS_ch]->out, 
        (uint8_t)ADC0_sensors[WDS_ch]->out,
        (uint16_t)ADC0_sensors[SLS_ch]->result,
        (uint8_t)crc_packer()
    );
}

void measure_all_data(){
    //data collecting , computing and send took about 210ms (active time)
    TX_LED_ON(); //turn on tx led
    ADC_read_ws_wd_sl(); //measure analog sensors data (Wind speed, direction and light level)
    BME680_read_t_p_rh(); //measure bme680 temperature, pressure and humidity
    RS485_TX(); //send all data to weather station
    TX_LED_OFF(); // turn off TX led
}


void RS485_RX(){
    static uint8_t index = 0;
	static char cmd[RS485_CMD_LENGTH] = {0}; // Empty command array
	static uint8_t start = 0;

    char c = USART0_readChar(); // Reading a character from USART
    
    if (c == '{') { // If received cmd start symbol
        start = 1;
        index = 0;
        RX_LED_ON();
    }    
    if (start) {
        if (c == '}') { // If received cmd end symbol
            RX_LED_OFF();
            start = 0;
            cmd[index] = 0;
            index = 0;
            if (strstr(cmd, "GET") != NULL) { //if received GET command 
                measure_all_data(); //start measure and compute all data from the sensors
            }				
        } 
        else if (index < RS485_CMD_LENGTH) {// fill aray
            cmd[index++] = c; // Store received character in command array
        }
        else{ //if array full start from beginning
            index = 0;
            start = 0;
        }
    }

}