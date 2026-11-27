#include "nmea.h"
#include <string.h>

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


