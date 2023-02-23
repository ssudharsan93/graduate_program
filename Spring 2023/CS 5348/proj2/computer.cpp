#include "computer.h"

Memory* mem;
Shell* shell;
CPU *cpu;
Scheduler *scheduler;
ReadyQueue *readyq;
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
    char *param = strtok(config_data, delim);
    mem_size = atoi(param);
    param = strtok(NULL, delim);
    TQ = atoi(param);
    param = strtok(NULL, delim);
    PT = atoi(param);

    config_file.close();

    cout << "Memory Size: " << mem_size << endl;
    cout << "Time Quantum: " << TQ << endl;
    cout << "Printing Time: " << PT << endl;

    mem = new Memory(mem_size);
    FILE* idle_prog_file = load_prog(idle_prog_name, 0);
    idlepcb = new PCB();
    shell = new Shell();
    shell->shell_print_memory();

    //CPU *cpu = new CPU();
    //cpu->cpu_operation();

    //load_finish(prog_file);

}

int main() {
    run_computer();
    return 0;
}
