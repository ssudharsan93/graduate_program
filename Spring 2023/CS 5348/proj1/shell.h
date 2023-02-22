#ifndef SHELL_H
#define SHELL_H

class Shell {

public:
    Shell();
    void shell_init();            // Initialize the shell module

    void shell_print_registers(); // Print out all the registers on the screen
    void shell_print_memory();    // Print out all the words in memory in integer form on the screen
    void shell_command (int cmd); // For each shell command code, call the corresponding functions.
                                   // Input cmd is the command code.
};

#endif SHELL_H
