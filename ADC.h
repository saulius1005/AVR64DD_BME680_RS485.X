/* 
 * File:   ADC.h
 * Author: Saulius
 *
 * Created on Penktadienis, 2026, rugs?jis 18, 16.20
 */

#ifndef ADC_H
#define	ADC_H

#ifdef	__cplusplus
extern "C" {
#endif
    
typedef enum {
    WSS_ch,
    WDS_ch,
    SLS_ch,
    MCU_ch,
}ADC_CH_name_t;
    

typedef struct {
    ADC_MUXPOS_t channel;
    VREF_REFSEL_t reference;
    uint16_t result;
} analog_t;

typedef struct{
    analog_t WSS;
    analog_t WDS;
    analog_t SLS;
    analog_t MCU;
}analog_sensors_t;

extern analog_sensors_t AnalogSensors;
extern analog_t *ADC0_sensors[4];

void ADC0_init();
void ADC_read_ws_wd_sl();


#ifdef	__cplusplus
}
#endif

#endif	/* ADC_H */

