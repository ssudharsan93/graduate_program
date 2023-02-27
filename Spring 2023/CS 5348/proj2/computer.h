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
#include "scheduler.h"

using namespace std;

extern Memory *mem;
extern Shell *shell;
extern CPU *cpu;
extern Loader *loader;
extern Scheduler *scheduler;
extern ReadyQueue *readyq;
extern PCB* idlepcb;

extern bool TERMINATE;
extern int TQ;
extern int PT;
extern int PROC_SEEN_BY_COMPUTER;

Memory* returnMemory();
Shell* returnShell();
CPU* returnCPU();
Loader* returnLoader();
Scheduler* returnScheduler();
ReadyQueue* returnReadyQueue();

#endif COMPUTER_H