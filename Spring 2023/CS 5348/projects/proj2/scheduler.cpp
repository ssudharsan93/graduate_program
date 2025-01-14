#include "computer.h"

ReadyQueue *readyq;

PCB::PCB() {
    this->PID = 0;
    this->proc_PC = 0;
    this->proc_AC = 0;
    this->proc_Base = 0;
    this->proc_MAR = 0;
    this->proc_MBR = 0;
    this->proc_IR0 = 0;
    this->proc_IR1 = 0;
}

PCB::PCB(int PID, int base) {
    this->PID = PID;
    this->proc_PC = base;
    this->proc_AC = 0;
    this->proc_Base = base;
    this->proc_MAR = 0;
    this->proc_MBR = 0;
    this->proc_IR0 = 0;
    this->proc_IR1 = 0;
}

void PCB::set_context(){
    PC = this->proc_PC;
    MAR = this->proc_MAR;
    MBR = this->proc_MBR;
    AC = this->proc_AC;
    BASE = this->proc_Base;
    IR0 = this->proc_IR0;
    IR1 = this->proc_IR1;
} // Copy the PCB context data to the registers

void PCB::save_context(){
    this->proc_PC = PC;
    this->proc_MAR = MAR;
    this->proc_MBR = MBR;
    this->proc_AC = AC;
    this->proc_IR0 = IR0;
    this->proc_IR1 = IR1;
}// Copy the updated register context data back to the PCB

int PCB::get_PID(){ return this->PID; }
int PCB::get_PC(){ return this->proc_PC; }
int PCB::get_AC(){ return this->proc_AC; }
int PCB::get_Base(){ return this->proc_Base; }
int PCB::get_MAR(){ return this->proc_MAR; }
int PCB::get_MBR(){ return this->proc_MBR; }
int PCB::get_IR0(){ return this->proc_IR0; }
int PCB::get_IR1(){ return this->proc_IR1; }

void PCB::print_contents(){
    cout << endl;
    cout << "\tPID: " << this->PID << endl;
    cout << "\tPC: " << this->proc_PC << endl;
    cout << "\tBase: " << this->proc_Base << endl;
    cout << "\tAC: " << this->proc_AC << endl;
    cout << "\tMAR: " << this->proc_MAR << endl;
    cout << "\tMBR: " << this->proc_MBR << endl;
    cout << endl;
}

void ReadyQueue::enqueue(PCB *new_proc){ 
    this->processQ.push(new_proc);
}
PCB* ReadyQueue::dequeue(){

    PCB* proc = this->processQ.front();
    this->processQ.pop();
    return proc; 
}

int ReadyQueue::get_size(){
    return this->processQ.size();
}

Scheduler::Scheduler(){
    this->current_proc = NULL;
    this->pcb_structure = NULL;
}

Scheduler::~Scheduler(){
    delete this->current_proc;
    delete this->pcb_structure;
}

PCB* Scheduler::get_current_proc() {
    return this->current_proc;
}

//Initialize a PCB data structure for PCBs of multiple processes.
void Scheduler::process_init_PCBs(){
    this->pcb_structure = new map<int, PCB*>();
}

// Create a PCB entry for a submitted process.
PCB* Scheduler::process_init_PCB(int base){

    if ( base == 0 ){    
        idlepcb = new PCB(1, 0);

        pair<int, PCB*> idle_pid_proc_pair = make_pair(1, idlepcb);
        this->pcb_structure->insert(idle_pid_proc_pair);

        return idlepcb;
    
    }

    PROC_SEEN_BY_COMPUTER = PROC_SEEN_BY_COMPUTER + 1;

    PCB* new_proc = new PCB(PROC_SEEN_BY_COMPUTER, base);
    
    auto pcb_struct_it = this->pcb_structure->find(PROC_SEEN_BY_COMPUTER);
    
    if ( pcb_struct_it == this->pcb_structure->end() ) {
        pair<int, PCB*> pid_proc_pair = make_pair(PROC_SEEN_BY_COMPUTER, new_proc);
        this->pcb_structure->insert(pid_proc_pair);
    }
    
    return new_proc;
}

//Dispose a PCB entry for an exiting process.
void Scheduler::process_dispose_PCB(){
    
    this->pcb_structure->erase(this->current_proc->get_PID());
    this->process_dump_PCB();

    delete this->current_proc;
    this->current_proc = NULL;
    
    return;

}

