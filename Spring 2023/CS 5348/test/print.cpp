#include "print.h"

int printer_read;
int print_read;
int printer_write;
int print_write;
pid_t pid;
bool TERMINATE = false;

void send_instruction(string instruction, int PID, string msg = "") {

    string cmd;
    string space = " ";
    string process_id;
    string newline = "\n";
    char return_msg[80];
    
    process_id = to_string(PID);
    cmd = instruction + space + process_id + newline + msg;

    char buffer[cmd.size()+1];
    strcpy(buffer, cmd.c_str());

    write(print_write, buffer, sizeof(cmd));
    fsync(print_write);
    read(print_read, return_msg, sizeof(return_msg));
    cout << "Received: " << return_msg << endl;
    
    return;
}

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

        //int flags = fcntl(print_read, F_GETFL, 0);
        //fcntl(print_read, FSETFL, flags | O_NONBLOCK);

        //bool NOACK = true;

        //while ( NOACK ) {
            
        read(print_read, buffer, sizeof(buffer));
        //if ( read_return_code == 0 ){ // nothing was received
        //    continue;
        //}

        cout << "Received: " << buffer << endl;
        //NOACK = false;

        //}


    } else { // printer process
        
        close(print_read);
        close(print_write);

        printer_main();

        close(printer_read);
        close(printer_write);

    }
}

void print_init_spool(int PID) {
    
    send_instruction("SPL", PID);
}

void print_end_spool(int PID){

    send_instruction("END",PID);
}

void print_print(char buffer[], int PID) {

    string msg(buffer);
    send_instruction("PRT", PID, msg);

}

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
        char msg[] = "AC: ";
        
        print_init_spool(1);
        print_print(msg, 1);
        print_end_spool(1);
        print_terminate();

    }

    return 0;

}


