/* 
 * File:   BME680Var.h
 * Author: Saulius
 *
 * Created on Penktadienis, 2026, balandis 17, 15.41
 */

#ifndef BME680VAR_H
#define	BME680VAR_H


#ifdef	__cplusplus
extern "C" {
#endif

BME680_t BME680 = {
    .STATUS_spi_mem_page = 0,
    .Config = {
        .filter = Filter_coef_0,
        .spi_3w_en = false,
    },
    .Ctrl_meas = {
        .osrs_t = oversampling_SKIP,
        .osrs_p = oversampling_SKIP,
        .mode = sleep_mode,
    },
    .Ctrl_hum = {
        .osrs_h = oversampling_SKIP,
        .spi_3w_init_en = false,
    },
    .hum = 0,
    .temp = 0,
    .pres = 0,
    .calibration_data = {
        .temp_calib_received = false,
        .par_t1 = 0,
        .par_t2 = 0,
        .par_t2 = 0,
    },
};


#ifdef	__cplusplus
}
#endif

#endif	/* BME680VAR_H */

