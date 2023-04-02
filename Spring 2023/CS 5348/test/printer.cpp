#include "printer.h"

/*
    sem_getvalue() places the current value of the semaphore pointed
    to sem into the integer pointed to by sval.

    sem_wait() decrements (locks) the semaphore pointed to by sem.
    If the semaphore's value is greater than zero, then the decrement
    proceeds, and the function returns, immediately.  If the
    semaphore currently has the value zero, then the call blocks
    until it becomes possible to perform the decrement. .
    
    sem_post() increments (unlocks) the semaphore pointed to by sem.
    If the semaphore's value consequently becomes greater than zero,
    then another process or thread blocked in a sem_wait(3) call will
    be woken up and proceed to lock the semaphore.
*/

sem_t *conn_queue_guard;
sem_t *conn_queue_full;
sem_t *conn_queue_empty;

sem_t *sync_pc;
sem_t *comm_printer_guard;
sem_t *comm_prot;

Communicator **communicators;
pthread_t *communicator_tids;
pthread_t printer;
queue<int> *connection_queue;

int comm_count;
int full_queue_select = 0;

map<string, FILE*> *file_desc_struct;

int SERVER_FD;
int PT;
int NC;
int CQS;
int MQS;
bool TERMINATE = false;
bool DEBUG_flag = true;
bool SPOOF_flag = false;

Communicator::Communicator() {
    this->message_queue = new queue<string>();
}

Communicator::~Communicator() {
    delete this->message_queue;
}

int Communicator::get_index(){
    return this->index;
}

void Communicator::set_index(int index){
    this->index = index;
}

int Communicator::get_bin_selector(){
    return this->bin_selector;
}

void Communicator::set_bin_selector(int bin_selector){
    this->bin_selector = bin_selector;
}

bool Communicator::get_terminate_flag(){
    return this->terminate_flag;
}

void Communicator::set_terminate_flag(){
    this->terminate_flag = true;
}

void Communicator::clear_terminate_flag(){
    this->terminate_flag = false;
}

void Communicator::enqueue_message(string msg){

    this->msg_queue_prot.lock();

    string index = to_string(this->get_index());
    string msg_to_be_printed = "\t\t\tEnqueuing in Communicator " + 
                               index + ": \t\t------>\t\t" + msg + "\n";
    const char* msg_to_print = msg_to_be_printed.c_str();
    
    cout.write(msg_to_print, msg_to_be_printed.size() + 1);
    cout.flush();

    this->message_queue->push(msg);
    
    this->msg_queue_prot.unlock();
}

string Communicator::dequeue_message(){
    
    this->msg_queue_prot.lock();
    string msg = this->message_queue->front();
    this->message_queue->pop();
    this->msg_queue_prot.unlock();
    
    return msg;
}

int Communicator::get_queue_size(){

    int Q_size;
    this->msg_queue_prot.lock();
    Q_size = this->message_queue->size();
    this->msg_queue_prot.unlock();

    return Q_size;
}

bool Communicator::is_queue_empty(){

    bool is_empty;
    is_empty = ( this->get_queue_size() == 0 );

    return is_empty;
}

// ############## PRINTER METHODS START ###############
void send_response(string response) {
    
    char resp[response.size() + 1];
    strcpy(resp, response.c_str());
    
}

void print_spool_to_printout(string CID, string PID, string footer, map<string, FILE*> *file_desc_struct){

    string print_out_file_index = CID + ".XXX";
    string spool_file_index = CID + "." + PID;

    FILE* spool_fp = file_desc_struct->at(spool_file_index);
    FILE* printer_fp = file_desc_struct->at(print_out_file_index);

    char line[100];

    fseek(spool_fp, 0, SEEK_SET);

    while ( fgets(line, sizeof(line), spool_fp) ){
        usleep(PT);
        fputs(line, printer_fp);
    }

    string separator =    "--------------------\n";
    string process_footer = separator + footer + separator;

    char close_msg[process_footer.size() + 1];
    strcpy(close_msg, process_footer.c_str());
    usleep(PT);
    fputs(close_msg, printer_fp);

    fclose(spool_fp);

    string fname;
    string CID_PID = CID + "_" + PID;
    string file_footer = "_spool.txt";

    fname = CID_PID + file_footer;

    char spool_fname[fname.size() + 1];
    strcpy(spool_fname, fname.c_str());

    cout << "Removing " << fname << "..." << endl;

    remove(spool_fname);

}

