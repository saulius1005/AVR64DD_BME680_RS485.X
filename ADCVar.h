/* 
 * File:   ADCVar.h
 * Author: Saulius
 *
 * Created on Penktadienis, 2026, rugs?jis 18, 16.20
 */

#ifndef ADCVAR_H
#define	ADCVAR_H

#include "ADC.h"


#ifdef	__cplusplus
extern "C" {
#endif

analog_sensors_t AnalogSensors = {
    .WSS = {
        ADC_MUXPOS_AIN29_gc,//adc channel
        VREF_REFSEL_VDD_gc,//reference
        0, //result
        0, //output for weather station
    },
    .WDS = {
        ADC_MUXPOS_AIN30_gc,
        VREF_REFSEL_VDD_gc,
        0,
        0,
    },
    .SLS = {
        ADC_MUXPOS_AIN31_gc,
        VREF_REFSEL_VDD_gc,
        0,
        0,
    },
    .MCU = {
        ADC_MUXPOS_VDDDIV10_gc,
        VREF_REFSEL_1V024_gc,
        3333, //as default MCU voltage is 3.333V
        0,
    }
};

analog_t *ADC0_sensors[4] = {
    &AnalogSensors.WSS,
    &AnalogSensors.WDS,
    &AnalogSensors.SLS,
    &AnalogSensors.MCU
};


#ifdef	__cplusplus
}
#endif

#endif	/* ADCVAR_H */

