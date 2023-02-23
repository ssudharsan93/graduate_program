#ifndef COMPUTER_H
#define COMPUTER_H

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <cstring>
#include <unistd.h>
#include <queue>

#include "memory.h"
#include "cpu.h"
#include "load.h"
#include "shell.h"
#include "scheduler.h"

using namespace std;

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

extern Memory *mem;
extern Shell *shell;
extern bool TERMINATE;
extern queue<PCB*> ReadyQueue;

Memory* returnMemory();
Shell* returnShell();

#endif COMPUTER_H
