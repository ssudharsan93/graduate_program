#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <queue>
#include <unordered_map>

class PCB {
private:
  int PID;
  int proc_PC;
  int proc_AC;
  int proc_Base;
  int proc_MAR;
  int proc_MBR;

public:
    PCB();
    PCB(int PID, int base);
    void set_context();
    void save_context();
    int get_PID();
    void print_contents();
};

class ReadyQueue {
private:
    queue<PCB*> processQ;
public:
    void enqueue(PCB *new_proc);
    PCB* dequeue();
    int get_size();
};

class Scheduler {
private:
    unordered_map<int, PCB*> *pcb_structure1;
    PCB *current_proc;
public:
    Scheduler();
    ~Scheduler();
    void process_set_registers();
    void process_init_PCBs(); //Initialize a PCB data structure for PCBs of multiple processes.
    PCB* process_init_PCB(int base); // Create a PCB entry for a submitted process.
    void process_dispose_PCB(); //Dispose a PCB entry for an exiting process.
    void process_dump_PCB();
    void process_init_readyQ(); //Initialize a ready queue data structure.
    void process_insert_readyQ(PCB *new_proc); //Insert the PCB of a newly submitted process into the ready queue.
    PCB* process_fetch_readyQ(); //Fetch a process to execute from ready queue based on the CPU scheduling algorithm.
                                 //It returns the fetched PCB pointer.
    void process_dump_readyQ();
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
};

#endif SCHEDULER_H