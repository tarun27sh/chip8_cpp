#include "gtest/gtest.h"
#include "../inc/ichip8.h"
#include "../lib/chip8.h"


TEST (chip8Test, readRomInvalidPath) {
    Chip8 chip8;
    EXPECT_EQ(false , chip8.loadRom("/tmp/doesnotExist.ch8"));
}

TEST (chip8Test, readRomValidPath) {
    Chip8 chip8;
    /* create a file with 1 opcode */
    system("echo 0x00E0 | xxd -r -p - > /tmp/chip8t1.ch8");
    EXPECT_EQ(true , chip8.loadRom("/tmp/chip8t1.ch8"));
}
TEST (chip8Test, readRomValidPathOpCode0x) {
    {
    Chip8 chip8;
    /* create a file with 1 opcode */
    // 0x00E0
    system("echo  0x00E0 | xxd -r -p -  > /tmp/chip8t1.ch8");
    EXPECT_EQ(true , chip8.loadRom("/tmp/chip8t1.ch8"));
    chip8.executeInstructions();
    }
    {
    Chip8 chip8;
    // 0x00EE
    system("echo 0x00EE  | xxd -r -p - > /tmp/chip8t1.ch8");
    EXPECT_EQ(true , chip8.loadRom("/tmp/chip8t1.ch8"));
    chip8.executeInstructions();
    }
    {
    Chip8 chip8;
    // 0x0NNN
    system("echo   0x0111 | xxd -r -p -  > /tmp/chip8t1.ch8");
    EXPECT_EQ(true , chip8.loadRom("/tmp/chip8t1.ch8"));
    chip8.executeInstructions();
    }
}
TEST (chip8Test, readRomValidPathOpCode1x) {
    {
        Chip8 chip8;
        /* create a file with 1 opcode, jump to out of bounds */
        system("echo 0x1002 | xxd -r -p -  > /tmp/chip8t1.ch8");
        EXPECT_EQ(true , chip8.loadRom("/tmp/chip8t1.ch8"));
        chip8.executeInstructions();
    }
    {
        Chip8 chip8;
        /* create a file with 1 opcode */
        system("echo 0x1001E000 | xxd -r -p -  > /tmp/chip8t1.ch8");
        EXPECT_EQ(true , chip8.loadRom("/tmp/chip8t1.ch8"));
        chip8.executeInstructions();
    }
}
TEST (chip8Test, readRomValidPathOpCode2x) {
    Chip8 chip8;
    /* create a file with 1 opcode */
    system("echo 0x2333 | xxd -r -p -  > /tmp/chip8t1.ch8");
    EXPECT_EQ(true , chip8.loadRom("/tmp/chip8t1.ch8"));
    chip8.executeInstructions();
}
TEST (chip8Test, readRomValidPathOpCode3x) {
    Chip8 chip8;
    /* create a file with 1 opcode */
    system("echo 0x3333 | xxd -r -p -  > /tmp/chip8t1.ch8");
    EXPECT_EQ(true , chip8.loadRom("/tmp/chip8t1.ch8"));
    chip8.executeInstructions();
}
TEST (chip8Test, readRomValidPathOpCode4x) {
    Chip8 chip8;
    /* create a file with 1 opcode */
    system("echo 0x4333 | xxd -r -p -  > /tmp/chip8t1.ch8");
    EXPECT_EQ(true , chip8.loadRom("/tmp/chip8t1.ch8"));
    chip8.executeInstructions();
}
TEST (chip8Test, readRomValidPathOpCode5x) {
    Chip8 chip8;
    /* create a file with 1 opcode */
    system("echo 0x5333 | xxd -r -p -  > /tmp/chip8t1.ch8");
    EXPECT_EQ(true , chip8.loadRom("/tmp/chip8t1.ch8"));
    chip8.executeInstructions();
}
TEST (chip8Test, readRomValidPathOpCode6x) {
    Chip8 chip8;
    /* create a file with 1 opcode */
    system("echo 0x6333 | xxd -r -p -  > /tmp/chip8t1.ch8");
    EXPECT_EQ(true , chip8.loadRom("/tmp/chip8t1.ch8"));
    chip8.executeInstructions();
}
TEST (chip8Test, readRomValidPathOpCode7x) {
    Chip8 chip8;
    /* create a file with 1 opcode */
    system("echo 0x7333 | xxd -r -p -  > /tmp/chip8t1.ch8");
    EXPECT_EQ(true , chip8.loadRom("/tmp/chip8t1.ch8"));
    chip8.executeInstructions();
}
TEST (chip8Test, readRomValidPathOpCode8x) {
    {
        Chip8 chip8;
        /* create a file with 1 opcode */
        system("echo  0x8330 | xxd -r -p -  > /tmp/chip8t1.ch8");
        EXPECT_EQ(true , chip8.loadRom("/tmp/chip8t1.ch8"));
        chip8.executeInstructions();
    }
    {
        Chip8 chip8;
        system("echo 0x8331  | xxd -r -p - > /tmp/chip8t1.ch8");
        EXPECT_EQ(true , chip8.loadRom("/tmp/chip8t1.ch8"));
        chip8.executeInstructions();
    }
    {
        Chip8 chip8;
        system("echo   0x8332 | xxd -r -p -  > /tmp/chip8t1.ch8");
        EXPECT_EQ(true , chip8.loadRom("/tmp/chip8t1.ch8"));
        chip8.executeInstructions();
    }
    {
        Chip8 chip8;
        system("echo   0x8333 | xxd -r -p -  > /tmp/chip8t1.ch8");
        EXPECT_EQ(true , chip8.loadRom("/tmp/chip8t1.ch8"));
        chip8.executeInstructions();
    }
    {
        Chip8 chip8;
        system("echo   0x8334 | xxd -r -p -  > /tmp/chip8t1.ch8");
        EXPECT_EQ(true , chip8.loadRom("/tmp/chip8t1.ch8"));
        chip8.executeInstructions();
    }
    {
        Chip8 chip8;
        system("echo   0x8335 | xxd -r -p -  > /tmp/chip8t1.ch8");
        EXPECT_EQ(true , chip8.loadRom("/tmp/chip8t1.ch8"));
        chip8.executeInstructions();
    }
    {
        Chip8 chip8;
        system("echo   0x8336 | xxd -r -p -  > /tmp/chip8t1.ch8");
        EXPECT_EQ(true , chip8.loadRom("/tmp/chip8t1.ch8"));
        chip8.executeInstructions();
    }
    {
        Chip8 chip8;
        system("echo   0x8337 | xxd -r -p -  > /tmp/chip8t1.ch8");
        EXPECT_EQ(true , chip8.loadRom("/tmp/chip8t1.ch8"));
        chip8.executeInstructions();
    }
    {
        Chip8 chip8;
        system("echo   0x833E | xxd -r -p -  > /tmp/chip8t1.ch8");
        EXPECT_EQ(true , chip8.loadRom("/tmp/chip8t1.ch8"));
        chip8.executeInstructions();
    }
}
TEST (chip8Test, readRomValidPathOpCode9x) {
    Chip8 chip8;
    /* create a file with 1 opcode */
    system("echo 0x9333 | xxd -r -p -  > /tmp/chip8t1.ch8");
    EXPECT_EQ(true , chip8.loadRom("/tmp/chip8t1.ch8"));
    chip8.executeInstructions();
}
TEST (chip8Test, readRomValidPathOpCodeAx) {
    Chip8 chip8;
    /* create a file with 1 opcode */
    system("echo 0xA333 | xxd -r -p -  > /tmp/chip8t1.ch8");
    EXPECT_EQ(true , chip8.loadRom("/tmp/chip8t1.ch8"));
    chip8.executeInstructions();
}

