#include "computer.h"

ReadyQueue *readyq;

PCB::PCB() {
    this->PID = 0;
    this->proc_PC = 0;
    this->proc_AC = 0;
    this->proc_Base = 0;
    this->proc_MAR = 0;
    this->proc_MBR = 0;
}

PCB::PCB(int PID, int base) {
    this->PID = PID;
    this->proc_PC = base;
    this->proc_AC = 0;
    this->proc_Base = base;
    this->proc_MAR = 0;
    this->proc_MBR = 0;
}

void PCB::set_context(){
    PC = this->proc_PC;
    MAR = this->proc_MAR;
    MBR = this->proc_MBR;
    AC = this->proc_AC;
    BASE = this->proc_Base;
} // Copy the PCB context data to the registers

void PCB::save_context(){
    this->proc_PC = PC;
    this->proc_MAR = MAR;
    this->proc_MBR = MBR;
    this->proc_AC = AC;
}// Copy the updated register context data back to the PCB

int PCB::get_PID(){ return this->PID; }

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
    this->pcb_structure1 = NULL;
}

Scheduler::~Scheduler(){
    delete this->current_proc;
    delete this->pcb_structure1;
}

//Initialize a PCB data structure for PCBs of multiple processes.
void Scheduler::process_init_PCBs(){
    this->pcb_structure1 = new unordered_map<int, PCB*>();
}

// Create a PCB entry for a submitted process.
PCB* Scheduler::process_init_PCB(int base){

    if ( base == 0 ){    
        idlepcb = new PCB(1, 0);

        pair<int, PCB*> idle_pid_proc_pair = make_pair(1, idlepcb);
        this->pcb_structure1->insert(idle_pid_proc_pair);

        return idlepcb;
    
    }

    PROC_SEEN_BY_COMPUTER = PROC_SEEN_BY_COMPUTER + 1;

    cout << "PID will be " << PROC_SEEN_BY_COMPUTER << endl;

    PCB* new_proc = new PCB(PROC_SEEN_BY_COMPUTER, base);
    
    auto pcb_struct_it = this->pcb_structure1->find(PROC_SEEN_BY_COMPUTER);
    
    if ( pcb_struct_it == this->pcb_structure1->end() ) {
        pair<int, PCB*> pid_proc_pair = make_pair(PROC_SEEN_BY_COMPUTER, new_proc);
        this->pcb_structure1->insert(pid_proc_pair);
    }
    
    return new_proc;
}

//Dispose a PCB entry for an exiting process.
void Scheduler::process_dispose_PCB(){
    
    this->pcb_structure1->erase(this->current_proc->get_PID());
    this->process_dump_PCB();
    PCB* proc_to_be_deleted = this->current_proc;
    delete proc_to_be_deleted;
    this->current_proc = NULL;
    
    return;

}

void Scheduler::process_dump_PCB(){

    auto pcb_struct_begin_it = this->pcb_structure1->begin();
    auto pcb_struct_end_it = this->pcb_structure1->end();
    PCB* curr_proc;

    for ( auto pcb_struct_it = pcb_struct_begin_it; pcb_struct_it != pcb_struct_end_it; ++pcb_struct_it ) {
        
        curr_proc = pcb_struct_it->second;

        cout << "\t--------------------------------------" << endl;
        cout << "\t               Process                " << endl;
        cout << "\t--------------------------------------" << endl;

        curr_proc->print_contents();

        cout << "\t--------------------------------------" << endl;

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
    
    for ( int q_cntr = 0; q_cntr < q_size; q_cntr++ ){
    
        PCB* proc = readyq->dequeue();
        cout << "\tProcess "<< q_cntr << ":\tPID = " << proc->get_PID() << endl;
        readyq->enqueue(proc);

    }

    return;
}

//Context switch two processes. Pass 2 PCBs as parameters. Need to consider the case of only switching one process in/out.
void Scheduler::process_context_switch(PCB *proc_to_be_switched_out, PCB *proc_to_be_run){
    
    if (proc_to_be_switched_out == NULL) {
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
        this->process_insert_readyQ(new_proc);
    }

}

//Handle process execution by calling other functions, including process_fetch_readyQ and cpu_operation (in cpu.c).
//If cpu_operation returns as Exit, then call process_exit.
void Scheduler::process_execute(){
    
    cpu = returnCPU();
    shell = returnShell();

    while( !TERMINATE ) {

        int idle_loop = 0;        
        while ( readyq->get_size() == 0 ) {

            if ( this->current_proc == idlepcb ) {
                idle_loop++;
            }
            
            if ( this->current_proc == NULL) {
                this->process_context_switch(this->current_proc, idlepcb);
                this->current_proc = idlepcb;
            }

        }

        if ( TERMINATE ) { continue; }

        PCB* proc_to_be_run = this->process_fetch_readyQ();
        PCB* current_proc = this->current_proc;
        this->process_context_switch(current_proc, proc_to_be_run);
        
        if ( current_proc != NULL  && current_proc != idlepcb ){
            this->process_insert_readyQ(this->current_proc);
        }

        this->current_proc = proc_to_be_run;
        
        cout << "Scheduler: Now Running: " << proc_to_be_run->get_PID() << endl;
        
        int return_code = cpu->cpu_operation();

        cout << "Return code: " << return_code << endl;
        cout << endl;

        if ( return_code == 0 ) {
            cout << "Process PID: " << this->current_proc->get_PID() << " exiting..." << endl;
            shell->shell_dump_readyq_information();
            this->process_exit();
        }
        else { continue; }
    }

}

//Clean up for the exiting process, including calling dispose_PCB and print_end_spool, etc.
void Scheduler::process_exit(){
    this->process_dispose_PCB();
    return; 
}
