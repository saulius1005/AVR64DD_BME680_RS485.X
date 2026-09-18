/* 
 * File:   SPI.h
 * Author: Saulius
 *
 * Created on Ketvirtadienis, 2026, rugs?jis 17, 13.05
 */

#ifndef SPI_H
#define	SPI_H

#ifdef	__cplusplus
extern "C" {
#endif

void SPI_init(); //spi initialization
uint8_t SPI_exchange_data(uint8_t data); //spi data exchange of one byte

#ifdef	__cplusplus
}
#endif

#endif	/* SPI_H */