//Initialize the printer, including opening the simulated printing paper, i.e., the “printer.out” file.
//Sends an ACK to the print component to indicate that the initialization is done.
void printer_init(string CID, map<string, FILE*> *file_desc_struct) {

    FILE *fp = NULL;

    string print_out_file_index = CID + ".XXX";

    string fname = CID + "_printer.out";
    cout << "Creating: " << fname << endl;

    char print_out_fname[fname.size() + 1];
    strcpy(print_out_fname, fname.c_str());

    auto file_desc_struct_it = file_desc_struct->find(print_out_file_index);
    
    if ( file_desc_struct_it == file_desc_struct->end() ) {

        fp = fopen(print_out_fname, "w");
        pair<string, FILE*> pid_file_desc_pair = make_pair(print_out_file_index, fp);
        file_desc_struct->insert(pid_file_desc_pair);
    
    } else { 
        cout << "printer.out file already exists for Computer: " << CID << endl;
    }

    return;

}

//Opening a spool file for the process.
//You can use PID to differentiate the spool file names.
void printer_init_spool(string CID, string PID, map<string, FILE*> *file_desc_struct){

    FILE *fp = NULL;
    
    string spool_file_index = CID + "." + PID;

    string footer = "_spool.txt";

    string fname = CID + "_" + PID + footer;
    cout << "Creating: " << fname << endl;

    char spool_fname[fname.size() + 1];
    strcpy(spool_fname, fname.c_str());

    auto file_desc_struct_it = file_desc_struct->find(spool_file_index);
        
    if ( file_desc_struct_it == file_desc_struct->end() ) {
        
        fp = fopen(spool_fname, "w+");

        pair<string, FILE*> pid_file_desc_pair = make_pair(spool_file_index, fp);
        file_desc_struct->insert(pid_file_desc_pair);

        string separator =    "--------------------\n";
        string process_str =  "     Computer: " + CID + " Process: " + PID + "\n";
        string process_header = separator + process_str + separator;
        char init_msg[process_header.size() + 1];
        strcpy(init_msg, process_header.c_str());

        fputs(init_msg, fp);
    
    } 

    else {
        cout << "Spool file already exists for Computer: " << CID << " PID: " << PID << endl;
    }

    return;


}

//The printer prints the contents in the spool file of the process to the simulated paper and close the spool file.
void printer_end_spool(string CID, string PID, map<string, FILE*> *file_desc_struct){
    
    cout << "End Spool Start" << endl;

    string footer =  "     End Computer: " + CID + " Process: " + PID + "\n";
    print_spool_to_printout(CID, PID, footer, file_desc_struct);

    string spool_file_index = CID + "." + PID;

    file_desc_struct->erase(spool_file_index);

    return;

}

void printer_dump_spool(map<string, FILE*> *file_desc_struct){
    
    auto f_desc_struct_begin = file_desc_struct->begin();
    auto f_desc_struct_end = file_desc_struct->end();
    string CID_PID;

    cout << "===========================" << endl;
    cout << "      Printer Dump         " << endl;
    cout << "===========================" << endl;
    cout << "Index: CID_PID" << endl;

    int index = 0;

    for ( auto f_desc_struct_it = f_desc_struct_begin; f_desc_struct_it != f_desc_struct_end; ++f_desc_struct_it ) {
        CID_PID = f_desc_struct_it->first;
        cout << index << ":" << CID_PID << endl;
        index = index + 1;
    }

}