/* Jump to addr, dst should be valid*/
TEST (chip8Test, readRomValidPathOpCodeBx) {
    Chip8 chip8;
    /* create a file with 1 opcode */
    system("echo 0xB001 | xxd -r -p -  > /tmp/chip8t1.ch8");
    EXPECT_EQ(true , chip8.loadRom("/tmp/chip8t1.ch8"));
    chip8.executeInstructions();
}
TEST (chip8Test, readRomValidPathOpCodeCxFail) {
    Chip8 chip8;
    /* create a file with 1 opcode */
    system("echo 0xC333 | xxd -r -p -  > /tmp/chip8t1.ch8");
    EXPECT_EQ(true , chip8.loadRom("/tmp/chip8t1.ch8"));
    ASSERT_DEATH(chip8.executeInstructions(), "Assertion");
}
TEST (chip8Test, readRomValidPathOpCodeDx) {
    Chip8 chip8;
    /* create a file with 1 opcode */
    system("echo 0xD333 | xxd -r -p -  > /tmp/chip8t1.ch8");
    EXPECT_EQ(true , chip8.loadRom("/tmp/chip8t1.ch8"));
    chip8.executeInstructions();
}
TEST (chip8Test, readRomValidPathOpCodeExFail) {
    {
        Chip8 chip8;
        /* create a file with 1 opcode */
        system("echo 0xE39E | xxd -r -p -  > /tmp/chip8t1.ch8");
        EXPECT_EQ(true , chip8.loadRom("/tmp/chip8t1.ch8"));
        ASSERT_DEATH(chip8.executeInstructions(), "Assertion");
    }{
        Chip8 chip8;
        /* create a file with 1 opcode */
        system("echo 0xE3A1 | xxd -r -p -  > /tmp/chip8t1.ch8");
        EXPECT_EQ(true , chip8.loadRom("/tmp/chip8t1.ch8"));
        ASSERT_DEATH(chip8.executeInstructions(), "Assertion");
    }
}
TEST (chip8Test, readRomValidPathOpCodeFxFail) {
    {
        Chip8 chip8;
        /* create a file with 1 opcode */
        system("echo 0xF307 | xxd -r -p -  > /tmp/chip8t1.ch8");
        EXPECT_EQ(true , chip8.loadRom("/tmp/chip8t1.ch8"));
        ASSERT_DEATH(chip8.executeInstructions(), "Assertion");
    }{
        Chip8 chip8;
        /* create a file with 1 opcode */
        system("echo 0xF30A | xxd -r -p -  > /tmp/chip8t1.ch8");
        EXPECT_EQ(true , chip8.loadRom("/tmp/chip8t1.ch8"));
        ASSERT_DEATH(chip8.executeInstructions(), "Assertion");
    }{
        Chip8 chip8;
        /* create a file with 1 opcode */
        system("echo 0xF315 | xxd -r -p -  > /tmp/chip8t1.ch8");
        EXPECT_EQ(true , chip8.loadRom("/tmp/chip8t1.ch8"));
        ASSERT_DEATH(chip8.executeInstructions(), "Assertion");
    }{
        Chip8 chip8;
        /* create a file with 1 opcode */
        system("echo 0xF318 | xxd -r -p -  > /tmp/chip8t1.ch8");
        EXPECT_EQ(true , chip8.loadRom("/tmp/chip8t1.ch8"));
        ASSERT_DEATH(chip8.executeInstructions(), "Assertion");
    }{
        Chip8 chip8;
        /* create a file with 1 opcode */
        system("echo 0xF31E | xxd -r -p -  > /tmp/chip8t1.ch8");
        EXPECT_EQ(true , chip8.loadRom("/tmp/chip8t1.ch8"));
        ASSERT_DEATH(chip8.executeInstructions(), "Assertion");
    }{
        Chip8 chip8;
        /* create a file with 1 opcode */
        system("echo 0xF329 | xxd -r -p -  > /tmp/chip8t1.ch8");
        EXPECT_EQ(true , chip8.loadRom("/tmp/chip8t1.ch8"));
        ASSERT_DEATH(chip8.executeInstructions(), "Assertion");
    }{
        Chip8 chip8;
        /* create a file with 1 opcode */
        system("echo 0xF333 | xxd -r -p -  > /tmp/chip8t1.ch8");
        EXPECT_EQ(true , chip8.loadRom("/tmp/chip8t1.ch8"));
        chip8.executeInstructions();
    }{
        Chip8 chip8;
        /* create a file with 1 opcode */
        system("echo 0xF355 | xxd -r -p -  > /tmp/chip8t1.ch8");
        EXPECT_EQ(true , chip8.loadRom("/tmp/chip8t1.ch8"));
        chip8.executeInstructions();
    }{
        Chip8 chip8;
        /* create a file with 1 opcode */
        system("echo 0xF365 | xxd -r -p -  > /tmp/chip8t1.ch8");
        EXPECT_EQ(true , chip8.loadRom("/tmp/chip8t1.ch8"));
        ASSERT_DEATH(chip8.executeInstructions(), "Assertion");
    }
}
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
