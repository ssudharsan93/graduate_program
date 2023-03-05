#include "computer.h"

Shell::Shell(){
    this->shell_init();
}

void Shell::shell_init(){
    return;
}            // Initialize the shell module

void Shell::shell_terminate_system() {
    TERMINATE = true;
    return;
}

void Shell::shell_submit_new_process(){

    scheduler = returnScheduler();
    loader = returnLoader();

    char delim[] = " ";
    char prog_name_char;
    char *program_info = new char[80];
    char *input_program_file = new char[80];
    int base;
    int prog_name_counter = 0;

    cout << "Input Program File and Base> ";
    cout.flush();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.getline(program_info, 80);

    char *prog_arg = strtok(program_info, delim);
    input_program_file = prog_arg;
    prog_arg = strtok(NULL, delim);
    base = atoi(prog_arg);
    
    cout << "Program file name: " << input_program_file << endl;
    cout << "Base: "  << base << endl;

    FILE *prog_file = loader->load_prog(input_program_file, base);
    loader->load_finish(prog_file);
    scheduler->process_submit(base);
    
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

void Shell::shell_dump_readyq_information() {

    scheduler = returnScheduler();

    cout << endl;
    cout << "=======================================" << endl;
    cout << "            Ready Queue Dump : " << endl;
    cout << "=======================================" << endl;

    scheduler->process_dump_readyQ();

    cout << endl;
    cout << "=======================================" << endl;
    cout << endl;

    return;

}

void Shell::shell_dump_process_information() {
    
    scheduler = returnScheduler();

    cout << endl;
    cout << "=======================================" << endl;
    cout << "   PCB Structure (Processes) Dump : " << endl;
    cout << "=======================================" << endl;

    scheduler->process_dump_PCB();

    cout << endl;
    cout << "=======================================" << endl;
    cout << endl;

    return;
}

void Shell::shell_dump_spool_information() {
    print_dump_spool();
    return;
}

void Shell::shell_command(){

    int cmd = -1;
    char input;

    while ( !TERMINATE ) {
        cout << "Shell Command> ";
        cin.get(input);

        if ( !isdigit(input) || input == '\n' ) {
            cout << endl;
            continue;
        }
        
        else {
            cmd = ( (int) input ) - ( (int) '0' );
        }

        switch(cmd){
            case 0:
s                this->shell_terminate_system();
                continue;
            case 1:
                this->shell_submit_new_process();
                continue;
            case 2:
                this->shell_print_registers();
                continue;
            case 3:
                this->shell_print_memory();
                continue;
            case 4:
                this->shell_dump_readyq_information();
                continue;
            case 5:
                this->shell_dump_process_information();
                continue;
            case 6:
                this->shell_dump_spool_information();
                continue;
            default:
                continue;
        }
    }

    return;

} // For each shell command code, call the corresponding functions.
 // Input cmd is the command code.

void *shell_main(void *arg) {
    Shell *shell = (Shell*) arg;
    shell->shell_command();
}
