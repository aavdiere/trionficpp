#pragma once

#ifdef DEBUG
    #define uint8_t unsigned int
#else
    typedef unsigned char uint8_t;
#endif // DEBUG
typedef unsigned int  uint32_t;