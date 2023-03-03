#ifndef PRINTER_H
#define PRINTER_H

#include <map>

using namespace std;

void send_response(int printer_write, string response);
void print_spool_to_printout(FILE *spool_fp, FILE *printer_fp, int PID, string footer);
FILE* printer_init(int printer_write);
FILE* printer_init_spool(int PID);
void printer_end_spool(int PID, FILE *spool_fp, FILE *printer_fp);
void printer_dump_spool(map<int, FILE*> *file_descr_struct);
void printer_print(string buffer, FILE *spool_fp);
void printer_terminate(map<int, FILE*> *file_desc_struct, FILE *printer_fp);
void printer_main(int PrinterTime);

#endif PRINTER_H