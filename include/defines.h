#pragma once

#ifdef DEBUG
    #define uint8_t unsigned int
    #define  int8_t   signed int
#else
    typedef unsigned char uint8_t;
    typedef signed char int8_t;
#endif // DEBUG
typedef unsigned int  uint32_t;