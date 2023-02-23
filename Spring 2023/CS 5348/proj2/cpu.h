#ifndef CPU_H
#define CPU_H

using namespace std;

extern int PC;
extern int IR0;
extern int IR1;
extern int MAR;
extern int MBR;
extern int AC;
extern int BASE;

class CPU {

public:
    void cpu_fetch_instruction();   // Read the 2 instruction words from memory, the addresses are computed from PC
    bool cpu_execute_instruction();  // For each instruction code, perform the simulated hardware operations
    int cpu_mem_address(int m_addr); // Compute the memory address to be accessed and put it in MAR.
                                      // The input is the PC or the operand (m-addr) of an instruction.
    int cpu_operation();           // Loop for executing instructions, starting from 0 till the exit instruction

};

#endif CPU_H
