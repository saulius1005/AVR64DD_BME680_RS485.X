/* 
 * File:   MCU_Config.h
 * Author: Saulius
 *
 * Created on Tre?iadienis, 2026, rugs?jis 16, 17.34
 */

#ifndef MCU_CONFIG_H
#define	MCU_CONFIG_H

#ifdef	__cplusplus
extern "C" {
#endif

FUSES = {
	.WDTCFG = 0x00, // WDTCFG {PERIOD=OFF, WINDOW=OFF}
	.BODCFG = 0x00, // BODCFG {SLEEP=DISABLE, ACTIVE=DISABLE, SAMPFREQ=128Hz, LVL=BODLEVEL0}
	.OSCCFG = 0x00, // OSCCFG {CLKSEL=OSCHF}
	.SYSCFG0 = 0xD1, // SYSCFG0 {EESAVE=SET, RSTPINCFG=GPIO, UPDIPINCFG=UPDI, CRCSEL=CRC16, CRCSRC=NOCRC}
	.SYSCFG1 = 0x10, // SYSCFG1 {SUT=0MS, MVSYSCFG=SINGLE}
	.CODESIZE = 0x00, // CODESIZE {CODESIZE=User range:  0x0 - 0xFF}
	.BOOTSIZE = 0x00, // BOOTSIZE {BOOTSIZE=User range:  0x0 - 0xFF}
};

LOCKBITS = 0x5CC5C55C; // {KEY=NOLOCK}


#ifdef	__cplusplus
}
#endif

#endif	/* MCU_CONFIG_H */