//This function is for handling the regular print instructions.
//It should determine which spool file to use and writes the to-be-printed content to the spool file.
void printer_print(string CID, string PID, string buffer, map<string, FILE*> *file_desc_struct){

    string spool_file_index = CID + "." + PID;
    FILE *spool_fp = file_desc_struct->at(spool_file_index);

    char buffer_to_be_written[buffer.size() + 1];
    strcpy(buffer_to_be_written, buffer.c_str());

    fputs(buffer_to_be_written, spool_fp);
    fputs("\n", spool_fp);

    return;

}

//For any process that has not terminated, print its partial output in its spool file
//to the simulated paper, and add a message at the end to indicate that the process did
//not finish yet. Then, clean up and terminate the printer process.
void printer_terminate(string CID, map<string, FILE*> *file_desc_struct){
    
    auto f_desc_struct_begin = file_desc_struct->begin();
    auto f_desc_struct_end = file_desc_struct->end();
    string CID_PID;
    FILE *spool_fp;

    for ( auto f_desc_struct_it = f_desc_struct_begin; f_desc_struct_it != f_desc_struct_end; ++f_desc_struct_it ) {
        CID_PID = f_desc_struct_it->first;
        spool_fp = f_desc_struct_it->second;

        char CID_PID_str[CID_PID.size() + 1];
        strcpy(CID_PID_str, CID_PID.c_str());
        char CID_PID_delim[] = ".";

        char *id_param = strtok(CID_PID_str, CID_PID_delim);
        string curr_CID(id_param);
        id_param = strtok(NULL, CID_PID_delim);
        string curr_PID(id_param);

        if ( curr_CID.compare(CID) == 0 ) {

            if ( curr_PID.compare("XXX") == 0 ) {
                cout << "Printout file is still in the system: " << CID_PID << endl;
                continue;
            }

            string footer =  "     Computer: " + curr_CID + " Process: " + curr_PID + " Terminated without Completion.\n";
            cout << footer << endl;
            print_spool_to_printout(curr_CID, curr_PID, footer, file_desc_struct);
        }
        
    }

    string print_out_file_index = CID + ".XXX";
    FILE *printer_out_fp = file_desc_struct->at(print_out_file_index);
    fclose(printer_out_fp);
    cout << "Erasing entry: " << print_out_file_index << endl;
    file_desc_struct->erase(print_out_file_index);

}

int exec_printer_cmd(string cmd, string CID_PID, string data, map<string, FILE*> *file_desc_struct){

    //SPL is SPOOL INIT
    //END is SPOOL END
    //PRT is PRINT
    //TRM is TERMINATE

    int ret_code = 0;

    char CID_PID_str[CID_PID.size() + 1];
    strcpy(CID_PID_str, CID_PID.c_str());
    char CID_PID_delim[] = ".";

    string SPL = "SPL";
    string END = "END";
    string PRT = "PRT";
    string DMP = "DMP";
    string TRM = "TRM";

    char *id_param = strtok(CID_PID_str, CID_PID_delim);
    string CID(id_param);
    id_param = strtok(NULL, CID_PID_delim);
    string PID(id_param);

    cout << "\t\t\tCommand:                 \t\t\t\t" << cmd << " ..." << endl;
    cout << "\t\t\tCID    :                 \t\t\t\t" << CID << " ..." << endl;
    cout << "\t\t\tPID    :                 \t\t\t\t" << PID << " ..." << endl;
    cout << "\t\t\tData   :                 \t\t\t\t" << data << " ..." << endl;

    if ( cmd.compare(SPL) == 0 ) {
        cout << "\t\t\tSpooling...                 \t\t\t\t" << CID_PID << endl;
        printer_init(CID, file_desc_struct);
        printer_init_spool(CID, PID, file_desc_struct);
        //printer_dump_spool(file_desc_struct);

    } 
    
    else if ( cmd.compare(END) == 0 ) {
        cout << "\t\t\tEnding...                 \t\t\t\t" << CID_PID << endl;
        printer_end_spool(CID, PID, file_desc_struct);
        //printer_dump_spool(file_desc_struct);

    } 
    
    else if ( cmd.compare(PRT) == 0 ) {
        cout << "\t\t\tPrinting...                 \t\t\t\t" << CID_PID << endl;
        printer_print(CID, PID, data, file_desc_struct);
    } 

    else if ( cmd.compare(DMP) == 0 ) {
        cout << "\t\t\tDumping...                 \t\t\t\t" << CID_PID << endl;
        printer_dump_spool(file_desc_struct);
    }
    
    else if ( cmd.compare(TRM) == 0 ) {
        cout << "\t\t\tTerminating...                 \t\t\t\t" << CID_PID << endl;
        printer_terminate(CID, file_desc_struct);
        ret_code = 1;
    } 

    else {
        cout << "Unknown CMD";
    }

    return ret_code;

}

