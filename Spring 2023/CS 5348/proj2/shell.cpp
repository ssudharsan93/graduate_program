#include "computer.h"

Shell::Shell(){
    this->shell_init();
}

void Shell::shell_init(){
    return;
}            // Initialize the shell module

void Shell::shell_terminate_system() {
    TERMINATE = 1;
    return;
}

void Shell::shell_submit_new_process(){

    scheduler = returnScheduler();
    loader = returnLoader();

    char prog_name_char;
    char *input_program_file = new char[80];
    int base;
    int prog_name_counter = 0;

    cout << "Input Program File and Base> ";

    while( cin.get(prog_name_char) && !isspace(prog_name_char) ) {
        input_program_file[prog_name_counter++] = prog_name_char;
    }

    cin >> base;

    scheduler->process_submit(base);
    //load_prog(input_program_file, base);


    return;

}

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

void Shell::shell_dump_process_information() {
    return;
}

void Shell::shell_dump_spools() {
    return;
}

void Shell::shell_command(){

    int cmd;

    while ( !TERMINATE ) {

        cout << "Shell Command> ";
        cin >> cmd;

        switch(cmd){

          case 0:
              this->shell_terminate_system();
              break;
          case 1:
              this->shell_submit_new_process();
              break;
          case 2:
              this->shell_print_registers();
              break;
          case 3:
              this->shell_print_memory();
              break;
          case 4:
              this->shell_dump_process_information();
              break;
          case 5:
              this->shell_dump_spools();
              break;
          default:
              break;

        }
    }

    return;

} // For each shell command code, call the corresponding functions.
 // Input cmd is the command code.

int shell_main() {
    return 0;
}
