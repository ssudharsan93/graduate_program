#include "computer.h"

int PC;
int IR0;
int IR1;
int MAR;
int MBR;
int AC;
int BASE;

void CPU::cpu_fetch_instruction(){

    mem = returnMemory();
    MAR = PC;
    mem->mem_read();
    IR0 = MBR;
    PC = PC + 1;
    MAR = PC;
    mem->mem_read();
    IR1 = MBR;
    PC = PC + 1;
    return;

}    // Read the 2 instruction words from memory, the addresses are computed from PC

bool CPU::cpu_execute_instruction(){

    switch ( IR0 ) {
        case 1: //1 (load) constant Load the constant to AC
            AC = IR1;
            break;

        case 2: //2 (load) m-addr load Mem[m-addr] into AC
            MAR = this->cpu_mem_address(IR1);
            mem = returnMemory();
            mem->mem_read();
            AC = MBR;
            break;

        case 3: //3 (add) m-addr load Mem[m-addr] into MBR, add MBR to AC
            MAR = this->cpu_mem_address(IR1);
            mem = returnMemory();
            mem->mem_read();
            AC = MBR + AC;
            break;

        case 4: //4 (mul) m-addr Same as above, except that add becomes multiply
            MAR = this->cpu_mem_address(IR1);
            mem = returnMemory();
            mem->mem_read();
            AC = MBR * AC;
            break;

        case 5: //5 (store) m-addr Store AC to Mem[m-addr]
            MAR = this->cpu_mem_address(IR1);
            mem = returnMemory();
            MBR = AC;
            mem->mem_write();
            break;

        case 6: //6 (ifgo) m-addr If AC > 0 then go to the address given in Mem[m-addr]
            MAR = this->cpu_mem_address(IR1);
            mem = returnMemory();
            mem->mem_read();
            if ( AC > 0 ) { PC = MAR; }
            break;

        case 7: //7 (print) Null Print the value in AC
            cout << "AC: " << AC << endl;
            break;

        case 8: //8 (sleep) Time Sleep for the given “time” in microseconds, which is the operand
            usleep(IR1);
	          break;

        case 9: //9 (shell) Code Execute the shell command according to code (elaborated later)
            shell = returnShell();
            shell->shell_command(IR1);
            break;

        case 0: //0 (exit) Null End of the current program, null is 0 and is unused
            return false;

        default: //Otherwise, continue to the next instruction
            return true;
    }

    return true;
} // For each instruction code, perform the simulated hardware operations


int CPU::cpu_mem_address(int m_addr){
    return m_addr + BASE;
} // Compute the memory address to be accessed and put it in MAR.
                                      // The input is the PC or the operand (m-addr) of an instruction.
void CPU::cpu_operation(){
    bool executing = true;

    while (executing) {
        this->cpu_fetch_instruction();
        executing = this->cpu_execute_instruction();
    }
}            // Loop for executing instructions, starting from 0 till the exit instruction
