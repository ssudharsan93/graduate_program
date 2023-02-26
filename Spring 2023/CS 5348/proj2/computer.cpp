#include "computer.h"

Memory* mem;
Shell* shell;
CPU *cpu;
Loader *loader;
Scheduler *scheduler;
PCB* idlepcb;


int TQ;
int PT;

bool TERMINATE;

Memory* returnMemory() {
    return mem;
}

Shell* returnShell() {
    return shell;
}

CPU* returnCPU(){
    return cpu;
}

Loader* returnLoader(){
    return loader;
}

Scheduler* returnScheduler(){
    return scheduler;
}

ReadyQueue* returnReadyQueue(){
    return readyq;
}

void run_computer() {

    TERMINATE = 0;

    int mem_size;
    char delim[] = " ,";
    char idle_prog_name[] = "prog_idle";

    char config_data[80];

    ifstream config_file("config.sys");

    if ( !config_file.good() ) {
      cout << "Error: config.sys doesn't exist" << endl;
    }

    char digit;
    int mem_size_read_counter = 0;

    config_file.getline(config_data, 80);
    char *config_arg = strtok(config_data, delim);
    mem_size = atoi(config_arg);
    config_arg = strtok(NULL, delim);
    TQ = atoi(config_arg);
    config_arg = strtok(NULL, delim);
    PT = atoi(config_arg);

    config_file.close();

    cout << "Memory Size: " << mem_size << endl;
    cout << "Time Quantum: " << TQ << endl;
    cout << "Printing Time: " << PT << endl;

    mem = new Memory(mem_size);
    loader = new Loader();
    FILE* idle_prog_file = loader->load_prog(idle_prog_name, 0);
    idlepcb = new PCB( 1, 0 );
    loader->load_finish(idle_prog_file);
    
    shell = new Shell();
    scheduler = new Scheduler();
    scheduler->process_init();
    //shell->shell_print_memory();

    shell->shell_command();
    shell->shell_command();
    shell->shell_command();

    //shell->shell_print_memory();

    scheduler->process_execute();

    delete scheduler;

    cout << "Exiting Entire System" << endl;



}

int main() {
    run_computer();
    return 0;
}
