#ifndef DATPROTOCOL_H
#define DATPROTOCOL_H

#include "stdint.h"

#define SOF_BYTE 0xAA
#define EOF_BYTE 0x0A

#define MAX_DATA_LEN 64

typedef enum{
    InvalidSOF,
    InvalidLen,
    InvalidCRC,
    InvalidEOF,
    ValidByte,
    ValidFrame
}DATResult;

typedef enum{
    SOF_State,
    CMD_State,
    LEN_State,
    DATA_State,
    CRC_State,
    EOF_State
}ProtocolState;

typedef struct{
    uint8_t cmd;
    uint8_t len;
    uint8_t data[MAX_DATA_LEN];
    uint16_t crc;
    uint8_t count;
    uint8_t crc_count;
}Frame;

class DATProtocol{
    public:
        Frame frame;
        ProtocolState state;
        DATProtocol();
        
        DATResult parseByte(uint8_t data);

        void reset();

};
#endif