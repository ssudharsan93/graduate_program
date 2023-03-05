#ifndef LOAD_H
#define LOAD_H

class Loader {
public:
    FILE* load_prog(char *fname, int base); // Open the user program file with the file name “fname”.
                                        // Copy the program to memory starting from memory address
    void load_finish(FILE *f);              // Clean up and close the program file
};

#endif LOAD_H