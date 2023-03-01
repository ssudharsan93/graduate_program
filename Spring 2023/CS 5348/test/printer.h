#ifndef PRINTER_H
#define PRINTER_H

#include <unordered_map>

using namespace std;

FILE* printer_init();
FILE* printer_init_spool(int PID);
void printer_end_spool(FILE *spool_fp, FILE *printer_fp);
void printer_dump_spool(unordered_map<int, FILE*> *file_descr_struct);
void printer_print(string buffer, FILE *spool_fp);
void printer_terminate();
void printer_main();

#endif PRINTER_H