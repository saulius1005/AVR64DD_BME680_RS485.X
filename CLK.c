#include "settings.h"

void CLOCK_INHF_clock_init() {
    ccp_write_io((uint8_t *) &CLKCTRL.MCLKCTRLA, CLKCTRL_CLKSEL_OSCHF_gc);   //selecting internal high frequency clock OCHF
    ccp_write_io((uint8_t *) &CLKCTRL.OSCHFCTRLA, CLKCTRL_FRQSEL_24M_gc); //selecting 24Mhz frequency
    ccp_write_io((uint8_t *) &CLKCTRL.MCLKCTRLB, CLKCTRL_PDIV_2X_gc & ~CLKCTRL_PEN_bm); //disabling frequency divider and run at full speed
    while (CLKCTRL.MCLKSTATUS & CLKCTRL_SOSC_bm) {};
}

void CLOCK_XOSCHF_clock_init(){
	ccp_write_io((uint8_t *) &CLKCTRL.XOSCHFCTRLA, CLKCTRL_SELHF_EXTCLOCK_gc | CLKCTRL_FRQRANGE_24M_gc | CLKCTRL_ENABLE_bm);
	ccp_write_io((uint8_t *) &CLKCTRL.MCLKCTRLA, CLKCTRL_CLKSEL_EXTCLK_gc);
	while (CLKCTRL.MCLKSTATUS & CLKCTRL_SOSC_bm) {};
}
