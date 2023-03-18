#ifndef COMPUTER_H
#define COMPUTER_H

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <cstring>
#include <string>
#include <unistd.h>
#include <pthread.h>
#include <mutex>

#include "memory.h"
#include "cpu.h"
#include "load.h"
#include "shell.h"
#include "scheduler.h"
#include "print.h"

using namespace std;

extern Memory *mem;
extern Shell *shell;
extern CPU *cpu;
extern Loader *loader;
extern Scheduler *scheduler;
extern ReadyQueue *readyq;
extern PCB* idlepcb;

extern mutex mem_prot;
extern mutex queue_prot;
extern mutex pcb_struct_prot;
extern mutex print_dump_prot;

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