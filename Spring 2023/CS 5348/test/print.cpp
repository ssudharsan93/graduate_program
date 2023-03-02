#include "print.h"

int printer_read;
int print_read;
int printer_write;
int print_write;
pid_t pid;
bool TERMINATE = false;

void send_instruction(string instruction, int PID, string msg = "") {

    string cmd;
    string comma = ",";
    string process_id;
    string newline = "\n";
    char return_msg[80];
    
    process_id = to_string(PID);
    cmd = instruction + comma + process_id;

    if ( ! ( msg.size() == 0 ) ) {
        cout << "Entered: " << msg << endl;
        cmd = cmd + comma + msg;
    }

    char buffer[cmd.size()+1];
    strcpy(buffer, cmd.c_str());

    write(print_write, buffer, sizeof(buffer));
    fsync(print_write);
    read(print_read, return_msg, sizeof(return_msg));
    cout << "Received: " << return_msg << endl;
    
    return;
}

//Fork the printer process and establish the pipe communication. Wait for the ACK from printer via pipe.
void print_init() {
    int fds1[2];
    int fds2[2];
    int fds3[2];

    char buffer[80];
        
    pipe(fds1); pipe(fds2);
    
    printer_read = fds1[0];
    print_read = fds2[0];
    printer_write = fds2[1];
    print_write = fds1[1];

    pid = fork();

    if ( pid > 0 ){ // print process
        close(printer_read);
        close(printer_write);
            
        read(print_read, buffer, sizeof(buffer));

        cout << "Received: " << buffer << endl;

    } else { // printer process
        
        close(print_read);
        close(print_write);

        printer_main();

        close(printer_read);
        close(printer_write);

    }
}

//When a process is created,
//the computer can call this function to initialize the spooling for the process.
//This function simply sends the PID of the process to the corresponding printer
//function via the pipe.
void print_init_spool(int PID) {
    
    send_instruction("SPL", PID);
}

//When a process exits, the computer can call this function
//to indicate the termination of the spool of the process
// and print outputs to the simulated paper.
void print_end_spool(int PID){

    send_instruction("END",PID);
}

//Whenever cpu executes a print instruction, it calls this function.
//This function should at least have input parameters “buffer” and PID.
//CPU passes what is to be printed to print() via buffer.
//Function print() sends the buffer and PID to printer via the pipe.
void print_print(char buffer[], int PID) {

    string msg(buffer);
    send_instruction("PRT", PID, msg);

}

//Before the system terminates, this function is
// called to inform the printer to terminate.
void print_terminate() {
    
    send_instruction("TRM", 9999); //PID value is ignored by printer component

    close(print_read);
    close(print_write);

    //cout << "terminating the system" << endl;

    //int kill_signal_num = SIGKILL;

    //kill(pid, kill_signal_num);
    //return;

}

int main() {

    print_init();

    if ( pid > 0 ) {
        char msg1[] = "AC:7";
        char msg2[] = "AC:9";
        
        print_init_spool(1);
        print_init_spool(2);
        print_print(msg1, 1);
        print_print(msg2, 2);
        print_end_spool(1);
        print_print(msg1, 2);
        print_end_spool(2);
        print_terminate();

    }

    return 0;

}


