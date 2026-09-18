#include "settings.h"
#include "BME680Var.h"

uint32_t BME680_exchange_data(uint32_t cmd, uint8_t tx_length, bool send_dummy){ //SPI actions
    uint8_t *p = (uint8_t *)&cmd; //creating 8 bit pointer to uint32 value
    uint32_t answer = 0;

    BME680_CS_LOW();

    for (uint8_t i = 0; i < tx_length + send_dummy; i++) {
        answer |= (uint32_t)SPI_exchange_data( i < tx_length ? p[tx_length - 1 - i] : 0x00 ) << (i * 8);//if it is not last byte send part of uint32 value as byte. And if it last send 0x00 dummy. And filling answer as uint32 value
    }
    BME680_CS_HIGH();
    return answer;
}

static inline uint8_t BME680_SPI_ReadAddr(uint8_t reg){ // to read need to use register add + 0x80
    return reg | 0x80;
}

void BME680_change_page(BME680_page_no_t page){ //most functions are in page 1
    
    if(BME680.STATUS_spi_mem_page == page) //if it is the same page do not change it and skip further code
        return; 
    uint32_t cmd = ((uint32_t)status_ADD << 16) | ((uint16_t)(page == BME680_page_1 ? 0x10 : 0x00) << 8) | BME680_SPI_ReadAddr(status_ADD); //write to reg | value | read reg
    
    uint32_t answer = BME680_exchange_data(cmd, 3, true)>>24;
    
    BME680.STATUS_spi_mem_page = answer & 0x10;
}

void BME680_Config(BME680_filter_t filter, bool spi_3w_en){ //write filter and spi3wire enable values to register 
    
    if((filter == BME680.Config.filter) && (spi_3w_en == BME680.Config.spi_3w_en)) //if filter and spi 3w eneable the same skip further code
        return;
    
    if(!BME680.STATUS_spi_mem_page){ //if page 0 change it to 1
        BME680_change_page(BME680_page_1);
    }
    
    uint32_t cmd = ((uint32_t)Config_ADD << 16) | ((uint32_t)filter << 10) | ((uint32_t)spi_3w_en << 8) | BME680_SPI_ReadAddr(Config_ADD);
    uint32_t answer = BME680_exchange_data(cmd, 3, true)>>24;
    
     BME680.Config.filter = (answer >> 2) & 7;
     BME680.Config.spi_3w_en = answer & 1;
}

void BME680_Ctrl_meas(BME680_meas_os_t os_t, BME680_meas_os_t os_p, BME680_mode_t mode){ //write ctrl meas register
    if((os_t == BME680.Ctrl_meas.osrs_t) && (os_p == BME680.Ctrl_meas.osrs_p) && (mode == BME680.Ctrl_meas.mode))
        return;
    if(!BME680.STATUS_spi_mem_page){ //if page 0 change it to 1
        BME680_change_page(BME680_page_1);
    }
    
    uint32_t cmd = ((uint32_t) Ctrl_meas_ADD << 16) | ((uint16_t)os_t << 13) | ((uint16_t)os_p << 10) | ((uint16_t)mode << 8) | BME680_SPI_ReadAddr(Ctrl_meas_ADD);  
    uint32_t answer = BME680_exchange_data(cmd, 3, true)>>24;
    
    BME680.Ctrl_meas.osrs_t = (answer >> 5) & 7;
    BME680.Ctrl_meas.osrs_p = (answer >> 2) & 7;
    BME680.Ctrl_meas.mode = answer & 3;
}

void BME680_Ctrl_hum(BME680_meas_os_t os_h, bool spi_3w_int_en){ //set humitity and spi 3 wires settings 
    if((os_h == BME680.Ctrl_hum.osrs_h) && (spi_3w_int_en == BME680.Ctrl_hum.spi_3w_init_en))
        return;
    if(!BME680.STATUS_spi_mem_page){ //if page 0 change it to 1
        BME680_change_page(BME680_page_1);
    }
    
    uint32_t cmd = ((uint32_t) Ctrl_hum_ADD << 16) | ((uint16_t)spi_3w_int_en << 14) | ((uint16_t)os_h << 8) | BME680_SPI_ReadAddr(Ctrl_hum_ADD);  
    uint32_t answer = BME680_exchange_data(cmd, 3, true)>>24;
    
    BME680.Ctrl_hum.osrs_h = answer & 7;
    BME680.Ctrl_hum.spi_3w_init_en = (answer >> 6) & 1;
}


void BME680_read_hum(){ 
    if(!BME680.STATUS_spi_mem_page){ //if page 0 change it to 1
        BME680_change_page(BME680_page_1);
    }
    
    uint32_t cmd = BME680_SPI_ReadAddr(hum_msb_ADD); 
    uint32_t answer = BME680_exchange_data(cmd<<8, 2, true)>>8; 

    answer = __builtin_bswap16(answer);

    BME680.hum = answer;

}

