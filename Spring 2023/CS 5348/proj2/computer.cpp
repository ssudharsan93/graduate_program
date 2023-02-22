#include "computer.h"

Memory* mem;
Shell* shell;

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

int main() {

    int mem_size;
    char input_data[80];

    ifstream input_file("config.sys");

    if ( !input_file.good() ) {
      cout << "Error: config.sys doesn't exist" << endl;
    }

    char digit;
    int mem_size_read_counter = 0;

    while ( input_file.get(digit) ){
        input_data[mem_size_read_counter] = digit;
        mem_size_read_counter++;
    }

    input_file.close();

    mem_size = atoi(input_data);

    char prog_name_char;
    char *input_program_file = new char[80];
    int base;
    int prog_name_counter = 0;

    cout << "Input Program File and Base> ";

    while( cin.get(prog_name_char) && !isspace(prog_name_char) ) {
        input_program_file[prog_name_counter++] = prog_name_char;
    }
    cin >> base;

    BASE = base;

    mem = new Memory(mem_size);
    FILE* prog_file = load_prog(input_program_file, base);
    PCB *pcb_proc1 = new PCB();
    pcb_proc1->process_set_registers();

    shell = new Shell();
    CPU *cpu = new CPU();
    cpu->cpu_operation();

    load_finish(prog_file);

}
