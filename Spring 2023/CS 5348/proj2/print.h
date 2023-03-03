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

#include "printer.h"

extern int printer_read;
extern int print_read;
extern int printer_write;
extern int print_write;

extern pid_t pid;

void send_instruction(string instruction, int PID, string msg);
void print_init(int PrintingTime);
void print_init_spool(int PID);
void print_end_spool(int PID);
void print_print(char buffer[], int PID);
void print_terminate();
void test_print_component();

#endif PRINT_H