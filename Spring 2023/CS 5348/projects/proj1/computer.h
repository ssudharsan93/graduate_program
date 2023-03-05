#ifndef COMPUTER_H
#define COMPUTER_H

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <cstring>
#include <unistd.h>

#include "memory.h"
#include "cpu.h"
#include "load.h"
#include "shell.h"

using namespace std;

extern Memory *mem;
extern Shell *shell;

Memory* returnMemory();
Shell* returnShell();

class PCB {

public:
    PCB();
    int PID;
    int PCB_PC;
    int PCB_AC;
    int PCB_Base;
    int PCB_MAR;
    int PCB_MBR;

    void process_init_PCB();
    void process_set_registers();

};

#endif COMPUTER_H