int service_printer_cmd(string msg, map<string, FILE*> *file_desc_struct) {

    char rcvd_msg[msg.size() + 1];
    strcpy(rcvd_msg, msg.c_str());

    char *message;
    int PID;

    FILE *fp = NULL;
    FILE *printer_out_fp = NULL;

    char delim[] = ",";
            
    message = strtok(rcvd_msg, delim);
    string command(message);
    message = strtok(NULL, delim);
    string CID_PID(message);
    message = strtok(NULL, delim);
    string data(message);

    return exec_printer_cmd(command, CID_PID, data, file_desc_struct);
}

// ############## PRINTER METHODS END ###############

// ############## THREAD METHODS START ###############

bool is_bit_set(int bin_number, int bit_index) {
    bool bit_is_set = ( bin_number >> bit_index & 1 ) == 1 ? true : false;

    if ( DEBUG_flag ) {
        cout << endl;
        cout << "\t\tIs Bit Number " << bit_index << " for number: ";
        cout << bin_number << " set? : " << bit_is_set << endl;
    }
    
    return bit_is_set;
}

int clear_bit(int bin_number, int bit_index) {

    if ( DEBUG_flag ) {
        cout << endl;
        cout << "\t\tNumber before bit " << bit_index << " was cleared: " << bin_number << endl;
    }
    
    int mask = 1 << bit_index;       // shift the 1 left until the bit to be cleared is reached.
    bin_number = bin_number & ~mask; // do bitwise negation so there are 1s in every other place
                                     // and a 0 in the bit to be cleared.
    
    if ( DEBUG_flag ) {
        cout << "\t\tNumber after bit " << bit_index << " was cleared: " << bin_number << endl;
        cout << endl;
    }

    return bin_number;
}
int set_bit(int bin_number, int bit_index) {

    if ( DEBUG_flag ) {
        cout << endl;
        cout << "\t\tNumber before bit " << bit_index << " was set: " << bin_number << endl;
    }

    int mask = 1 << bit_index;
    bin_number = bin_number | mask;

    if ( DEBUG_flag ){
        cout << "\t\tNumber after bit " << bit_index << " was set: " << bin_number << endl;
        cout << endl;
    }

    return bin_number;
}

void communicator_critical_section(Communicator *comm_obj, string msg) {

    int sem_wait_ret_code;
    int sem_post_ret_code;
    int sem_getval_ret_code;
    int sync_pc_val;

    sem_wait_ret_code = sem_wait(comm_prot);           // protect against other communicators

    comm_count++;                  // increase the number of communicators
    if (comm_count == 1) {
        sem_wait_ret_code = sem_wait(comm_printer_guard);
    }                              // if first communicator check if printer is reading
    sem_post_ret_code = sem_post(comm_prot);           // release to allow other communicators through

    if ( DEBUG_flag ) {
        cout << endl;
        cout << "##########\t\tIn Communicator Critical Section.\t\t##########" << endl;
        cout << endl;
    }

    comm_obj->enqueue_message(msg);

    sem_wait_ret_code = sem_wait(comm_prot);             // protect against other communicators
    comm_count--;                                        // decrease the number of communicators

    if ( ( ( full_queue_select >> comm_obj->get_index() ) & 1 ) == 0 ) {
       sem_post_ret_code = sem_post(sync_pc);
    }
    
    full_queue_select = set_bit(full_queue_select, comm_obj->get_index());

    if (comm_count == 0) {                           // if last communicator 
        sem_post_ret_code = sem_post(comm_printer_guard);
    }
    sem_post_ret_code = sem_post(comm_prot);         // release to allow other communicators through
        
}

