#include "print.h"

int PrintingTimeSystemParameter;
bool TERMINATE_PRINTER;

void send_response(string response) {
    
    char resp[response.size() + 1];
    strcpy(resp, response.c_str());
    write(printer_write, resp, sizeof(resp));
    fsync(printer_write);
    
}

void print_spool_to_printout(FILE *spool_fp, FILE *printer_fp, int PID, string footer){

    char line[100];

    fseek(spool_fp, 0, SEEK_SET);

    while ( fgets(line, sizeof(line), spool_fp) ){
        usleep(PrintingTimeSystemParameter);
        fputs(line, printer_fp);
    }

    string separator =    "--------------------\n";
    string process_footer = separator + footer + separator;

    char close_msg[process_footer.size() + 1];
    strcpy(close_msg, process_footer.c_str());
    usleep(PrintingTimeSystemParameter);
    fputs(close_msg, printer_fp);

    fclose(spool_fp);

    string fname;
    string file_header = "pid";
    string process_id = to_string(PID);
    string file_footer = "_spool.txt";

    fname = file_header + process_id + file_footer;

    char spool_fname[fname.size() + 1];
    strcpy(spool_fname, fname.c_str());

    cout << "Removing " << fname << "..." << endl;

    remove(spool_fname);

}

//Initialize the printer, including opening the simulated printing paper, i.e., the “printer.out” file.
//Sends an ACK to the print component to indicate that the initialization is done.
FILE* printer_init() {

    FILE *fp = NULL;
    string ACK = "ACK";

    send_response(ACK);

    fp = fopen("printer.out", "w");
    return fp;

}

//Opening a spool file for the process.
//You can use PID to differentiate the spool file names.
FILE* printer_init_spool(int PID){

    FILE *fp = NULL;
    string fname;
    string header = "pid";
    string footer = "_spool.txt";

    string process_id = to_string(PID);
    fname = header + process_id + footer;
    cout << fname << endl;

    char spool_fname[fname.size() + 1];
    strcpy(spool_fname, fname.c_str());

    fp = fopen(spool_fname, "w+");
    
    string separator =    "--------------------\n";
    string process_str =  "     Process: " + to_string(PID) + "\n";
    string process_header = separator + process_str + separator;
    char init_msg[process_header.size() + 1];
    strcpy(init_msg, process_header.c_str());

    fputs(init_msg, fp);

    string return_msg = "Init Spool Finish";

    send_response(return_msg);

    return fp;

}

//The printer prints the contents in the spool file of the process to the simulated paper and close the spool file.
void printer_end_spool(int PID, FILE *spool_fp, FILE *printer_fp){
    
    cout << "End Spool Start" << endl;

    string footer =  "     End Process: " + to_string(PID) + "\n";
    print_spool_to_printout(spool_fp, printer_fp, PID, footer);

    string return_msg = "End Spool Finish";

    send_response(return_msg);

    return;

}

void printer_dump_spool(map<int, FILE*> *file_desc_struct){
    
    auto f_desc_struct_begin = file_desc_struct->begin();
    auto f_desc_struct_end = file_desc_struct->end();
    int PID;

    cout << "===========================" << endl;
    cout << "      Printer Dump         " << endl;
    cout << "===========================" << endl;
    cout << "Index: PID" << endl;

    int index = 0;

    for ( auto f_desc_struct_it = f_desc_struct_begin; f_desc_struct_it != f_desc_struct_end; ++f_desc_struct_it ) {
        PID = f_desc_struct_it->first;
        cout << index << ":" << PID << endl;
    }

    string return_msg = "Dump Spool Finish";
    send_response(return_msg);

}

//This function is for handling the regular print instructions.
//It should determine which spool file to use and writes the to-be-printed content to the spool file.
void printer_print(char buffer[], FILE *spool_fp){

    fputs(buffer, spool_fp);
    fputs("\n", spool_fp);

    string return_msg = "Print Spool Finish";

    send_response(return_msg);

    return;

}

//For any process that has not terminated, print its partial output in its spool file
//to the simulated paper, and add a message at the end to indicate that the process did
//not finish yet. Then, clean up and terminate the printer process.
void printer_terminate(map<int, FILE*> *file_desc_struct, FILE *printer_fp){
    
    TERMINATE_PRINTER = true;

    auto f_desc_struct_begin = file_desc_struct->begin();
    auto f_desc_struct_end = file_desc_struct->end();
    int PID;
    FILE *spool_fp;

    for ( auto f_desc_struct_it = f_desc_struct_begin; f_desc_struct_it != f_desc_struct_end; ++f_desc_struct_it ) {
        PID = f_desc_struct_it->first;
        spool_fp = f_desc_struct_it->second;

        string footer =  "     Process: " + to_string(PID) + " Terminated without Completion.\n";
        print_spool_to_printout(spool_fp, printer_fp, PID, footer);
    }

    string return_msg = "Term Completed";
    send_response(return_msg);


}

//This is the printer main function. It calls printer_init() to initialize the printer
//and then waits on the pipe. Once a message is received,
//it analyzes the message and determines the function to call.
//SPL is SPOOL INIT
//END is SPOOL END
//PRT is PRINT
//TRM is TERMINATE
void printer_main(int PrintingTime) {

    PrintingTimeSystemParameter = PrintingTime;
    TERMINATE_PRINTER = false;

    char SPL[] = "SPL";
    char END[] = "END";
    char PRT[] = "PRT";
    char DMP[] = "DMP";
    char TRM[] = "TRM";

    char CMD[100];
    char buffer[100];

    char *message;
    int PID;

    FILE *fp = NULL;
    FILE *printer_out_fp = NULL;

    map<int, FILE*> *file_desc_struct = new map<int, FILE*>();

    char *command = NULL;

    char delim[] = ",";
    
    printer_out_fp = printer_init();

    while ( !TERMINATE_PRINTER ) {

        read(printer_read, CMD, sizeof(CMD));
        
        message = strtok(CMD, delim);
        command = message;
        message = strtok(NULL, delim);
        PID = atoi(message);

        if ( strcmp(command, SPL) == 0 ) {
            fp = printer_init_spool(PID);

            auto file_desc_struct_it = file_desc_struct->find(PID);
        
            if ( file_desc_struct_it == file_desc_struct->end() ) {
                pair<int, FILE*> pid_file_desc_pair = make_pair(PID, fp);
                file_desc_struct->insert(pid_file_desc_pair);
            }
        } 
        
        else if ( strcmp(command, END) == 0 ) {
            fp = file_desc_struct->at(PID);
            printer_end_spool(PID, fp, printer_out_fp);
            file_desc_struct->erase(PID);

        } 
        
        else if ( strcmp(command, PRT) == 0 ) {
            message = strtok(NULL, delim);
            cout << message << endl;
            fp = file_desc_struct->at(PID);
            printer_print(message, fp);
        } 

        else if ( strcmp(command, DMP) == 0 ) {
            printer_dump_spool(file_desc_struct);
        }
        
        else if ( strcmp(command, TRM) == 0 ) {
            printer_terminate(file_desc_struct, printer_out_fp);
            fclose(printer_out_fp);

        } 

        else {
            cout << "Unknown CMD";
        }
    }

}