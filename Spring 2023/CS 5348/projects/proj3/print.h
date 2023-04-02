#ifndef PRINT_H
#define PRINT_H

#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <fcntl.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>

using namespace std;

void send_instruction(string instruction, string CID_PID, string msg);
void print_init();
void print_init_spool(int PID);
void print_end_spool(int PID);
void print_print(char buffer[], int PID);
void print_dump_spool();
void print_terminate();
void test_print_component();

#endif PRINT_H