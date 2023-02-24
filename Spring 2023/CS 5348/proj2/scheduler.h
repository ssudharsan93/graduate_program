#ifndef SCHEDULER_H
#define SCHEDULER_H

class PCB {
private:
  int PID;
  int PCB_PC;
  int PCB_AC;
  int PCB_Base;
  int PCB_MAR;
  int PCB_MBR;

public:
    PCB();
    PCB(int PID, int base);
    void set_context();
    void save_context();
    int get_PID();
};

class ReadyQueue {
private:
    queue<PCB*> ProcessQ;
public:
    void enqueue(PCB *new_proc);
    PCB* dequeue();
    int get_size();
};

class Scheduler {
private:
    PCB **pcb_structure = NULL;
    PCB *current_proc = NULL;
    int size_pcb_structure = 100;
    int num_processes = 1;
public:
    void process_set_registers();
    void process_init_PCBs(); //Initialize a PCB data structure for PCBs of multiple processes.
    PCB* process_init_PCB(int PID, int base); // Create a PCB entry for a submitted process.
    void process_dispose_PCB(); //Dispose a PCB entry for an exiting process.
    void process_init_readyQ(); //Initialize a ready queue data structure.
    void process_insert_readyQ(PCB *new_proc); //Insert the PCB of a newly submitted process into the ready queue.
    PCB* process_fetch_readyQ(); //Fetch a process to execute from ready queue based on the CPU scheduling algorithm.
                                 //It returns the fetched PCB pointer.
    void process_context_switch(PCB *proc_to_be_switched_out, PCB *proc_to_be_run);
                                  //Context switch two processes. Pass 2 PCBs as parameters.
                                   //Need to consider the case of only switching one process in/out.
    void process_init();  //Initialize the module by calling other init functions in the module,
                          //including process_init_PCBs and process_init_readyQ.
    void process_submit(int base);//Handle process submission by calling other functions in the module,
                          //including process_init_PCB, process_insert_readyQ, and print_init_spool.
                          //(called by shell.c)
    void process_execute(); //Handle process execution by calling other functions,
                            //including process_fetch_readyQ and cpu_operation (in cpu.c).
                            //If cpu_operation returns as Exit, then call process_exit.
    void process_exit(); //Clean up for the exiting process,
                         //including calling dispose_PCB and print_end_spool, etc.
    int get_num_processes();
};

#endif SCHEDULER_H