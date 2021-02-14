#ifndef _CHIP8_H_
#define _CHIP8_H_
/*
 * chip8.h - CHIP8 internals
 */
#include<cstdint>
#include<iostream>
#include<array>
#include<vector>
#include<stack>
#include"graphics.h"
#include"../inc/ichip8.h"
//#include"inc/ichip8.h"
#include <memory>


struct Timers {
    uint8_t delay;
    uint8_t sound;
};


constexpr uint8_t nof_registers = 16;
constexpr uint16_t size_of_ram_bytes = 4096;
constexpr uint8_t size_of_stack_bytes = 16;
constexpr uint16_t size_of_graphics_pixel = (64*32);
constexpr uint8_t size_of_graphics_width = 64;
constexpr uint8_t size_of_graphics_height = 32;
enum  wtype {
    MAIN_WINDOW,
    DEBUG_WINDOW
};

// nested class impl
class Chip8::Impl {
public:
    Impl();
    ~Impl();
    void executeInstructions();
    void executeOneInstruction();
    /* The first 512 bytes, from 0x000 to 0x1FF, are where the original 
     * interpreter was located, and should not be used by programs.  
     * http://devernay.free.fr/hacks/chip8/C8TECH10.HTM#0.1
     */
    std::array<char, size_of_ram_bytes>  ram{};
    std::array<uint8_t, nof_registers>  v_reg{};
    uint16_t i_reg;
    std::array<uint16_t, size_of_stack_bytes>  stack{};
    uint16_t *sp;             // ptr to stack
    uint16_t *pc;
    Timers timer;
    uint8_t  input_kb;        // 4bits - 16 keys
    std::array<uint8_t, size_of_graphics_pixel>  graphics{};

    /* inject this dependency instead of making class depend on it */
    std::unique_ptr<WindowObject>    pwin; // print window 
    std::unique_ptr<WindowObject>    dwin; // debug window 
};
#endif // _CHIP8_H_
