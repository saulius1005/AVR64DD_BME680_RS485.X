#include "settings.h"
#include "ADCVar.h"

void ADC0_init() {
    ADC0.CTRLB = ADC_SAMPNUM_ACC16_gc; // 16 measurements //32,64,128 is truncated
    ADC0.CTRLC = ADC_PRESC_DIV256_gc; // 24Mhz / 256 ADC speed = 93.75kHz (160kHz is top)
    ADC0.CTRLD = ADC_SAMPDLY_DLY15_gc | ADC_INITDLY_DLY256_gc ;//15cpu cycles betwean each sample, intialization is 256 cpu cycles after vref selection
    ADC0.SAMPCTRL = 255;//one sampling duration is extended by 255 cpu cycles
    ADC0.CTRLA = ADC_ENABLE_bm | ADC_RESSEL_12BIT_gc; // 12-bit resolution
}

void ADC0_read(ADC_CH_name_t channel) {
    
    ADC0.MUXPOS = ADC0_sensors[channel]->channel;    
    VREF.ADC0REF = ADC0_sensors[channel]->reference;
    
    ADC0.COMMAND = ADC_STCONV_bm; // Start conversion
    while (!(ADC0.INTFLAGS & ADC_RESRDY_bm)); // Wait until result is ready
    uint16_t answer = ADC0.RES>>4;
    if (channel != MCU_ch)
        ADC0_sensors[channel]->result = (uint16_t)(((uint32_t)answer * ADC0_sensors[MCU_ch]->result / 4096));
    else
        ADC0_sensors[channel]->result = (uint16_t)((uint32_t)answer * 1024 / 409.6);
    ADC0.COMMAND = ADC_SPCONV_bm; // Stop conversion
}

void ADC_read_ws_wd_sl(){
    for(uint8_t i = 0; i < 4; i++){
        ADC0_read(3-i); //start from MCU voltage
    }
    
    uint16_t *source[3] = {&ADC0_sensors[WSS_ch]->result, &ADC0_sensors[WDS_ch]->result, &ADC0_sensors[SLS_ch]->result};  
    uint16_t *target[3] = {&ADC0_sensors[WSS_ch]->out, &ADC0_sensors[WDS_ch]->out, &ADC0_sensors[SLS_ch]->out};
    uint16_t *ref = &ADC0_sensors[MCU_ch]->result;
    
    *target[WSS_ch] = (uint8_t)((double)*source[WSS_ch] / *ref * 30); //wind speed
    *target[WDS_ch] = (uint8_t)(*source[WDS_ch] / (*ref / 8)); //wind direction
    //SLS sensor need to calibrate with pyranometer for now i will send raw voltage
    
}