void printer_critical_section(map<string, FILE*> *file_desc_struct) {

    if ( DEBUG_flag ) {
        cout << endl;
        cout << "#####################################################" << endl;
        cout << "          In Printer Critical Section.               " << endl;
        cout << "#####################################################" << endl;
        cout << endl;
    }
    
    Communicator *comm_obj;
    string msg;

    for ( int communicator_cntr = 0; communicator_cntr < NC; communicator_cntr++ ) {
        comm_obj = communicators[communicator_cntr];

        if ( ! ( is_bit_set(full_queue_select, comm_obj->get_index()) ) ) {
            cout << "\t\tQueue " << comm_obj->get_index() << " is empty. Queue Selector: " << full_queue_select << endl;
            continue;
        } 
        
        else { 
            cout << "\t\tEmptying Communicator: " << communicator_cntr << " ..." << endl;
            while ( ! ( comm_obj->is_queue_empty() ) ) {
                msg = comm_obj->dequeue_message();
                cout << endl;
                cout << "\t\t\tServicing:                 \t\t------>\t\t" << msg << " ..." << endl;
                service_printer_cmd(msg, file_desc_struct);
            }
            
            full_queue_select = clear_bit(full_queue_select, comm_obj->get_index());
            break;
        }
    }

}

void *printer_main(void *arg){

    int sem_wait_ret_code;
    int sem_post_ret_code;
    int sem_getval_ret_code;
    int sync_pc_val;

    map<string, FILE*> *file_desc_struct = new map<string, FILE*>();

    while ( !TERMINATE ) {
        sem_wait_ret_code = sem_wait(sync_pc); // wait for a message to exist
        
        if ( sem_wait_ret_code == -1 ) {
            cout << "Error with sync_pc has occurred.";

            if (errno == EINTR) {
                cout << "EINTR error" << endl;
            } else if (errno == EINVAL) {
                cout << "EINVAL error" << endl;
            } else { 
                cout << "Another error occurred: " << errno << endl;
            }
        }

        sem_wait_ret_code = sem_wait(comm_printer_guard); // tell communicators you are reading a message
        if ( sem_wait_ret_code == -1 ) {
            cout << "Error with guard has occurred.";
            if (errno == EINTR) {
                cout << "EINTR error" << endl;
            } else if (errno == EINVAL) {
                cout << "EINVAL error" << endl;
            } else { 
                cout << "Another error occurred: " << errno << endl;
            }
        }

        printer_critical_section(file_desc_struct);
        
        sem_post_ret_code = sem_post(comm_printer_guard); // tell communicators you are done reading    
    }
    
    return 0;
}

