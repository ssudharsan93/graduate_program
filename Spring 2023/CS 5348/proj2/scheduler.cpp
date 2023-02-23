#include "computer.h"

//Initialize a PCB data structure for PCBs of multiple processes.
void Scheduler::process_init_PCBs(){ return; }

// Create a PCB entry for a submitted process.
void Scheduler::process_init_PCB(){ return; }

//Dispose a PCB entry for an exiting process.
void Scheduler::process_dispose_PCB(){ return; }

//Initialize a ready queue data structure.
void Scheduler::process_init_readyQ(){ return; }

//Insert the PCB of a newly submitted process into the ready queue.
void Scheduler::process_insert_readyQ(){ return; }

//Fetch a process to execute from ready queue based on the CPU scheduling algorithm. It returns the fetched PCB pointer.
void Scheduler::process_fetch_readyQ(){ return; }

//Context switch two processes. Pass 2 PCBs as parameters. Need to consider the case of only switching one process in/out.
void Scheduler::process_context_switch(){ return; }

//Initialize the module by calling other init functions in the module, including process_init_PCBs and process_init_readyQ.
void Scheduler::process_init(){ return; }

//Handle process submission by calling other functions in the module,
//including process_init_PCB, process_insert_readyQ, and print_init_spool.
//(called by shell.c)
void Scheduler::process_submit(){ return; }

//Handle process execution by calling other functions, including process_fetch_readyQ and cpu_operation (in cpu.c).
//If cpu_operation returns as Exit, then call process_exit.
void Scheduler::process_execute(){ return; }

//Clean up for the exiting process, including calling dispose_PCB and print_end_spool, etc.
void Scheduler::process_exit(){ return; }
