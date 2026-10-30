#include "DATprotocol.hpp"

class DATProtocol{
    public:
        Frame frame;
        ProtocolState state;
        DATProtocol(){
            reset();
        }
        
        DATResult parseByte(uint8_t data){
            switch (state)
            {
            case SOF_State:
                if(data == SOF_BYTE){
                    state = CMD_State;
                }
                else return InvalidSOF;
                break;
            
            case CMD_State:
                frame.cmd = data;
                state = LEN_State;
                break;
            case LEN_State:
                if(data > MAX_DATA_LEN){
                    reset();
                    return InvalidLen;
                } 
                frame.len = data;
                frame.count = 0;
                state = DATA_State; 
                break;
            case DATA_State:
                if(frame.count < frame.len){
                    frame.data[frame.count++] = data;
                    if(frame.count == frame.len){
                        state = CRC_State;
                        frame.crc_count = 0x00;
                    }
                }
                break;
            case CRC_State:
                if(frame.crc_count <= 1){
                    frame.crc = (uint16_t)(frame.crc << 8) + data;
                    frame.crc_count ++;
                    if(frame.crc_count == 2){

                    }
                }
                break;
            case EOF_State:
                state = SOF_State;
                if(data != EOF_BYTE) {      
                    return InvalidEOF;
                }
                else{
                    return ValidFrame;
                }
                break;
            }
            
            return ValidByte;
        }

        void reset(){
            state = SOF_State;
            frame.cmd = 0x00;
            frame.len = 0x00;
            frame.crc = 0x00;
            frame.count = 0x00;
            frame.crc_count = 0x00;
        }

};
