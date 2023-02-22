#ifndef SCHEDULER_H
#define SCHEDULER_H

class Scheduler {
    process_init_PCBs(...);
    // Create a PCB entry for a submitted process.
    process_init_PCB(...);
    //Dispose a PCB entry for an exiting process.
    process_dispose_PCB(...);
    //Initialize a ready queue data structure.
    process_init_readyQ(...);
    //Insert the PCB of a newly submitted process into the ready queue.
    process_insert_readyQ(...);
    //Fetch a process to execute from ready queue based on the CPU scheduling algorithm. It returns the fetched PCB pointer.
    process_fetch_readyQ(...);
    //Context switch two processes. Pass 2 PCBs as parameters. Need to consider the case of only switching one process in/out.
    process_context_switch(...);
    //Initialize the module by calling other init functions in the module, including process_init_PCBs and process_init_readyQ.
    process_init(...);
    //Handle process submission by calling other functions in the module,
    //including process_init_PCB, process_insert_readyQ, and print_init_spool.
    //(called by shell.c)
    process_submit(...);
    //Fetch a process to execute from ready queue based on the CPU scheduling algorithm. It returns the fetched PCB pointer.
    process_fetch_readyQ(...);
    //Handle process execution by calling other functions, including process_fetch_readyQ and cpu_operation (in cpu.c).
    //If cpu_operation returns as Exit, then call process_exit.
    process_execute(...);
    //Clean up for the exiting process, including calling dispose_PCB and print_end_spool, etc.
    process_exit(...);
}

#endif SCHEDULER_H
