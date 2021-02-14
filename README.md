## How to run ?

    1. $  mkdir build && cd build/
    2. $  cmake ../
    3. $  make
 
    4. Run
        $  ./src/chip8 <path-to-ibm_logo.ch8>
    
        ┌──────────────────────────────────────────────────────────────┐ ┌──────────────────────────────────────────────────────────────┐ 
        │                                                              │ │[30]-- draw sprite(33, 8)                                     │
        │                                                              │ │[31]instr_offset=0x21c, opc=0x7008, inst_type=0x7             │
        │                                                              │ │[32]-- add 8 to Vx[0]=33                                      │
        │                                                              │ │[33]instr_offset=0x21e, opc=0xa266, inst_type=0xa             │
        │                                                              │ │[34]-- set I to NNN, i_reg=0x266                              │
        │                                                              │ │[35]instr_offset=0x220, opc=0xd01f, inst_type=0xd             │
        │                                                              │ │[36]-- draw sprite(41, 8)                                     │
        │           ######## #########   #####         #####           │ │[37]instr_offset=0x222, opc=0x7008, inst_type=0x7             │
        │                                                              │ │[38]-- add 8 to Vx[0]=41                                      │
        │           ######## ########### ######       ######           │ │[39]instr_offset=0x224, opc=0xa275, inst_type=0xa             │
        │                                                              │ │[40]-- set I to NNN, i_reg=0x275                              │
        │             ####     ###   ###   #####     #####             │ │[41]instr_offset=0x226, opc=0xd01f, inst_type=0xd             │
        │                                                              │ │[42]-- draw sprite(49, 8)                                     │
        │             ####     #######     ####### #######             │ │[43]instr_offset=0x228, opc=0x1228, inst_type=0x1             │
        │                                                              │ │[44]-- jump to 0x228                                          │
        │             ####     #######     ### ####### ###             │ │                                                              │
        │                                                              │ │                                                              │
        │             ####     ###   ###   ###  #####  ###             │ │                                                              │
        │                                                              │ │                                                              │
        │           ######## ########### #####   ###   #####           │ │                                                              │
        │                                                              │ │                                                              │
        │           ######## #########   #####    #    #####           │ │                                                              │
        │                                                              │ │                                                              │
        │                                                              │ │                                                              │
        │                                                              │ │                                                              │
        │                                                              │ │                                                              │
        │                                                              │ │                                                              │
        │                                                              │ │                                                              │
        │                                                              │ │                                                              │
        │                                                              │ │                                                              │
        └──────────────────────────────────────────────────────────────┘ └──────────────────────────────────────────────────────────────┘
    
    5. Run tests (using gtest)
       $  ./test/chip8t
       [==========] Running 18 tests from 1 test suite.
       [----------] Global test environment set-up.
       [----------] 18 tests from chip8Test
       [ RUN      ] chip8Test.readRomInvalidPath
       [       OK ] chip8Test.readRomInvalidPath (4 ms)
       [ RUN      ] chip8Test.readRomValidPath
       [       OK ] chip8Test.readRomValidPath (6 ms)
       [ RUN      ] chip8Test.readRomValidPathOpCode0x
       [       OK ] chip8Test.readRomValidPathOpCode0x (326 ms)
       [ RUN      ] chip8Test.readRomValidPathOpCode1x
       [       OK ] chip8Test.readRomInvalidPath (6 ms)
       [ RUN      ] chip8Test.readRomValidPath
       [       OK ] chip8Test.readRomValidPath (5 ms)
       [ RUN      ] chip8Test.readRomValidPathOpCode0x
       [       OK ] chip8Test.readRomValidPathOpCode0x (335 ms)
       [ RUN      ] chip8Test.readRomValidPathOpCode1x
       [       OK ] chip8Test.readRomValidPathOpCode1x (216 ms)
       [ RUN      ] chip8Test.readRomValidPathOpCode2x
       [       OK ] chip8Test.readRomValidPathOpCode2x (109 ms)
       [ RUN      ] chip8Test.readRomValidPathOpCode3x
       [       OK ] chip8Test.readRomValidPathOpCode3x (108 ms)
       [ RUN      ] chip8Test.readRomValidPathOpCode4x
       [       OK ] chip8Test.readRomValidPathOpCode4x (109 ms)
       [ RUN      ] chip8Test.readRomValidPathOpCode5x
       [       OK ] chip8Test.readRomValidPathOpCode5x (111 ms)
       [ RUN      ] chip8Test.readRomValidPathOpCode6x
       [       OK ] chip8Test.readRomValidPathOpCode6x (112 ms)
       [ RUN      ] chip8Test.readRomValidPathOpCode7x
       [       OK ] chip8Test.readRomValidPathOpCode7x (109 ms)
       [ RUN      ] chip8Test.readRomValidPathOpCode8x
       [       OK ] chip8Test.readRomValidPathOpCode8x (984 ms)
       [ RUN      ] chip8Test.readRomValidPathOpCode9x
       [       OK ] chip8Test.readRomValidPathOpCode9x (114 ms)
       [ RUN      ] chip8Test.readRomValidPathOpCodeAx
       [       OK ] chip8Test.readRomValidPathOpCodeAx (115 ms)
       [ RUN      ] chip8Test.readRomValidPathOpCodeBxFail
       [       OK ] chip8Test.readRomValidPathOpCodeBxFail (310 ms)
       [ RUN      ] chip8Test.readRomValidPathOpCodeCxFail
       [       OK ] chip8Test.readRomValidPathOpCodeCxFail (226 ms)
       [ RUN      ] chip8Test.readRomValidPathOpCodeDx
       [       OK ] chip8Test.readRomValidPathOpCodeDx (113 ms)
       [ RUN      ] chip8Test.readRomValidPathOpCodeExFail
       [       OK ] chip8Test.readRomValidPathOpCodeExFail (456 ms)
       [ RUN      ] chip8Test.readRomValidPathOpCodeFxFail
       [       OK ] chip8Test.readRomValidPathOpCodeFxFail (2047 ms)
       [----------] 18 tests from chip8Test (5588 ms total)
       
       [----------] Global test environment tear-down
       [==========] 18 tests from 1 test suite ran. (5588 ms total)
       [  PASSED  ] 18 tests.
       
       To run regex matching tests:
       ./test/chip8t --gtest_filter=*1x


    6. run clang tidy on a file
        $  clang-tidy-9 ../chip8.cc -checks='*'
        . . .
        Suppressed 18577 warnings (18577 in non-user code).
        Use -header-filter=.* to display errors from all non-system headers. Use -system-headers to display errors from system headers as well.

