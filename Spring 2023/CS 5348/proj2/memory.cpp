#include "computer.h"

Memory::Memory(){
    this->mem_init(0);
}

Memory::~Memory(){
    delete this->Mem;
}

Memory::Memory(int size){
    this->mem_init(size);
}

void Memory::mem_init(int M){
    this->Mem = new int[M];

    for (int mem_index = 0; mem_index < M; mem_index++) {
        this->Mem[mem_index] = 0;
    }

    this->size = M;
}

void Memory::mem_read(){
    MBR = this->Mem[MAR];
}

void Memory::mem_write(){
    this->Mem[MAR] = MBR;
}
