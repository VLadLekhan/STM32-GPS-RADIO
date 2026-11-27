#include "nmea.h"
#include <string.h>

static int hex_value(char c){
        if(c >= '0' && c <= '9'){
            return c - '0';
        } else if(c >= 'A' && c <= 'F') {
            return c - 'A' + 10;
        } else if(c >= 'a' && c <= 'f'){
            return c - 'a' + 10;
        } else {
            return -1;
        }

}

NMEA_Status_t NMEA_ParseLine(const char* line, GpsData_t* data){
    if(line[0] != '$'){
        return NMEA_ERR_FORMAT;
    }

    const char* star = strchr(line, '*');
    if (star == NULL){
        return NMEA_ERR_FORMAT;
    }

    if(star[1] == '\0'){
        return NMEA_ERR_FORMAT;
    }

    if(star[2] == '\0'){
        return NMEA_ERR_FORMAT;
    }

    int hi = hex_value(star[1]);
    if(hi == -1) return NMEA_ERR_FORMAT;

    int lo = hex_value(star[2]);
    if(lo == -1) return NMEA_ERR_FORMAT;

    int sum = (hi << 4) + lo;

    int check_sum = NMEA_Checksum(line);

    if (sum != check_sum){
        return NMEA_ERR_CHECKSUM;
    }

    (void)data;
 
    return NMEA_ERR_UNSUPPORTED;
}

uint8_t NMEA_Checksum(const char* line){
    uint8_t sum = 0;
    int i = 1;

    while(line[i] != '*' && line[i] != '\0'){
        sum = sum ^ line[i];
        i++;
    }
    return sum;
}


