#include "computer.h"

ReadyQueue *readyq;

PCB::PCB() {
    this->PID = 0;
    this->PCB_PC = 0;
    this->PCB_AC = 0;
    this->PCB_Base = 0;
    this->PCB_MAR = 0;
    this->PCB_MBR = 0;
}

PCB::PCB(int PID, int base) {
    this->PID = PID;
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

int PCB::get_PID(){ return this->PID; }

void ReadyQueue::enqueue(PCB *new_proc){ 
    this->ProcessQ.push(new_proc);
}
PCB* ReadyQueue::dequeue(){

    PCB* proc = this->ProcessQ.front();
    this->ProcessQ.pop();
    return proc; 
}

int ReadyQueue::get_size(){
    return this->ProcessQ.size();
}

//Initialize a PCB data structure for PCBs of multiple processes.
void Scheduler::process_init_PCBs(){
    pcb_structure = new PCB*[100];
}

// Create a PCB entry for a submitted process.
PCB* Scheduler::process_init_PCB(int PID, int base){

    PCB* new_proc = new PCB(PID, base);
    return new_proc;
}

//Dispose a PCB entry for an exiting process.
void Scheduler::process_dispose_PCB(){
    
    this->pcb_structure[this->current_proc->get_PID()] = NULL;
    PCB* proc_to_be_deleted = this->current_proc;
    delete proc_to_be_deleted;
    this->current_proc = NULL;
    
    return;

}

//Initialize a ready queue data structure.
void Scheduler::process_init_readyQ(){
    readyq = new ReadyQueue();
}

//Insert the PCB of a newly submitted process into the ready queue.
void Scheduler::process_insert_readyQ(PCB *new_proc){
    readyq->enqueue(new_proc);
}

//Fetch a process to execute from ready queue based on the CPU scheduling algorithm. It returns the fetched PCB pointer.
PCB* Scheduler::process_fetch_readyQ(){
    PCB* fetched_proc = readyq->dequeue();
    return fetched_proc;
}

//Context switch two processes. Pass 2 PCBs as parameters. Need to consider the case of only switching one process in/out.
void Scheduler::process_context_switch(PCB *proc_to_be_switched_out, PCB *proc_to_be_run){
    
    if (proc_to_be_switched_out == NULL) {
        proc_to_be_run->set_context();
    } 
    
    else {
        proc_to_be_switched_out->save_context();
        proc_to_be_run->set_context();
        this->process_insert_readyQ(proc_to_be_switched_out);
    }
    
    return;
}

//Initialize the module by calling other init functions in the module, including process_init_PCBs and process_init_readyQ.
void Scheduler::process_init(){ 
    this->process_init_PCBs();
    this->process_init_readyQ();
    return;
}

//Handle process submission by calling other functions in the module,
//including process_init_PCB, process_insert_readyQ, and print_init_spool.
//(called by shell.c)
void Scheduler::process_submit(int base){ 
    
    PCB* new_proc;
    
    for ( int pcb_struct_cntr = 0; pcb_struct_cntr < this->size_pcb_structure; pcb_struct_cntr++ ){
        if ( pcb_structure[pcb_struct_cntr] != NULL ){
            new_proc = process_init_PCB(pcb_struct_cntr, base);
        }
    }

    process_insert_readyQ(new_proc);
}

//Handle process execution by calling other functions, including process_fetch_readyQ and cpu_operation (in cpu.c).
//If cpu_operation returns as Exit, then call process_exit.
void Scheduler::process_execute(){
    PCB* proc_to_be_run = this->process_fetch_readyQ();
    this->process_context_switch(this->current_proc, proc_to_be_run);
    cpu = returnCPU();
    int return_code = cpu->cpu_operation();

    if ( return_code == 0 ) { this->process_exit(); }
    else {  this->process_fetch_readyQ(); }
}

//Clean up for the exiting process, including calling dispose_PCB and print_end_spool, etc.
void Scheduler::process_exit(){
    this->process_dispose_PCB();
    return; 
}

int Scheduler::get_num_processes(){ return this->num_processes; }
