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
#include <signal.h>
#include <errno.h>
#include <cstdio>
#include <cstring>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <map>

using namespace std;

class Communicator {
private:
    int index;
    int bin_selector;
    bool terminate_flag = false;
    queue<string> *message_queue;
    mutex msg_queue_prot;
public:
    Communicator();
    ~Communicator();
    int get_index();
    void set_index(int index);
    int get_bin_selector();
    void set_bin_selector(int bin_selector);
    bool get_terminate_flag();
    void set_terminate_flag();
    void init_message_queue();
    void enqueue_message(string msg);
    string dequeue_message();
    int get_queue_size();
    bool is_queue_empty();
};

// Printer Methods
void send_response(int printer_write, string response);
void print_spool_to_printout(string CID, string PID, string footer, map<string, FILE*> *file_desc_struct);
void printer_init(string CID, string PID, map<string, FILE*> *file_desc_struct);
void printer_init_spool(string CID, string PID, map<string, FILE*> *file_desc_struct);
void printer_end_spool(string CID, string PID, map<string, FILE*> *file_desc_struct);
void printer_dump_spool(map<string, FILE*> *file_desc_struct);
void printer_print(string CID, string PID, map<string, FILE*> *file_desc_struct);
void printer_terminate(string CID, map<string, FILE*> *file_desc_struct);
int exec_printer_cmd(string cmd, string CID_PID, string data, map<string, FILE*> *file_desc_struct);
int service_cmd(string msg, map<string, FILE*> *file_desc_struct);

bool is_bit_set(int bin_number, int bit_index);
int clear_bit(int bin_number, int bit_index);
int set_bit(int bin_number, int bit_index);

// Semaphore Methods
void initialize_semaphores();
void close_semaphores();

// Thread Spawning and Termination Methods
void spawn_printer();
void terminate_printer();
void spawn_communicators();
void terminate_communicators();


// Main Thread Methods
void *printer_main(void *PrintingTime);
void *communicator(void *arg);

// System methods
int get_connection();
void read_and_set_sys_params();
void ctrl_c_signal_callback_handlr(int signum);
void print_manager_init();
void printer_manager();

// Test Critical Section Methods
void test_NQ(Communicator *comm_obj, string msg);
void test_DQ();

#endif PRINTER_H