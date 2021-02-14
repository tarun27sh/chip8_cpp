#include"chip8.h"
#include"graphics.h"
#include"opcode.h"
#include<fstream>
#include<memory>
#include<iostream>
#include<cstdio>
#include<cassert>
#include<unistd.h>
#include<ncurses.h>

using namespace std;
#define window_trace(...) do {            \
    pimpl->dwin->trace(__VA_ARGS__); \
} while(0);
#define Iwindow_trace(...) do {            \
    dwin->trace(__VA_ARGS__); \
} while(0);

Chip8::Impl::Impl() {
}
Chip8::Impl::~Impl() {
}
Chip8::Chip8():
    pimpl(new Impl())
{
    // init memory, reg=0
    // setup pc. sp
    pimpl->sp = &pimpl->stack[0];
    pimpl->pc = nullptr;
    // init unique ptrs
    pimpl->pwin = std::unique_ptr<WindowObject>(new WindowObject());
    pimpl->dwin = std::unique_ptr<WindowObject>(new WindowObject());
    
    // graphics init - call only once
    // main "print" window
	pimpl->pwin->ncurses_init();
    pimpl->pwin->init(0, 0, size_of_graphics_height,
     size_of_graphics_width, COLOR_CYAN,
     COLOR_BLACK, 1, 1);
	pimpl->pwin->createCustomWindow();

    // debug window for logs
    pimpl->dwin->init(0, size_of_graphics_width + 1, size_of_graphics_height,
     size_of_graphics_width, COLOR_YELLOW,
     COLOR_BLACK, 2, 1);
	pimpl->dwin->createCustomWindow();

}

#if 0
// copy constructor
Chip8::Chip8(const Chip8& source) {
}

// copy assignment operator
Chip8& Chip8::operator=(const Chip8& source) {
}

// move constructor

// move assignment operator
Chip8& Chip8::operator=(const Chip8&& /*rvalue*/ source) noexcept{
}
#endif
Chip8::~Chip8() {
    // cleanup
    pimpl->pwin->ncurses_cleanup();
    pimpl->dwin->ncurses_cleanup();
}



// rule of 3
// class 'Chip8' defines a non-default destructor but does not define a:
// - copy constructor          | Chip8 obj2(obj1);
// - copy assignment operator  | obj2 = obj1
// - move constructor          | Chip8 obj2(obj1); // move
// - move assignment operator  | obj2 = obj1      // move


bool
Chip8::loadRom(const char* path) {
    // read binary rom file
	window_trace( "reading rom");
    ifstream in_rom;
    in_rom.open(path, ios::binary | ios::ate); // get pointer will be positioned at the end of the file
    if (!in_rom.is_open()) {
	    window_trace( "Error opening rom, exiting");
	    return false;
    }
    int size = in_rom.tellg();
    //unique_ptr<char> in_rom_data(new char(size));
	window_trace( "size=%d B", size);
    in_rom.seekg (0, ios::beg);
    in_rom.read (pimpl->ram.data() + 0x200, size);
    pimpl->pc = reinterpret_cast<uint16_t*>(&pimpl->ram.at(0x200));
    assert(pimpl->pc!=NULL);
    in_rom.close();
    return true;
}


