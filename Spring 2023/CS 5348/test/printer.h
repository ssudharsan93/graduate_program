#ifndef PRINTER_H
#define PRINTER_H

#include <iostream>
#include <fstream>
#include <queue>
#include <string>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <mutex>

using namespace std;

class Communicator {
private:
    int index;
    queue<string> *message_queue;
    mutex msg_queue_prot;
public:
    Communicator();
    ~Communicator();
    int get_index();
    void set_index(int index);
    void init_message_queue();
    void enqueue_message(string msg);
    string dequeue_message();
    int get_queue_size();
    bool is_queue_empty();
};

Communicator **communicators;
pthread_t *communicator_tids;
pthread_t printer;
queue<int> *connection_queue;

sem_t sync_pc;
mutex conn_queue_prot;

void spawn_communicators();
void terminate_communicators();
void *printer_main(void *PrintingTime);
void *communicator(void *arg);
int get_connection();
void print_manager_init();
void printer_manager();

#endif PRINTER_H