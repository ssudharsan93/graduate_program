#include "computer.h"

int SERVER_FD;

void send_instruction(string instruction, string CID_PID, string msg = "XXX") {

    string cmd;
    string comma = ",";
    string newline = "\n";

    int send_ret;
    
    cmd = instruction + comma + CID_PID + comma + msg;

    int server_fd_flags = fcntl(SERVER_FD, F_GETFL, 0);
    fcntl(SERVER_FD, F_SETFL, server_fd_flags | O_NONBLOCK);

    char buffer[1024];
    strcpy(buffer, cmd.c_str());

    cout << "\t\t\tSending...\t\t--->\t\t" << buffer << endl;

    //send_ret = send(SERVER_FD, buffer, sizeof(buffer), 0);

    send(SERVER_FD, buffer, sizeof(buffer), MSG_DONTWAIT);
    
    return;
}

void print_init() {
    
    SERVER_FD = socket(AF_INET, SOCK_STREAM, 0);
    if ( SERVER_FD < 0 ){
        perror("Error socket: ");
    }

    const char *printer_ip_address = PRINTER_IP_ADDRESS.c_str();
    int printer_port_number = stoi(PRINTER_PORT_NUMBER);

    struct sockaddr_in server_addr;

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    inet_pton(AF_INET, printer_ip_address, &server_addr.sin_addr);
    server_addr.sin_port = htons(printer_port_number);

    int connection_accepted_code;

    int connect_ret = connect(SERVER_FD, (struct sockaddr *)&server_addr, sizeof(server_addr));
    int recv_ret = recv(SERVER_FD, &connection_accepted_code, sizeof(connection_accepted_code), 0);
    int send_ret;

    if ( connect_ret < 0 ) {
        cout << "Error code: " << errno << endl;
        if (errno == ECONNREFUSED) {
            cout << "Connection refused by server\n" << endl;
        } else {
            perror("Error connecting to server");
        }
    }

    if ( connection_accepted_code == 1 ) {
        cout << "Connection to server accepted. Server is ready to accept messages." << endl;
    }

}

//When a process is created,
//the computer can call this function to initialize the spooling for the process.
//This function simply sends the PID of the process to the corresponding printer
//function via the pipe.
void print_init_spool(int PID) {
    send_instruction("SPL", COMPUTER_ID + "." + to_string(PID));
}

//When a process exits, the computer can call this function
//to indicate the termination of the spool of the process
// and print outputs to the simulated paper.
void print_end_spool(int PID){
    send_instruction("END", COMPUTER_ID + "." + to_string(PID));
}

//Whenever cpu executes a print instruction, it calls this function.
//This function should at least have input parameters “buffer” and PID.
//CPU passes what is to be printed to print() via buffer.
//Function print() sends the buffer and PID to printer via the pipe.
void print_print(char buffer[], int PID) {

    cout << "Preparing to send print instruction." << endl;
    string msg(buffer);
    send_instruction("PRT", COMPUTER_ID + "." + to_string(PID), msg);

}

//This function is called to inform
// the printer to dump its spool information.
void print_dump_spool() {
    send_instruction("DMP", COMPUTER_ID + ".XXX"); //PID value is ignored by printer component
}

//Before the system terminates, this function is
// called to inform the printer to terminate.
void print_terminate() {
    send_instruction("TRM", COMPUTER_ID + ".XXX"); //PID value is ignored by printer component
}

void test_print_component() {

    print_init();

    char msg1[] = "AC: 7";
    char msg2[] = "AC: 9";
    
    print_init_spool(1);
    print_init_spool(2);
    print_print(msg1, 1);
    print_print(msg2, 2);
    print_end_spool(1);
    print_print(msg1, 2);
    print_end_spool(2);
    print_terminate();

}