void *communicator(void *arg) {

    Communicator *comm_obj = (Communicator*) arg;

    string values[] = {"AC:20", "AC:5000", "AC:89000"};
    int num_of_computers_serviced = 0;

    string msg;
    string CMD;

    bool terminate_conn_received = false;

    while ( !TERMINATE ) {
        
        if ( DEBUG_flag ) {
            cout << "Communicator: " << comm_obj->get_index()<< " is waiting for a connection..." << endl;
        }
        
        if ( SPOOF_flag ) {

            string CID = to_string(get_connection()); 

            if ( DEBUG_flag ) {
                cout << "Communicator is acquired connection." << endl;
            }

            int spoof_PID = 1;

            string msg1 = "SPL," + CID + "." + to_string(spoof_PID) + ",###";
            string msg2 = "PRT," + CID + "." + to_string(spoof_PID) + "," + values[0];
            string msg3 = "PRT," + CID + "." + to_string(spoof_PID) + "," + values[1];
            string msg4 = "PRT," + CID + "." + to_string(spoof_PID) + "," + values[2];
            string msg5 = "END," + CID + "." + to_string(spoof_PID) + ",###";
            string msg6 = "TRM," + CID + "." + to_string(spoof_PID) + ",###";

            usleep( ( comm_obj->get_index() + 1 ) * 10);
            communicator_critical_section(comm_obj, msg1);
            usleep( ( comm_obj->get_index() + 1 ) * 100);
            communicator_critical_section(comm_obj, msg2);
            usleep( ( comm_obj->get_index() + 1 ) * 10000);
            communicator_critical_section(comm_obj, msg3);
            usleep( ( comm_obj->get_index() + 1 ) * 100000);
            communicator_critical_section(comm_obj, msg4);
            usleep( ( comm_obj->get_index() + 1 ) * 1000000);
            communicator_critical_section(comm_obj, msg5);

            spoof_PID = 2;

            msg1 = "SPL," + CID + "." + to_string(spoof_PID) + ",###";
            msg2 = "PRT," + CID + "." + to_string(spoof_PID) + "," + values[0];
            msg3 = "PRT," + CID + "." + to_string(spoof_PID) + "," + values[1];
            msg4 = "PRT," + CID + "." + to_string(spoof_PID) + "," + values[2];
            msg5 = "END," + CID + "." + to_string(spoof_PID) + ",###";
            msg6 = "TRM," + CID + "." + to_string(spoof_PID) + ",###";

            usleep( ( comm_obj->get_index() + 1 ) * 10);
            communicator_critical_section(comm_obj, msg1);
            usleep( ( comm_obj->get_index() + 1 ) * 100);
            communicator_critical_section(comm_obj, msg2);
            usleep( ( comm_obj->get_index() + 1 ) * 10000);
            communicator_critical_section(comm_obj, msg3);
            usleep( ( comm_obj->get_index() + 1 ) * 100000);
            communicator_critical_section(comm_obj, msg4);

            //TERMINATE
            usleep( ( comm_obj->get_index() + 1 ) * 1000000);
            communicator_critical_section(comm_obj, msg6);
        }

        int client_fd = get_connection();

        if ( DEBUG_flag ) {
            cout << "Communicator has acquired connection: " << client_fd << endl;
        }

        while ( !terminate_conn_received ) {
            string msg = get_msg_from_connection(client_fd);
            CMD =  msg.substr(0, msg.find(","));
            
            if ( CMD.compare("TRM") == 0 ) {
                if ( DEBUG_flag ) {
                    cout << "Terminate received. Closing client file descriptor." << endl;
                }
                
                close(client_fd);
                terminate_conn_received = true;
            }
            
            communicator_critical_section(comm_obj, msg);
        }

        terminate_conn_received = false;
    }

    // while ( !TERMINATE ) {
    //     usleep(500000);
    // }

    return 0;
}

string get_msg_from_connection(int client_fd) {

    if ( DEBUG_flag ) {
        cout << "Trying to get a message from client: " << to_string(client_fd) << endl;
    } 
    
    char buffer[1024];
    int recv_ret = recv(client_fd, buffer, sizeof(buffer), 0);
    string msg = string(buffer);

    if ( recv_ret > 0 ) {
        if ( DEBUG_flag ) {
            cout << "Message: " << msg << " Message Size: "<< msg.length() << endl;
        }
        return msg;
    }

    return "";

}

int get_connection() {

    int sem_wait_ret_code;
    int sem_post_ret_code;
    int sem_getval_ret_code;

    sem_wait_ret_code = sem_wait(conn_queue_empty);
    sem_wait_ret_code = sem_wait(conn_queue_guard);

    int socket_fd = connection_queue->front();
    connection_queue->pop();
    
    sem_post_ret_code = sem_post(conn_queue_full);
    sem_post_ret_code = sem_post(conn_queue_guard);

    return socket_fd;
}

// ############## THREAD METHODS END ###############

// ############## PRINTER MANAGER METHODS START ############### 
void test_connection_acceptance() {

    place_connection(1);
    place_connection(2);
    place_connection(3);

    // for (int i = 0; i < 10000; i++) {
    //     place_connection(i);
    //     place_connection(i+1);
    //     place_connection(i+2);
    //     place_connection(i+3);
        
    //     usleep(10000000);
    //     place_connection(i+4);
    //     place_connection(i+5);
    //     place_connection(i+6);
    // }

}

