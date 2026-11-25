#ifndef NMEA_H
#define NMEA_H

#include <stdint.h>
#include <stdbool.h>

typedef struct {
    uint8_t hour;
    uint8_t min;
    uint8_t sec;
}GpsTime_t;

typedef struct {
    GpsTime_t time;
    int32_t lat_e7;             // latitude and longitude degrees multiply 10^7 
    int32_t lon_e7;
    int32_t altitude_m;         // meters
    bool fix;
    uint8_t satellites_count;  
    float speed;                // nodes
    float course;               // degrees
} GpsData_t;

typedef enum {
    NMEA_OK = 0,
    NMEA_ERR_FORMAT,
    NMEA_ERR_CHECKSUM,
    NMEA_ERR_UNSUPPORTED,
    NMEA_ERR_TOO_LONG
}NMEA_Status_t;


NMEA_Status_t NMEA_ParseLine(const char* line, GpsData_t* data);
uint8_t NMEA_Checksum(const char* line);


#endif /*NMEA_H*/
