/* 
 * File:   settings.h
 * Author: Saulius
 *
 * Description:
 *   Global project configuration header.
 *   Contains CPU frequency definition, common includes,
 *   and forward declarations for low-level hardware modules:
 *   clock setup, GPIO, SERCOM (SPI), DMA, and ILI9341 LCD driver.
 *
 * Created on: Thursday, 29 January 2026, 14:24
 */

#ifndef SETTINGS_H
#define	SETTINGS_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <xc.h>
#include <avr/cpufunc.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include "CLK.h"
#include "GPIO.h"    
#include "USART.h"
#include "SPI.h"
#include "BME680.h"
#include "ADC.h"
#include "RTC.h"
#include "RS485.h"
#include "crc8.h"


#ifdef	__cplusplus
}
#endif

#endif	/* SETTINGS_H */
