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
