#ifndef PRINTER_MANAGER_H
#define PRINTER_MANAGER_H

#include <iostream>
#include <fstream>
#include <queue>
#include <string>
#include <pthread.h>
#include <unistd.h>

using namespace std;

class Communicator {
private:
    pthread_t tid;
public:
    queue<string> *message_queue;
    Communicator();
    pthread_t get_tid();
    void set_tid();
    void init_message_queue();
};

pthread_t *communicators;
Communicator *communicator_references;
pthread_t printer;
queue<int> *connection_queue;
queue<string> **communicator_message_queues;

void spawn_communicators();
void terminate_communicators();
void *printer_main(void *PrintingTime);
void *communicator(void *arg);
void print_manager_init();
void printer_manager();

#endif PRINTER_MANAGER_H