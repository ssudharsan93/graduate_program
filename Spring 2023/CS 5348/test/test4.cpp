#include "test3.h";

void printer_init() {
    
    char ACK[] = "ACK";
    write(printer_write, ACK, sizeof(ACK));

}
void printer_init_spool()
void printer_end_spool()
void printer_dump_spool()
void printer_print()
void printer_terminate()

void printer_main() {
    printer_init();

    close(printer_read);
    close(printer_write);

}