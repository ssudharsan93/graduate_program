#include "printer.h"

int PT;
int NC;
int CQS;
int MQS;
bool TERMINATE = false;

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

void Communicator::enqueue_message(string msg){ 
    
    this->msg_queue_prot.lock();
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
    this->msg_queue_prot.lock();
    return this->message_queue->size();
    this->msg_queue_prot.unlock();
}

void spawn_communicators() {

    for ( int communicator_cntr = 0; communicator_cntr < NC; communicator_cntr++ ) {
        
        pthread_t new_communicator_thread;
        Communicator *new_communicator = new Communicator();
        communicators[communicator_cntr] = new_communicator;
        new_communicator->set_index(communicator_cntr);

        pthread_create(&new_communicator_thread, NULL, communicator, (void*) new_communicator);

        communicator_tids[communicator_cntr] = new_communicator_thread;

        int communicator_index = communicators[communicator_cntr]->get_index();

        cout << "Spawning thread.." << endl;
        cout << "Thread: " <<  communicator_index << endl;
        cout << "Thread ID: " << &communicator_tids[communicator_index] << endl;

    }

}

void terminate_communicators() {
    
    for ( int communicator_cntr = 0; communicator_cntr < NC; communicator_cntr++ ) {
       
        int communicator_index = communicators[communicator_cntr]->get_index();

        cout << "Terminating thread.." << endl;
        cout << "Thread: " << communicators[communicator_cntr]->get_index() << endl;
        cout << "Thread ID: " << &communicator_tids[communicator_cntr] << endl;
        pthread_join(communicator_tids[communicator_cntr], NULL);
    
    }

    delete [] communicators;
    delete [] communicator_tids;
    
}

void *printer_main(void *PrintingTime){
    return 0;
}

void *communicator(void *arg) {

    Communicator *communicator_obj = (Communicator*) arg;

    string msg1 = "TRM,001002,msg1";
    string msg2 = "PRT,002003,msg2";
    string msg3 = "SPL,007009,msg3";
    string msg4 = "END,010006,msg4";

    //sem_signal(&sync_pc);
    //sem_wait(&sync_pc);
    // communicator_obj->enqueue_message(msg1);
    // communicator_obj->enqueue_message(msg2);
    // communicator_obj->enqueue_message(msg3);
    // communicator_obj->enqueue_message(msg4);
    //sem_signal(&sync_pc);

    // while ( !TERMINATE ) {
    //     usleep(500);
    //     communicator_obj->enqueue_message(msg1);
    //     usleep(5000);
    //     communicator_obj->enqueue_message(msg2);
    //     usleep(500000);
    //     communicator_obj->enqueue_message(msg3);
    //     usleep(5000000);
    //     communicator_obj->enqueue_message(msg4);
    // }

    return 0;
}

// Printer Manager Methods Start

int get_connection() {
    
    conn_queue_prot.lock();
    int socket_fd = connection_queue->front();
    connection_queue->pop();
    conn_queue_prot.unlock();

    return socket_fd;
}

void print_manager_init() {

    //configuration parameters file read start
    char delim[] = " ,";
    char config_data[255];
    
    ifstream config_file("config.sys");

    if ( !config_file.good() ) {
      cout << "Error: config.sys doesn't exist" << endl;
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

    connection_queue = new queue<int>();
    //sem_init(&sync_pc, 0, 0);

    communicators = new Communicator*[NC];
    communicator_tids = new pthread_t[NC];

    cout << "Printing Time: " << PT << endl;
    cout << "Number of Communicators: " << NC << endl;
    cout << "Connection Queue Size: " << CQS << endl;
    cout << "Message Queue Size: " << MQS << endl;

    //spawn_communicators();

    //pthread_create(&orinter, NULL, printer_main, (void*) PT);

    return;

}

void printer_manager() {
    print_manager_init();

    char input;
    int cmd = -1;

    while( !TERMINATE ) {
        usleep(10000);
	    cout << "Terminate System? Type in 1 if Yes. > ";
        
        cin.get(input);

        if ( !isdigit(input) || input == '\n' ) {
            cout << endl;
            continue;
        }
        
        else {
            cmd = ( (int) input ) - ( (int) '0' );
        }

        if ( cmd == 1 ){
            TERMINATE = true;
        }
    }

    //terminate_communicators();
    
    // listen()
    // conn_queue_prot.lock();
    // accept()
    // enqueue();
    // conn_queue_prot.unlock();
}

// Printer Manager Methods End

int main() {
    printer_manager();
    return 0;
}