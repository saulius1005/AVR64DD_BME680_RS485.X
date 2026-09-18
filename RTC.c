#include "settings.h"
#include "RTCVar.h"

void RTC_ON(uint16_t period_ms){
    while (RTC.STATUS > 0);
    RTC.CLKSEL = RTC_CLKSEL_OSC1K_gc;
    RTC.PER = (uint16_t)(period_ms * 1.024) + 0.5;  
    RTC.CNT = 0;
    RTC.CTRLA = RTC_RTCEN_bm | RTC_PRESCALER_DIV1_gc;
}