void BME680_read_temp(){ 
    if(BME680.STATUS_spi_mem_page != 1){ //if page 0 change it to 1
        BME680_change_page(BME680_page_1);
    }    
   
    uint32_t cmd = BME680_SPI_ReadAddr(temp_msb_ADD);
    uint32_t answer = BME680_exchange_data(cmd<<16, 3, true)>>8;

    answer = __builtin_bswap32(answer)>>8;

    BME680.temp = answer >> 4;

}

void BME680_read_pres(){
    if(BME680.STATUS_spi_mem_page != 1){ //if page 0 change it to 1
        BME680_change_page(BME680_page_1);
    }
    
    uint32_t cmd = BME680_SPI_ReadAddr(pres_msb_ADD);
    uint32_t answer = BME680_exchange_data(cmd<<16, 3, true)>>8;
    
    answer = __builtin_bswap32(answer)>>8;
    
    BME680.pres = answer >> 4;
}

void BME680_read_hum_calib(){//humidity calibration values
    if(BME680.calibration_data.hum_calib_received) //if calibration data already received skip further code
        return;
    
    if(BME680.STATUS_spi_mem_page != 0){ //if page 1 change it to 0
        BME680_change_page(BME680_page_0);
    }   
    uint32_t cmd = par_h2_ADD;
    uint32_t answer = BME680_exchange_data(cmd<<24, 4, false) >> 8; 
    
    BME680.calibration_data.par_h1 = ((answer >> 16) << 4) | ((answer >> 8) & 0xf);    
    BME680.calibration_data.par_h2 = ((answer & 0xff) << 4) | ((answer >> 12) & 0xf); 
    
    cmd = par_h3_ADD;
    answer = BME680_exchange_data(cmd<<24, 4, false) >> 8;
    
    BME680.calibration_data.par_h3 = answer & 0xff;
    BME680.calibration_data.par_h4 = (answer >> 8) & 0xff;
    BME680.calibration_data.par_h5 = answer >> 16;
    
    cmd = par_h6_ADD;
    answer = BME680_exchange_data(cmd<<16, 3, false) >> 8;
    
    BME680.calibration_data.par_h6 = answer & 0xff;
    BME680.calibration_data.par_h7 = answer >> 8;
    
    BME680.calibration_data.hum_calib_received = true;
}

void BME680_read_temp_calib(){ //temperature calibration values
    if(BME680.calibration_data.temp_calib_received) //if calibration data already received skip further code
        return;
    
    if(BME680.STATUS_spi_mem_page != 0){ //if page 1 change it to 0
        BME680_change_page(BME680_page_0);
    }   
    uint32_t cmd = par_t1_ADD;
    uint32_t answer = BME680_exchange_data(cmd<<16, 3, false);
    
    BME680.calibration_data.par_t1 = answer >> 8; //exmp. received ff8e65 but flipped 658eff >> 8 = 658e
    
    cmd = par_t2_ADD;
    answer = BME680_exchange_data(cmd<<24, 4, false);
    
    BME680.calibration_data.par_t2 = (answer >> 8) & 0xffff; //received fff56603 but flipped 0366f5ff >> 8 = 0366f5 & 0xffff = 66f5
    BME680.calibration_data.par_t3 = answer >> 24; //0366f5ff >> 24 = 03
    
    BME680.calibration_data.temp_calib_received = true;
}

void BME680_read_pres_calib(){ //pressure calibration values
if(BME680.calibration_data.pres_calib_received) //if calibration data already received skip further code
        return;
    
    if(BME680.STATUS_spi_mem_page != 0){ //if page 1 change it to 0
        BME680_change_page(BME680_page_0);
    }   
    int32_t cmd = par_p1_ADD;
    int32_t answer = BME680_exchange_data(cmd<<16, 3, false);
    
    BME680.calibration_data.par_p1 = answer >> 8; //exmp. received ff8e65 but flipped 658eff >> 8 = 658e
    
    cmd = par_p2_ADD;
    answer = BME680_exchange_data(cmd<<24, 4, false);
    
    BME680.calibration_data.par_p2 = (answer >> 8) & 0xffff; //received fff56603 but flipped 0366f5ff >> 8 = 0366f5 & 0xffff = 66f5
    BME680.calibration_data.par_p3 = answer >> 24; //0366f5ff >> 24 = 03
    
    cmd = par_p4_ADD;
    BME680.calibration_data.par_p4 = BME680_exchange_data(cmd<<16, 3, false) >> 8;
    
    cmd = par_p5_ADD;
    BME680.calibration_data.par_p5 = BME680_exchange_data(cmd<<16, 3, false) >> 8;
    
    cmd = par_p7_ADD;
    answer = BME680_exchange_data(cmd<<16, 3, false) >> 8;
    
    BME680.calibration_data.par_p7 = answer & 0xff;
    BME680.calibration_data.par_p6 = answer >> 8;
    
    cmd = par_p8_ADD;
    BME680.calibration_data.par_p8 = BME680_exchange_data(cmd<<16, 3, false) >> 8;
       
    cmd = par_p9_ADD;
    answer = BME680_exchange_data(cmd<<24, 4, false);
    
    BME680.calibration_data.par_p9 = (answer >> 8) & 0xffff;
    BME680.calibration_data.par_p10 = answer >> 24;   
    
    BME680.calibration_data.pres_calib_received = true;    
}