void place_connection(int socket) {

    int sem_wait_ret_code;
    int sem_post_ret_code;
    int sem_getval_ret_code;
    
    cout << "Printer Manager is attempting to place connection: " << socket << endl;
    
    sem_wait_ret_code = sem_wait(conn_queue_full);
    sem_wait_ret_code = sem_wait(conn_queue_guard);

    cout << "Printer Manager is placing a connection..." << endl;

    connection_queue->push(socket);

    sem_post_ret_code = sem_post(conn_queue_empty);
    sem_post_ret_code = sem_post(conn_queue_guard);

}

void initialize_semaphores() {

    conn_queue_guard = sem_open("/proj3_conn_queue_guard", O_CREAT, 0666, 1); 
    
    if (conn_queue_guard == SEM_FAILED) {
        perror("sem_open");
        exit(1);
    }

    conn_queue_empty = sem_open("/proj3_conn_queue_empty", O_CREAT, 0666, 0); 
    
    if (conn_queue_empty == SEM_FAILED) {
        perror("sem_open");
        exit(1);
    }

    conn_queue_full = sem_open("/proj3_conn_queue_full", O_CREAT, 0666, CQS); 
    
    if (conn_queue_full == SEM_FAILED) {
        perror("sem_open");
        exit(1);
    }

    sync_pc = sem_open("/proj3_sync_pc", O_CREAT, 0666, 0);
    
    if (sync_pc == SEM_FAILED) {
        perror("sem_open");
        exit(1);
    }
    
    comm_printer_guard = sem_open("/proj3_comm_printer_guard", O_CREAT, 0666, 1);
    
    if (comm_printer_guard == SEM_FAILED) {
        perror("sem_open");
        exit(1);
    }
    comm_prot = sem_open("/proj3_comm_prot", O_CREAT, 0666, 1); 
    
    if (comm_prot == SEM_FAILED) {
        perror("sem_open");
        exit(1);
    } 
}

void close_semaphores() {

    sem_close(conn_queue_guard);
    sem_close(conn_queue_empty);
    sem_close(conn_queue_full);

    sem_close(sync_pc);
    sem_close(comm_printer_guard);
    sem_close(comm_prot);

    sem_unlink("/proj3_conn_queue_guard");
    sem_unlink("/proj3_conn_queue_empty");
    sem_unlink("/proj3_conn_queue_full");

    sem_unlink("/proj3_sync_pc");
    sem_unlink("/proj3_comm_printer_guard");
    sem_unlink("/proj3_comm_prot");
}

void spawn_printer() {

    int *PT_ptr = &PT;
    pthread_create(&printer, NULL, printer_main, (void*) PT_ptr);
    cout << "Printer Ready..." << endl;
    cout << "Thread ID: " << &printer << endl;

}

void terminate_printer() {
    
    cout << "Terminating Printer.." << endl;
    cout << "Thread ID: " << &printer << endl;
    //pthread_join(printer, NULL);
    pthread_cancel(printer);

}

void spawn_communicators() {

    cout << endl;
    cout << endl;

    for ( int communicator_cntr = 0; communicator_cntr < NC; communicator_cntr++ ) {
        
        pthread_t new_communicator_thread;
        Communicator *new_communicator = new Communicator();
        communicators[communicator_cntr] = new_communicator;
        new_communicator->set_index(communicator_cntr);

        pthread_create(&new_communicator_thread, NULL, communicator, (void*) new_communicator);

        communicator_tids[communicator_cntr] = new_communicator_thread;
        string thread_msg = "Spawning Communicator Thread: " + to_string(communicator_cntr) + " ...\n";
        cout.write( thread_msg.c_str(), thread_msg.size() + 1 );

    }

    cout << endl;
    cout << endl;

}

void terminate_communicators() {

    cout << endl;
    cout << endl;
    
    for ( int communicator_cntr = 0; communicator_cntr < NC; communicator_cntr++ ) {
       
        int communicator_index = communicators[communicator_cntr]->get_index();

        cout << "Terminating thread.." << endl;
        cout << "Thread: " << communicators[communicator_cntr]->get_index() << endl;
        cout << "Thread ID: " << &communicator_tids[communicator_cntr] << endl;
        //pthread_join(communicator_tids[communicator_cntr], NULL);
        pthread_cancel(communicator_tids[communicator_cntr]);
    
    }

    cout << endl;
    cout << endl;

    delete [] communicators;
    delete [] communicator_tids;
    
}