void Scheduler::process_dump_PCB(){

    auto pcb_struct_begin_it = this->pcb_structure->begin();
    auto pcb_struct_end_it = this->pcb_structure->end();
    PCB* curr_proc;

    string header = "pid";
    string footer = "_spool.txt";
    string fname;

    string process_id, process_Base, process_PC, process_IR0;
    string process_IR1, process_AC, process_MAR, process_MBR;

    cout << "===========================" << endl;
    cout << "       PCB Dump            " << endl;
    cout << "===========================" << endl;
    cout << "Index: [ Filename:XXXXX, PID:#, BASE:#, PC:#, IR0:#, IR1:#, AC:#, MAR:#, MBR:# ]" << endl;

    for ( auto pcb_struct_it = pcb_struct_begin_it; pcb_struct_it != pcb_struct_end_it; ++pcb_struct_it ) {
        
        curr_proc = pcb_struct_it->second;

        if ( curr_proc->get_PID() == 1 ) { continue; }

        process_id = to_string(curr_proc->get_PID());
        process_Base = to_string(curr_proc->get_Base());
        process_PC = to_string(curr_proc->get_PC());
        process_IR0 = to_string(curr_proc->get_IR0());
        process_IR1 = to_string(curr_proc->get_IR1());
        process_AC = to_string(curr_proc->get_AC());
        process_MAR = to_string(curr_proc->get_MAR());
        process_MBR = to_string(curr_proc->get_MBR());

        fname = header + process_id + footer;

        cout << "Index: [ Filename:" << fname <<", PID:" << process_id << ", BASE:" << process_Base;
        cout << ", PC:" << process_PC << ", IR0:" << process_IR0 << ", IR1:" << process_IR1;
        cout << ", AC:" << process_AC << ", MAR:" << process_MAR << ", MBR:" << process_MBR << " ]" << endl;

    }
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

void Scheduler::process_dump_readyQ() {
    
    readyq = returnReadyQueue();

    int q_size = readyq->get_size();

    cout << "===========================" << endl;
    cout << "      ReadyQ Dump          " << endl;
    cout << "===========================" << endl;
    cout << "Index: Process ID" << endl;
    
    for ( int q_cntr = 0; q_cntr < q_size; q_cntr++ ){
        PCB* proc = readyq->dequeue();
        cout << q_cntr << ": " << proc->get_PID() << endl;
        readyq->enqueue(proc);
    }

    return;
}

//Context switch two processes. Pass 2 PCBs as parameters. Need to consider the case of only switching one process in/out.
void Scheduler::process_context_switch(PCB *proc_to_be_switched_out, PCB *proc_to_be_run){
    
    if ( proc_to_be_switched_out == NULL ) {
        proc_to_be_run->set_context();
    } 
    
    else {
        proc_to_be_switched_out->save_context();
        proc_to_be_run->set_context();
    }
    
    return;
}

//Initialize the module by calling other init functions in the module, including process_init_PCBs and process_init_readyQ.
void Scheduler::process_init(){ 
    this->process_init_PCBs();
    this->process_init_readyQ();

    int pcb_struct_cntr;
    return;
}

//Handle process submission by calling other functions in the module,
//including process_init_PCB, process_insert_readyQ, and print_init_spool.
//(called by shell.c)
void Scheduler::process_submit(int base){
    
    PCB* new_proc;
    
    new_proc = process_init_PCB(base);

    if ( base != 0 ){
        print_init_spool(new_proc->get_PID());
        this->process_insert_readyQ(new_proc);
        this->process_dump_readyQ();
    }

}

//Handle process execution by calling other functions, including process_fetch_readyQ and cpu_operation (in cpu.c).
//If cpu_operation returns as Exit, then call process_exit.
void Scheduler::process_execute(){
    
    cpu = returnCPU();

    if ( readyq->get_size() == 0 ) {
        
        this->process_context_switch(this->current_proc, idlepcb);
        this->current_proc = idlepcb;

    } else { 
        
        PCB *proc_to_be_run = this->process_fetch_readyQ();
        PCB *current_proc = this->current_proc;
        this->process_context_switch(current_proc, proc_to_be_run);

        this->current_proc = proc_to_be_run;

        cout << "Scheduler: Now Running Process PID: " << this->current_proc->get_PID();
        cout << " PC: " << this->current_proc->get_PC() << endl;

    }

    int return_code = cpu->cpu_operation();
    
    if ( return_code == 0 ) {

        cout << "Process PID: " << this->current_proc->get_PID() << " exiting..." << endl;
        this->process_exit();
        this->process_dump_readyQ();

    } else {
    
        if ( this->current_proc != idlepcb ){
        
            this->process_insert_readyQ(this->current_proc);
            cout << "Scheduler: Was Running Process PID: " << this->current_proc->get_PID();
            cout << " PC: " << PC << endl;
        
        }
    
    }

}

//Clean up for the exiting process, including calling dispose_PCB and print_end_spool, etc.
void Scheduler::process_exit(){
    print_end_spool(this->current_proc->get_PID());
    this->process_dispose_PCB();
    return; 
}
