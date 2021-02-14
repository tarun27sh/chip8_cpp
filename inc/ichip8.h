#ifndef _ICHIP8_H_
#define _ICHIP8_H_
#include<iostream>
#include<memory>
/*
 * Client Interface
 */

class Chip8 {
    class Impl;
    std::unique_ptr<Impl> pimpl;
public:
    Chip8();
    ~Chip8();
    //virtual bool loadRom(const char* file_path) = 0;
    //virtual void executeInstructions() = 0;
    //~Chip8(){std::cout << "dest empty" << std::endl;}
    bool loadRom(const char* file_path);
    //{std::cout << "loadRom empty" << std::endl;}
    void executeInstructions();
    //void executeOneInstruction();
    //{std::cout << "executeInstructions empty" << std::endl;}
};
#endif
