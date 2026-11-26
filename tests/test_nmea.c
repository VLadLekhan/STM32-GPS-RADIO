#include <stdio.h>
#include <stdbool.h>
#include "nmea.h"


bool compare_nmea(const char *name, uint8_t got, uint8_t expect){
 if(got == expect){
    printf("PASS: %s\n",name);
    return 0;
 } else {
    printf("FAIL: %s\n",name);
    return 1;
 }
}

int main(void) {
    int   failed = 0;
    const char* gga_line = "$GPGGA,123519,4807.038,N,01131.000,E,1,08,0.9,545.4,M,46.9,M,,*47";
    const char* rmc_line = "$GPRMC,123519,A,4807.038,N,01131.000,E,022.4,084.4,230394,003.1,W*6A";
    const char* ab_test = "$AB*";
    const char* ab_star_test = "$AB";

    failed += compare_nmea("NMEA_Checksum_gga",NMEA_Checksum(gga_line),0x47);
    failed += compare_nmea("NMEA_Checksum_rmc",NMEA_Checksum(rmc_line),0x6A);
    failed += compare_nmea("NMEA_Checksum_ab_test",NMEA_Checksum(ab_test),0x3);
    failed += compare_nmea("NMEA_Checksum_b_star_tes",NMEA_Checksum(ab_star_test),0x3);
    
    return failed;
}