int accept_connection() {
    
    struct sockaddr_in client_addr;
    int client_addrlen = sizeof(client_addr);

    int new_conn_fd = accept(SERVER_FD, (struct sockaddr *) &client_addr, (socklen_t*) &client_addrlen);
    int conn_accept_code = 1;
    send(new_conn_fd, &conn_accept_code, sizeof(conn_accept_code), 0);

    return new_conn_fd;

}

int set_up_printer_socket() {
    
    int server_fd;

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if ( server_fd < 0 ){
        perror("Error socket: ");
    }

    int port = 8140;

    struct sockaddr_in server_addr;

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(port);

    int bind_ret = bind(server_fd, (struct sockaddr *) &server_addr, sizeof(server_addr));
    if ( bind_ret < 0 ) {
        perror("Error bind: ");
    }

    return server_fd;

}

void read_and_set_sys_params() {

    //configuration parameters file read start
    char delim[] = " ,";
    char config_data[255];

    ifstream config_file;
    
    config_file.open("config.sys");

    if ( !config_file.good() ) {
        cout << "Error config file: `config.sys` does not exist." << endl;
    }

    config_file.getline(config_data, 255);
    char *config_arg = strtok(config_data, delim); 
    config_arg = strtok(NULL, delim); // discarding IP address
    config_arg = strtok(NULL, delim); // discarding port number
    config_arg = strtok(NULL, delim); // discarding M ( memory size )
    config_arg = strtok(NULL, delim); // discarding TQ ( Time Quantum )
    PT = atoi(config_arg);
    config_arg = strtok(NULL, delim); 
    NC = atoi(config_arg);
    config_arg = strtok(NULL, delim);
    CQS = atoi(config_arg);
    config_arg = strtok(NULL, delim);
    MQS = atoi(config_arg);

    config_file.close();
    //configuration parameters file read end

    cout << "Printing Time: " << PT << endl;
    cout << "Number of Communicators: " << NC << endl;
    cout << "Connection Queue Size: " << CQS << endl;
    cout << "Message Queue Size: " << MQS << endl;
    cout << "Full Queue Select: " << full_queue_select << endl;

}

int print_manager_init() {

    comm_count = 0;

    read_and_set_sys_params();

    int server_fd = set_up_printer_socket();


    connection_queue = new queue<int>();

    communicators = new Communicator*[NC];
    communicator_tids = new pthread_t[NC];

    return server_fd;

}

void ctrl_c_signal_callback_handlr(int signum) {
    cout << "Received CTRL-C command" << endl;
    TERMINATE = true;

    close(SERVER_FD);

    terminate_communicators();
    terminate_printer();
    close_semaphores();

    exit(0);
}

void printer_manager() {
    
    SERVER_FD = print_manager_init();

    char input;
    int cmd = -1;

    signal(SIGINT, ctrl_c_signal_callback_handlr);

    initialize_semaphores();
    spawn_communicators();
    spawn_printer();

    if ( SPOOF_flag ) {
        test_connection_acceptance();
    }

    struct sockaddr_in client_addr;
    int client_addrlen = sizeof(client_addr);

    listen(SERVER_FD, 32);

    while( !TERMINATE ) {

        //usleep(500000);
        cout << "Server is listening..." << endl;
        int new_conn_fd = accept(SERVER_FD, (struct sockaddr *) &client_addr, (socklen_t*) &client_addrlen);

        int conn_accept_code = 1;
        send(new_conn_fd, &conn_accept_code, sizeof(conn_accept_code), 0);
        
        place_connection(new_conn_fd);

    }

    //ctrl_c_signal_callback_handlr(0);

}

// ############## PRINTER MANAGER METHODS END ############### 

int main() {
    printer_manager();
    return 0;
}