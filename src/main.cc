#include "../inc/ichip8.h"
#include <cstdio>
#include<iostream>

using namespace std;

int main(int argc, char *argv[]) {
    if (argc != 2)  {
        cout << "pass rom as argument" << endl;
        return -1;
    }
    char *input_file = argv[1];
    Chip8 chip8;
    chip8.loadRom(input_file);
    chip8.executeInstructions();
    return 0;
}
