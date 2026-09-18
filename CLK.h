/* 
 * File:   CLK.h
 * Author: Saulius
 *
 * Created on Ketvirtadienis, 2026, vasaris 26, 17.52
 */

#ifndef CLK_H
#define	CLK_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#define F_CPU 24000000UL //cpu speed

void CLOCK_INHF_clock_init(); //internal cpu clock settings
void CLOCK_XOSCHF_clock_init(); //external cpu clock settings

#ifdef	__cplusplus
}
#endif

#endif	/* CLK_H */

