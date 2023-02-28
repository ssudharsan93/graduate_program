#include test3.h

void print_init() {
    int fds1[2];
    int fds2[2];
    pid_t pid;

    pipe(fds1); pipe(fds2);
    
    printer_read = fds1[0];
    print_read = fds2[0];
    printer_write = fds2[1];
    print_write = fds1[1];

    pid = fork();

    if ( pid > 0 ){ // print process
        close(printer_read);
        close(printer_write);

        int flags = fcntl(print_read, F_GETFL, 0);
        fcntl(print_read, FSETFL, flags | O_NONBLOCK);

        bool NOACK = true;

        while ( NOACK ) {
            int read_return_code = read(print_read, buffer, sizeof(buffer));
            if ( read_return_code == 0 ){ // nothing was received
                continue;
            }

            cout << buffer << endl;
            NOACK = false;

        }

        close(print_read);
        close(print_write);


    } else { // printer process
        
        close(print_read);
        close(print_write);
        printer_main();

    }
}

void print_init_spool(int PID) {
    return;
}

void print_end_spool(int PID){
    return;
}

void print_terminate() {
    return;
}

int main() {

    print_init();

}


