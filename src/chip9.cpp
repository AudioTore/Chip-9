#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

unsigned int memory[4096]; // 4096 kbs
unsigned int REG[10];
unsigned int REGVF;
unsigned int resolution = 64 * 32; // 2048
int I; // Pointer for Output memory address.

int pc;

/*
--------------
|	        |
|	        |
|   Output  | (Any graphics and such are printed here in the output)
|	        |  
|	        |
-------------- - 0x200 (512)
|	         |
|     ROM    | (Where rom contents are stored)
|	         |
-------------- - 0x0 (0)
*/

int disp_clear()
{
    for (int i = 0; i < resolution; i++) {
        cout << "" << endl;
    }
}

int loadrom() // Load instructions into Memory.
{
    int i = 0; // ROM Instruction pointer. (for loading instructions into memory addres 0x0)

    memory[i] = 0x00E; // CLEAR
    i += 2;
    memory[i] = 0x001; // MOV
    i += 2;
    memory[i] = 0x1; // REG1,
    i += 2;
    memory[i] = 1; // 1 (MOV REG1, 1)
    i += 2;
    memory[i] = 0x001; // MOV
    i += 2;
    memory[i] = 0x2; // REG2,
    i += 2;
    memory[i] = 2; // 2 (MOV REG2, 2)
    i += 2;
    memory[i] = 0x001; // MOV
    i += 2;
    memory[i] = 0x3; // REG3,
    i += 2;
    memory[i] = 3; // 3 (MOV REG3, 3)
    i += 2;
    // memory[i] = 0x005; // HLT
    memory[i] = 0x006; // PUSH
    i += 2;
    memory[i] = 0x1; // R1 (PUSH R1)
    i += 2;
    memory[i] = 0x006; // PUSH
    i += 2;
    memory[i] = 0x2; // R2 (PUSH R2)
    i += 2;
    memory[i] = 0x006; // PUSH
    i += 2;
    memory[i] = 0x3; // R3 (PUSH R3)
    i += 2;
    memory[i] = 0x002; // EXIT

    if (i >= 512) {
        cout << "Woah! Too many instructions! (Overflowing to 0x200)" << endl;
    }
}

int chip9init()
{
    // Clear our Registers.
    for (int i = 0; i < 10; i++) {
        REG[i] = 0;
    }

    REGVF = NULL;
    I = 512;
    pc = 0x0;
}

int emulatecycle()
{
    int registerw; // For 0x001.
    int opcode = memory[pc];

    switch (opcode)
    {
        case 0x00E:
            disp_clear();
            pc += 2;
            break;

        case 0x001:
            pc += 2;
            registerw = memory[pc];
            REG[registerw] = memory[pc += 2];
            pc += 2;
            break;

        case 0x003:
            for (;;)
            {
                // HANG.
            }
            break;

        case 0x006:
            memory[I] = memory[pc += 2];
            cout << memory[I] << endl;
            I++;
            pc += 2;
            break;

        case 0x005:
            cout << "HALTED!" << endl;
            for (;;)
            {
                // HANG.
            }
            break;

        case 0x002:
            exit(0);
            break;
    }
}

int main()
{
    chip9init();
    loadrom();

    for (;;)
    {
        emulatecycle();
    }

    return 0;
}