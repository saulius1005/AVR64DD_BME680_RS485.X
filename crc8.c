#include "settings.h"
#include "crc8Var.h"


uint8_t crc8_cdma2000(uint8_t* buf, uint8_t i){
	uint8_t crc = 0xFF;
	for (uint8_t j = 0; j < i; j++)
	crc = crc8_table[crc ^ buf[j]];

	return crc;
}

uint8_t crc_packer(){
    uint8_t buf_for_crc8[8]; //temprary buffer for crc calculation
	uint8_t i = 0;
        buf_for_crc8[i++] = (uint8_t)BME680.temperature;
        buf_for_crc8[i++] = (uint8_t)(BME680.pressure >> 8 ); //hb
        buf_for_crc8[i++] = (uint8_t)BME680.pressure & 0xff; //lb
        buf_for_crc8[i++] = (uint8_t)BME680.humidity;
        buf_for_crc8[i++] = (uint8_t)ADC0_sensors[WSS_ch]->out; 
        buf_for_crc8[i++] = (uint8_t)ADC0_sensors[WDS_ch]->out;
        buf_for_crc8[i++] = (uint8_t)(ADC0_sensors[SLS_ch]->result >> 8); //hb;
        buf_for_crc8[i++] = (uint8_t)ADC0_sensors[SLS_ch]->result & 0xff; //lb;
        
    i = crc8_cdma2000(buf_for_crc8, i);    
	return i;
}