/*
 * opcode.h - opcode represenation
 */
#ifndef _OPCODE_H_
#define _OPCODE_H_
#include<array>
#include<cstdint>

class Opcode {
    uint16_t raw_opc;
    //opcode_u opu;
public:
    Opcode(uint16_t raw_Opcode);
    //: Opcode_u.raw (raw_Opcode);
    //~Opcode();
    int getRawOpcode(){return (raw_opc);               }
    int getInstType() {return (raw_opc & 0xF000U) >> 12;}
    int getLowByte()  {return (raw_opc & 0xFFU);        }
    int getNNN()      {return (raw_opc & 0xFFFU);       }
    int getRegVx()    {return (raw_opc & 0x0F00U) >> 8; }
    int getRegVy()    {return (raw_opc & 0x00F0U) >> 4; }
    int getString()   {return (raw_opc & 0x00F0U) >> 4; }
};

#endif // _OPCODE_H_
