#include "printer_manager.h"

int PT;
int NC;
int CQS;
int MQS;
bool TERMINATE = false;

pthread_t Communicator::get_tid(){
    return this->tid;
}
void Communicator::set_tid(){

}

void spawn_communicators() {

    for ( int communicator_cntr = 0; communicator_cntr < NC; communicator_cntr++ ) {
        pthread_t new_communicator_thread;
        communicators[communicator_cntr] = new_communicator_thread;
        Communicator *new_communicator = new Communicator();
        Communicator->set_tid(new_communicator_thread);
        communicator_references[communicator_cntr] = new_communicator;

        int index = communicator_cntr;
        int *index_ptr = &index;

        cout << "Spawning thread.." << endl;
        cout << "Thread: " << &communicators[communicator_cntr] << endl;

        pthread_create(&communicators[communicator_cntr], NULL, communicator, (void*) new_communicator);
    }

}

void terminate_communicators() {
    
    for ( int communicator_cntr = 0; communicator_cntr < NC; communicator_cntr++ ) {
        cout << "Terminating thread.." << endl;
        cout << "Thread: " << &communicators[communicator_cntr] << endl;
        pthread_join(communicators[communicator_cntr], NULL);
    }

    delete [] communicators;
    delete [] communicator_message_queues;

void *printer_main(void *PrintingTime){
    return 0;
}

void *communicator(void *arg) {

    Communicator *communicator_obj = (Communicator*) arg;
    queue<string> *message_queue = communicator_obj->message_queue;
    //communicator_message_queues[index] = message_queue;

    cout << "My Index is: " << index << endl;

    // while ( !TERMINATE ) {
    //     usleep(500);
    // }

    return 0;
}

void print_manager_init() {

    char delim[] = " ,";
    char config_data[255];

    connection_queue = new queue<int>();

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

    communicators = new pthread_t[NC];
    communicator_message_queues = new queue<string>*[NC]();
    communicator_references = new Communicator[NC]();

    cout << "Printing Time: " << PT << endl;
    cout << "Number of Communicators: " << NC << endl;
    cout << "Connection Queue Size: " << CQS << endl;
    cout << "Message Queue Size: " << MQS << endl;

    spawn_communicators();
    terminate_communicators();

    //pthread_create(&orinter, NULL, printer_main, (void*) PT);

    return;

}

void printer_manager() {
    print_manager_init();
}

int main() {
    printer_manager();
    return 0;
}