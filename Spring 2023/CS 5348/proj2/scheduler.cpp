#include "computer.h"

PCB::PCB() {
    this->PID = 0;
    this->PCB_PC = 0;
    this->PCB_AC = 0;
    this->PCB_Base = 0;
    this->PCB_MAR = 0;
    this->PCB_MBR = 0;
}

PCB::PCB(int base) {
    this->PID = 0;
    this->PCB_PC = base;
    this->PCB_AC = 0;
    this->PCB_Base = base;
    this->PCB_MAR = 0;
    this->PCB_MBR = 0;
}

void PCB::set_context(){
    PC = this->PCB_PC;
    MAR = this->PCB_MAR;
    MBR = this->PCB_MBR;
    AC = this->PCB_AC;
    BASE = this->PCB_Base;
} // Copy the PCB context data to the registers

void PCB::save_context(){
    this->PCB_PC = PC;
    this->PCB_MAR = MAR;
    this->PCB_MBR = MBR;
    this->PCB_AC = AC;
}// Copy the updated register context data back to the PCB

ReadyQueue::ReadyQueue(){ return; }
void ReadyQueue::enqueue(PCB* new_proc){ return; }
PCB* ReadyQueue::dequeue(){
    PCB* proc = this->ProcessQ.front();
    this->ProcessQ.pop();
    return proc; 
}


//Initialize a PCB data structure for PCBs of multiple processes.
void Scheduler::process_init_PCBs(){
    readyq = new ReadyQueue();
}

// Create a PCB entry for a submitted process.
void Scheduler::process_init_PCB(){
    return;
}

//Dispose a PCB entry for an exiting process.
void Scheduler::process_dispose_PCB(){
  return;
}

//Initialize a ready queue data structure.
void Scheduler::process_init_readyQ(){
  return;
}

//Insert the PCB of a newly submitted process into the ready queue.
void Scheduler::process_insert_readyQ(){
  return;
}

//Fetch a process to execute from ready queue based on the CPU scheduling algorithm. It returns the fetched PCB pointer.
PCB* Scheduler::process_fetch_readyQ(){
    PCB* fetched_proc = readyq->dequeue();
    return fetched_proc;
}

//Context switch two processes. Pass 2 PCBs as parameters. Need to consider the case of only switching one process in/out.
void Scheduler::process_context_switch(PCB *to_be_switched_out, PCB *to_be_run){
    return;
}

//Initialize the module by calling other init functions in the module, including process_init_PCBs and process_init_readyQ.
void Scheduler::process_init(){ return; }

//Handle process submission by calling other functions in the module,
//including process_init_PCB, process_insert_readyQ, and print_init_spool.
//(called by shell.c)
void Scheduler::process_submit(){ return; }

//Handle process execution by calling other functions, including process_fetch_readyQ and cpu_operation (in cpu.c).
//If cpu_operation returns as Exit, then call process_exit.
void Scheduler::process_execute(){
    PCB* proc_to_be_run = this->process_fetch_readyQ();

    return;
}

//Clean up for the exiting process, including calling dispose_PCB and print_end_spool, etc.
void Scheduler::process_exit(){ return; }
