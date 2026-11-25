#include "nmea.h"

NMEA_Status_t NMEA_ParseLine(const char* line, GpsData_t* data){
    return NMEA_ERR_UNSUPPORTED;
}

uint8_t NMEA_Checksum(const char* line){
    return 0;
}
