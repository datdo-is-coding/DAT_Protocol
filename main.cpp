#include "iostream"
#include "stdint.h"
#include <bitset>
#define TRUE 0x01
#define FALSE 0x00

using namespace std;

class CRC
{
public:
    uint16_t crc;
    uint32_t poly;
    uint8_t refin;
    uint8_t refout;
    uint16_t xorout;

    CRC()
    {
        refin = FALSE;
        refout = FALSE;
        xorout = 0x0000;
        crc = 0x0000;
        poly = 0x11021;
    }
    void calculateCRC(uint8_t _byte)
    {
        uint32_t data = (uint32_t)(_byte << 16);

        std::cout << "Hex| " << std::hex << data << std::endl;
        std::cout << "POLY Hex| " << std::hex << poly << std::endl;
        printBin(data);
        printBin(poly);
        int pos = -1;
        
        
        

        for(int i = 24; i >=0 ; i--){
            if(((data >> i) & 1) == 1){
                cout <<std::dec<<i<<" "<< (data>>i)<<endl;
                pos = i - 16;
                break;
            }
        }
        printBin(data);
        printBin(poly << pos);

        std::cout << std::endl;
    }
    void printBin(uint32_t data){
        std::string bitStr = std::bitset<32>(data).to_string();
        std::cout << "Bin| ";

        for (size_t i = 0; i < bitStr.length(); i++) {
            std::cout << bitStr[i];
            // Insert a space every 4 characters
            if ((i + 1) % 4 == 0 && i + 1 != bitStr.length()) {
                std::cout << " ";
            }
        }
        cout<<std::endl;
    }   
};

int main()
{
    CRC num;
    num.calculateCRC(0x31);
    return 0;
    
}
