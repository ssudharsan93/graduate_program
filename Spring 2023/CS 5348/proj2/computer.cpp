#include "computer.h"

Memory* mem;
Shell* shell;
bool TERMINATE;

PCB::PCB() {
    this->process_init_PCB();
}

void PCB::process_init_PCB(){
  this->PID = 0;
  this->PCB_PC = BASE;
  this->PCB_AC = 0;
  this->PCB_Base = BASE;
  this->PCB_MAR = 0;
  this->PCB_MBR = 0;

} // Create a PCB for the user program and initialize it.

void PCB::process_set_registers(){

  PC = this->PCB_PC;
  IR0 = 0;
  IR1 = 0;
  MAR = this->PCB_MAR;
  MBR = this->PCB_MBR;
  AC = this->PCB_AC;

} // Copy the PCB context data to the registers

Memory* returnMemory() {
    return mem;
}

Shell* returnShell() {
    return shell;
}

void run_computer() {

    TERMINATE = 0;

    int mem_size;
    int time_quantum;
    int printing_time;
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
    time_quantum = atoi(param);
    param = strtok(NULL, delim);
    printing_time = atoi(param);

    config_file.close();

    cout << "Memory Size: " << mem_size << endl;
    cout << "Time Quantum: " << time_quantum << endl;
    cout << "Printing Time: " << printing_time << endl;

    mem = new Memory(mem_size);
    FILE* idle_prog_file = load_prog(idle_prog_name, 0);
    shell = new Shell();
    shell->shell_print_memory();

    //PCB *pcb_proc1 = new PCB();
    //pcb_proc1->process_set_registers();

    //CPU *cpu = new CPU();
    //cpu->cpu_operation();

    //load_finish(prog_file);

}

int main() {
    run_computer();
    return 0;
}