void BME680_calculate_temperature(){
    BME680_read_temp_calib(); //reading temperature calibration for bme680 sensor, calibration data not changing, enough to read once
    BME680_read_temp(); //first read temperature value;
    int32_t var1 = ((int32_t)BME680.temp >> 3) - ((int32_t)BME680.calibration_data.par_t1 << 1); 
    int32_t var2 = (var1 * (int32_t)BME680.calibration_data.par_t2) >> 11; 
    int32_t var3 = ((((var1 >> 1) * (var1 >> 1)) >> 12) * ((int32_t)BME680.calibration_data.par_t3 << 4)) >> 14; 
    BME680.t_fine = var2 + var3; 
    BME680.temperature = ((((BME680.t_fine * 5) + 128) >> 8)+ 50) / 100;
}

void BME680_calculate_pressure(){
    BME680_read_pres_calib(); //if already readed it will be skipped
    BME680_read_pres();
    int32_t var1 = ((int32_t)BME680.t_fine >> 1) - 64000; 
    int32_t var2 = ((((var1 >> 2) * (var1 >> 2)) >> 11) * (int32_t)BME680.calibration_data.par_p6) >> 2; 
    var2 = var2 + ((var1 * (int32_t)BME680.calibration_data.par_p5) << 1); 
    var2 = (var2 >> 2) + ((int32_t)BME680.calibration_data.par_p4 << 16); 
    var1 = (((((var1 >> 2) * (var1 >> 2)) >> 13) * ((int32_t)BME680.calibration_data.par_p3 << 5)) >> 3) + (((int32_t)BME680.calibration_data.par_p2 * var1) >> 1);
    var1 = var1 >> 18; 
    var1 = ((32768 + var1) * (int32_t)BME680.calibration_data.par_p1) >> 15; 
    BME680.pressure = 1048576 - BME680.pres; 
    BME680.pressure = (uint32_t)((BME680.pressure - (var2 >> 12)) * ((uint32_t)3125)); 
    if (BME680.pressure >= ((uint32_t)1 << 30)) BME680.pressure = ((BME680.pressure / (uint32_t)var1) << 1); 
    else BME680.pressure = ((BME680.pressure << 1) / (uint32_t)var1); 
    var1 = ((int32_t)BME680.calibration_data.par_p9 * (int32_t)(((BME680.pressure >> 3) * (BME680.pressure >> 3)) >> 13)) >> 12; 
    var2 = ((int32_t)(BME680.pressure >> 2) * (int32_t)BME680.calibration_data.par_p8) >> 13; 
    int32_t var3 = ((int32_t)(BME680.pressure >> 8) * (int32_t)(BME680.pressure >> 8) * (int32_t)(BME680.pressure >> 8) * (int32_t)BME680.calibration_data.par_p10) >> 17; 
    BME680.pressure = (((int32_t)(BME680.pressure) + ((var1 + var2 + var3 + ((int32_t)BME680.calibration_data.par_p7 << 7)) >> 4))+ 50)/ 100;
}

void BME680_calculate_humidity(){
    BME680_read_hum_calib(); //if already readed it will be skipped
    BME680_read_hum();
    int32_t temp_scaled = (int32_t)BME680.temperature; 
    int32_t var1 = (int32_t)BME680.hum - (int32_t)((int32_t)BME680.calibration_data.par_h1 << 4) - (((temp_scaled * (int32_t)BME680.calibration_data.par_h3) / ((int32_t)100)) >> 1); 
    int32_t var2 = ((int32_t)BME680.calibration_data.par_h2 * (((temp_scaled * (int32_t)BME680.calibration_data.par_h4) / ((int32_t)100)) + (((temp_scaled * ((temp_scaled * (int32_t)BME680.calibration_data.par_h5) / ((int32_t)100))) >> 6) / ((int32_t)100)) + ((int32_t)(1 << 14)))) >> 10; 
    int32_t var3 = var1 * var2; 
    int32_t var4 = (((int32_t)BME680.calibration_data.par_h6 << 7) + ((temp_scaled * (int32_t)BME680.calibration_data.par_h7) / ((int32_t)100))) >> 4; 
    int32_t var5 = ((var3 >> 14) * (var3 >> 14)) >> 10; 
    int32_t var6 = (var4 * var5) >> 1; 
    BME680.humidity = (((((var3 + var6) >> 10) * ((int32_t) 1000)) >> 12)+ 500) / 1000;

}

void BME680_read_t_p_rh(){
    BME680_Ctrl_hum(oversampling_x16, false); //humidity oversample and interrupt off       
    BME680_Ctrl_meas(oversampling_x16, oversampling_x16, forced_mode);  //temperature and pressure OS and working mode forced     
    BME680_Config(Filter_coef_127, false); //IIR filter and keep spi 3wire mode disabled 

    BME680_calculate_humidity();                
    BME680_calculate_temperature();
    BME680_calculate_pressure();
    
    BME680_Ctrl_meas(oversampling_x16, oversampling_x16, sleep_mode);  //temperature and pressure OS  go to sleep mode 
}