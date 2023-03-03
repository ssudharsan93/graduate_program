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
int PROC_SEEN_BY_COMPUTER;

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
    PROC_SEEN_BY_COMPUTER = 1;

    pthread_t shell_thread;

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
    shell = new Shell();
    scheduler = new Scheduler();
    scheduler->process_init();
    
    FILE* idle_prog_file = loader->load_prog(idle_prog_name, 0);
    loader->load_finish(idle_prog_file);
    scheduler->process_submit(0);

    //test_print_component();
    print_init(PT);

    pthread_create(&shell_thread, NULL, shell_main, (void*) shell);

    while( !TERMINATE ) {
        usleep(500);
        scheduler->process_execute();
    }

    pthread_join(shell_thread, NULL);

    print_terminate();
    
    delete scheduler;

    cout << "Exiting Entire System" << endl;


}

int main() {
    run_computer();
    return 0;
}
