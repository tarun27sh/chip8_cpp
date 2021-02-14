#include<arpa/inet.h>
#include"opcode.h"
Opcode::Opcode(uint16_t raw_opc) 
{
    this->raw_opc = ntohs(raw_opc);
}
