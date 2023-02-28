#include "print.h"

int printer_read;
int print_read;
int printer_write;
int print_write;
pid_t pid;
bool TERMINATE = false;

void print_init() {
    int fds1[2];
    int fds2[2];
    int fds3[2];

    char buffer[1024];
        
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
            
        int read_return_code = read(print_read, buffer, sizeof(buffer));
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
    
    char spool[] = "SPL ";
    char pid_str[80];
    char newline[] = "\n";
    
    sprintf(pid_str, "%d", PID);
    
    strcat(spool, pid_str);
    strcat(spool, newline);

    write(print_write, spool, sizeof(spool));
    
    return;
}

void print_end_spool(int PID){
    char end[] = "END ";
    char pid_str[80];
    char newline[] = "\n";
    
    sprintf(pid_str, "%d", PID);
    
    strcat(end, pid_str);
    strcat(end, newline);

    cout << end << sizeof(end) << endl;

    write(print_write, end, sizeof(end));
}

void print_print(char buffer[], int PID) {
    char prt[] = "PRT ";
    char pid_str[80];
    char newline[] = "\n";
    
    sprintf(pid_str, "%d", PID);
    
    strcat(prt, pid_str);
    strcat(prt, newline);

    cout << prt << sizeof(prt) << endl;
    write(print_write, prt, sizeof(prt));
    write(print_write, buffer, sizeof(buffer));

    return;
}

void print_terminate() {

    char trm[] = "TRM ";
    char pid_str[80];
    char newline[] = "\n";
    char buffer[1024];
    
    sprintf(pid_str, "%d", 9999);
    
    strcat(trm, pid_str);
    strcat(trm, newline);

    cout << trm << sizeof(trm) << endl;
    write(print_write, trm, sizeof(trm));
    read(print_read, buffer, sizeof(buffer));

    cout << buffer << endl;

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
        char msg[] = "I want to print this to the spool file";
        
        print_init_spool(1);
        //print_print(msg, 1);
        //print_end_spool(1);
        print_terminate();
    }

    return 0;

}


