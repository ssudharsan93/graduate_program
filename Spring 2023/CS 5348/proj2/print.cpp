//Fork the printer process and establish the pipe communication. Wait for the ACK from printer via pipe.
print_init(...)

//When a process is created,
//the computer can call this function to initialize the spooling for the process.
//This function simply sends the PID of the process to the corresponding printer
//function via the pipe.
print_init_spool(...)

//When a process exits, the computer can call this function
//to indicate the termination of the spool of the process
// and print outputs to the simulated paper.
print_end_spool(...)

//Whenever cpu executes a print instruction, it calls this function.
//This function should at least have input parameters “buffer” and PID.
//CPU passes what is to be printed to print() via buffer.
//Function print() sends the buffer and PID to printer via the pipe.
print_print(...)

//Before the system terminates, this function is
// called to inform the printer to terminate.
print_terminate()
