#ifndef PRINTER_MANAGER_H
#define PRINTER_MANAGER_H

#include <iostream>
#include <fstream>
#include <queue>
#include <pthread.h>

pthread_t *communicators;
pthread_t printer;
queue<int> *connection_queue;

#endif PRINTER_MANAGER_H