void
Chip8::Impl::executeOneInstruction() {
    int offset=0;
    //assert(pc!=NULL);
    assert(pc!=NULL);
    Opcode opc_obj{*pc};
    offset = (int)((char*)pc - &ram[0]);
    //offset = (int)(&ram[0] - (char*)pc);
    uint16_t opc = opc_obj.getRawOpcode();
    if (!opc) {
        ++pc;
        return;
    }
#define TIME_PER_INSTR 100000
    usleep(TIME_PER_INSTR);
    uint8_t inst_type = opc_obj.getInstType();
    Iwindow_trace("instr_offset=0x%x, opc=0x%04hx, inst_type=0x%hhx\t", offset, opc, inst_type);

    // handle fixed instructions
    switch(opc) {
        case 0x00E0:
            Iwindow_trace( "-- clear display");
            pwin->ncurses_clear_window();
            ++pc;
            return;
        case 0x00EE:
            Iwindow_trace("-- retun from subroutine, pc = 0x%x", sp);
            pc = sp;
            return;
    }

    // handle 1 byte fixed instructions
    switch(inst_type) {
        case 0x0:
            Iwindow_trace("-- Call machine code routine at - x02%x", opc_obj.getNNN());
            ++pc;
            break;
        case 0x1:
            Iwindow_trace("-- jump to 0x%02x", opc_obj.getNNN());
            pc = reinterpret_cast<uint16_t *>(&ram.at(opc_obj.getNNN()) + 0x200);  // fixes IBM logo.rom, tests
            //pc = reinterpret_cast<uint16_t *>(&ram.at(opc_obj.getNNN()));        // test.rom
            break;
        case 0x2:
            Iwindow_trace("-- call subroutine at 0x02%x", opc_obj.getNNN());
            sp = pc + 1; // save pc
            pc = (uint16_t *)(opc_obj.getNNN() + (uint8_t *)&ram);
            break;
        case 0x3:
            Iwindow_trace("-- skip next inst if V[%hhx] == 0x%02x", opc_obj.getRegVx(), opc_obj.getLowByte());
            if (v_reg[opc_obj.getRegVx()] ==  opc_obj.getLowByte()) {
                pc+=2;
            } else {
                ++pc;
            }
            break;
        case 0x4:
            Iwindow_trace("-- skip next inst if V[%hhx] != 0x%02x", opc_obj.getRegVx(), opc_obj.getLowByte());
            if (v_reg[opc_obj.getRegVx()] !=   opc_obj.getLowByte()) {
                pc+=2;
            } else {
                ++pc;
            }
            break;
        case 0x5:
            Iwindow_trace("-- skip next inst if V[0x%hhx] == V[0x%hhx]", opc_obj.getRegVx(), opc_obj.getRegVy());
            if (v_reg[opc_obj.getRegVx()] ==  v_reg[opc_obj.getRegVy()]) {
                pc+=2;
            } else {
                ++pc;
            }
            break;
        case 0x6:
            Iwindow_trace("-- set Vx[%hhd] to 0x%02hhx", opc_obj.getRegVx(), opc_obj.getLowByte());
            ++pc;
            v_reg[opc_obj.getRegVx()] = opc_obj.getLowByte();
            break;
        case 0x7:
            ++pc;
            Iwindow_trace("-- add %d to Vx[%d]=%d", 
                  opc_obj.getLowByte(), opc_obj.getRegVx(), v_reg[opc_obj.getRegVx()]);
            v_reg[opc_obj.getRegVx()] += opc_obj.getLowByte();
            break;
        case 0x8: {
            ++pc;
            uint8_t nibble_0 = opc & 0xF;
            switch (nibble_0) {
                case 0x0:
                    Iwindow_trace("-- Sets VX to VY.");
                    v_reg[opc_obj.getRegVx()] = v_reg[opc_obj.getRegVy()];
                    break;
                case 0x1:
                    Iwindow_trace("-- Sets VX to VX or VY");
                    v_reg[opc_obj.getRegVx()] |= v_reg[opc_obj.getRegVy()];
                    break;
                case 0x2:
                    Iwindow_trace("-- Sets VX to VX & VY");
                    v_reg[opc_obj.getRegVx()] &= v_reg[opc_obj.getRegVy()];
                    break;
                case 0x3:
                    Iwindow_trace("-- Sets VX to VX ^ VY");
                    v_reg[opc_obj.getRegVx()] ^= v_reg[opc_obj.getRegVy()];
                    break;
                case 0x4: {
                    Iwindow_trace("-- Sets VX to VX + VY");
                    uint16_t old_max = std::max(opc_obj.getRegVx(), opc_obj.getRegVy());
                    v_reg[opc_obj.getRegVx()] += v_reg[opc_obj.getRegVy()];
                    v_reg[0xF] = v_reg[opc_obj.getRegVx()] < old_max ? 1 : 0;
                    break;
                          }
                case 0x5: {
                    uint16_t old_max = std::max(opc_obj.getRegVx(), opc_obj.getRegVy());
                    Iwindow_trace("-- Sets VX to VX - VY");
                    v_reg[opc_obj.getRegVx()] -= v_reg[opc_obj.getRegVy()];
                    v_reg[0xF] = v_reg[opc_obj.getRegVx()] > old_max ? 1 : 0;
                    break;
                          }
                case 0x6:
                    Iwindow_trace("-- Sets VX to VX >>1");
                    v_reg[0xF] = v_reg[opc_obj.getRegVx()] & 1;
                    v_reg[opc_obj.getRegVx()] = v_reg[opc_obj.getRegVy()]>>1;
                    break;
                case 0x7:
                    Iwindow_trace("-- Sets VX to VY - VX");
                    v_reg[opc_obj.getRegVx()] = v_reg[opc_obj.getRegVy()] - v_reg[opc_obj.getRegVx()];
                    break;
                case 0xE:
                    Iwindow_trace("-- Sets VX to VX << 1");
                    v_reg[0xF] = v_reg[opc_obj.getRegVx()] & 0x1000;
                    v_reg[opc_obj.getRegVx()] = v_reg[opc_obj.getRegVy()] << 1;
                    break;
                default:
                    Iwindow_trace("-- 0x%04hx - Not Implemented", opc);
            }
                  }
            break;
        case 0x9:
            Iwindow_trace("-- skip next inst if V[0x%hhx] != V[0x%hhx]", 
                  opc_obj.getRegVx(), opc_obj.getRegVy());
            if (v_reg[opc_obj.getRegVx()] !=  v_reg[opc_obj.getRegVy()]) {
                pc+=2;
            } else {
                ++pc;
            }
            break;
        case 0xA:
            ++pc;
            i_reg = opc_obj.getNNN();
            Iwindow_trace("-- set I to NNN, i_reg=0x%hx", i_reg);
            break;
        case 0xB:
            pc = (uint16_t *)(v_reg[0] + &ram.at(opc_obj.getNNN()));
            //pc = reinterpret_cast<uint16_t *>(&ram.at(opc_obj.getNNN()));
            Iwindow_trace("-- jump to addr V0 + NNN=0x%x", pc);
            break;
        case 0xC:
            ++pc;
            Iwindow_trace("-- jump to addr V0 + NNN");
            assert(0);
            break;
        case 0xD: {
                ++pc;
                uint16_t reg1 = v_reg[opc_obj.getRegVx()];
                uint16_t reg2 = v_reg[opc_obj.getRegVy()];
                Iwindow_trace("-- draw sprite(%d, %d)", reg1, reg2);
                uint8_t sprite_height =  opc & 0xF;
                SpriteData spd { reg2, reg1, sprite_height, 8, &ram[i_reg] };
                pwin->draw_sprite_on_window(spd);
            }
            break;

        case 0xE:
            ++pc;
            Iwindow_trace("-- key operation");
            assert(0);
            break;
        case 0xF: {
            uint8_t byte_0 = opc & 0xFF;
            switch (byte_0) {
            case 0x07:
                Iwindow_trace("-- Vx = getDelayTimer()");
                v_reg[opc_obj.getRegVx()] = timer.delay;
                ++pc;
                break;
            case 0x0A:
                Iwindow_trace("-- Vx = getKeyInput() - BLOCKING");
                v_reg[opc_obj.getRegVx()] = input_kb;
                ++pc;
                break;
            case 0x15:
                Iwindow_trace("-- setDelayTimer(Vx)");
                timer.delay = v_reg[opc_obj.getRegVx()];
                ++pc;
                break;
            case 0x18:
                Iwindow_trace("-- setSoundTimer()");
                timer.sound = v_reg[opc_obj.getRegVx()];
                ++pc;
                break;
            case 0x1E:
                Iwindow_trace("-- I+=Vx");
                i_reg += v_reg[opc_obj.getRegVx()];
                ++pc;
                break;
            case 0x29:
                Iwindow_trace("-- I=sprite_addr[Vx]");
                assert(0);
                ++pc;
                break;
            case 0x33:
                Iwindow_trace("-- BCD(vx & 0x0FFF) -> I");
                assert(0);
                ++pc;
                break;
            case 0x55:
                Iwindow_trace("-- dump V* to I");
                assert(0);
                ++pc;
                break;
            default:
                Iwindow_trace("--Not Implemented");
                assert(0);
            }
            break;
        }
        default:
            Iwindow_trace("--Not Implemented");
            assert(0);
    }
}
void
Chip8::executeInstructions() {
    while(pimpl->pc < reinterpret_cast<uint16_t*>(&pimpl->ram[pimpl->ram.size()])) {
        //usleep(TIME_PER_INSTR);
        pimpl->executeOneInstruction();
    }
    pimpl->dwin->trace( "exiting !!");
}
