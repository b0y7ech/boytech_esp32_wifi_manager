/******************************************************************
 Libraries   : Re-define datatype
 Author      : Nguyen Hai Linh
 Description : The Modbus
******************************************************************/

#ifndef COMMON_H
#define COMMON_H

#include <Arduino.h>
#include <vector>

#ifndef ENABLE_UART_TRACE
    #define ENABLE_UART_TRACE
#endif   

#ifdef ENABLE_UART_TRACE
    #define TRACE(...) Serial.printf(__VA_ARGS__)
#else
    #define TRACE(...) while (0) {}
#endif

#endif //COMMON_H
