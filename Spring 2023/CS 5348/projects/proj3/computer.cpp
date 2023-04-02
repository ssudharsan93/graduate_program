#include "computer.h"

Memory* mem;
Shell* shell;
CPU *cpu;
Loader *loader;
Scheduler *scheduler;
PCB* idlepcb;

mutex mem_queue_dump_mutex;
mutex mem_prot;
mutex queue_prot;
mutex pcb_struct_prot;

int TQ;

string COMPUTER_ID;
string PRINTER_IP_ADDRESS;
string PRINTER_PORT_NUMBER;

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

    TERMINATE = false;
    PROC_SEEN_BY_COMPUTER = 1;

    pthread_t shell_thread;

    int mem_size;
    char delim[] = " ,";
    char idle_prog_name[] = "prog-idle";
    char *printer_ip_address;
    char *printer_port_number;

    char config_data[255];

    ifstream config_file("config.sys");

    if ( !config_file.good() ) {
      cout << "Error: config.sys doesn't exist" << endl;
    }

    config_file.getline(config_data, 255);
    char *config_arg = strtok(config_data, delim);
    printer_ip_address = config_arg;
    config_arg = strtok(NULL, delim);
    printer_port_number = config_arg;
    config_arg = strtok(NULL, delim);
    mem_size = atoi(config_arg);
    config_arg = strtok(NULL, delim);
    TQ = atoi(config_arg);

    config_file.close();

    cout << "Printer Ip Address: " << printer_ip_address << endl;
    cout << "Printer Port Number: " << printer_port_number << endl;
    cout << "Memory Size: " << mem_size << endl;
    cout << "Time Quantum: " << TQ << endl;

    PRINTER_IP_ADDRESS = string(printer_ip_address);
    PRINTER_PORT_NUMBER = string(printer_port_number);

    mem = new Memory(mem_size);
    loader = new Loader();
    shell = new Shell();
    scheduler = new Scheduler();
    scheduler->process_init();
    
    FILE* idle_prog_file = loader->load_prog(idle_prog_name, 0);
    loader->load_finish(idle_prog_file);
    scheduler->process_submit(0);

    print_init();

    pthread_create(&shell_thread, NULL, shell_main, (void*) shell);

    while( !TERMINATE ) {
        usleep(10000);
	    scheduler->process_execute();
    }

    pthread_join(shell_thread, NULL);

    print_terminate();
    
    delete scheduler;

    cout << "Exiting Entire System" << endl;


}

int main(int argc, char *argv[]) {
    
    if ( argc < 2 || ( string(argv[1]).length() == 0 ) ) {
        cout << "No Computer ID or irregular Computer ID provided" << endl;
        exit(1);
    }

    COMPUTER_ID = string(argv[1]);
    cout << "COMPUTER_ID is... " << COMPUTER_ID << endl;

    run_computer();
    return 0;
}
