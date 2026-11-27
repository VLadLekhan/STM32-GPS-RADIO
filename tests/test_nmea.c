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

int compare_status(const char* name,NMEA_Status_t got, NMEA_Status_t expect){
   if (got == expect){
      printf("PASS: %s\n",name);
      return 0;
   } else {
      printf("FAIL: %s (got %d, expect %d)\n",name,got,expect);
      return 1;
   }

}

int main(void) {
    int   failed = 0;
    const char* gga_line = "$GPGGA,123519,4807.038,N,01131.000,E,1,08,0.9,545.4,M,46.9,M,,*47";
    const char* rmc_line = "$GPRMC,123519,A,4807.038,N,01131.000,E,022.4,084.4,230394,003.1,W*6A";
    const char* ab_with_star = "$AB*";
    const char* ab_no_star = "$AB";
    const char* gga_line_bad_sum = "$GPGGA,123519,4807.038,N,01131.000,E,1,08,0.9,545.4,M,46.9,M,,*00";
    const char* gga_line_no_dollar = "GPGGA,123519,4807.038,N,01131.000,E,1,08,0.9,545.4,M,46.9,M,,*47";
    const char* gga_line_no_star = "$GPGGA,123519,4807.038,N,01131.000,E,1,08,0.9,545.4,M,46.9,M,,47";
    const char* gga_line_bad_sum_with_G = "$GPGGA,123519,4807.038,N,01131.000,E,1,08,0.9,545.4,M,46.9,M,,*4G";
    GpsData_t test_data = {0};

    failed += compare_nmea("NMEA_Checksum_gga",NMEA_Checksum(gga_line),0x47);
    failed += compare_nmea("NMEA_Checksum_rmc",NMEA_Checksum(rmc_line),0x6A);
    failed += compare_nmea("NMEA_Checksum_ab_with_star",NMEA_Checksum(ab_with_star),0x3);
    failed += compare_nmea("NMEA_Checksum_ab_no_star",NMEA_Checksum(ab_no_star),0x3);

    failed +=compare_status("NMEA_ParseLine_gga",NMEA_ParseLine(gga_line,&test_data),NMEA_OK);
    failed +=compare_status("NMEA_ParseLine_rmc",NMEA_ParseLine(rmc_line,&test_data),NMEA_OK);
    failed +=compare_status("NMEA_ParseLine_gga_bad_sum",NMEA_ParseLine(gga_line_bad_sum,&test_data),NMEA_ERR_CHECKSUM);
    failed +=compare_status("NMEA_ParseLine_gga_no_$",NMEA_ParseLine(gga_line_no_dollar,&test_data),NMEA_ERR_FORMAT);
    failed +=compare_status("NMEA_ParseLine_gga_no_star",NMEA_ParseLine(gga_line_no_star,&test_data),NMEA_ERR_FORMAT);
    failed +=compare_status("NMEA_ParseLine_gga_line_bad_sum_with_G",NMEA_ParseLine(gga_line_bad_sum_with_G,&test_data),NMEA_ERR_FORMAT);

    return failed;
}