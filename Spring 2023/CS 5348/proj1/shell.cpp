#include "computer.h"

Shell::Shell(){
    this->shell_init();
}

void Shell::shell_init(){
    return;
}            // Initialize the shell module

void Shell::shell_print_registers(){

    cout << endl;

    cout << "===========================" << endl;
    cout << "     Register Dump         " << endl;
    cout << "===========================" << endl;
    cout << "Register: Contents" << endl;
    cout << "BASE: " << BASE << endl;
    cout << "PC: " << PC << endl;
    cout << "IR0: " << IR0 << endl;
    cout << "IR1: " << IR1 << endl;
    cout << "AC: " << AC << endl;
    cout << "MAR: " << MAR << endl;
    cout << "MBR: " << MBR << endl;

    cout << endl;

} // Print out all the registers on the screen

void Shell::shell_print_memory(){

    Memory* mem = returnMemory();

    cout << endl;

    cout << "===========================" << endl;
    cout << "     Memory Dump: k = " << mem->size << "    " << endl;
    cout << "===========================" << endl;
    cout << "Address: Contents" << endl;

    int mem_size = mem->size;

    for ( int mem_addr_counter = 0; mem_addr_counter < mem_size; mem_addr_counter++ ){
        cout << mem_addr_counter << ": " << mem->Mem[mem_addr_counter] << endl;
    }

    cout << endl;
}    // Print out all the words in memory in integer form on the screen

void Shell::shell_command (int cmd){
    switch(cmd){

      case 2:
          this->shell_print_registers();
          break;
      case 3:
          this->shell_print_memory();
          break;
      default:
          break;

    }

    return;

} // For each shell command code, call the corresponding functions.
                                   // Input cmd is the command code.
