#ifndef MEMORY_H
#define MEMORY_H

using namespace std;

class Memory {
public:
    int *Mem;
    int size;
    Memory();
    Memory(int size);
    void mem_init(int M);
    void mem_read();
    void mem_write();

};

#endif MEMORY_H