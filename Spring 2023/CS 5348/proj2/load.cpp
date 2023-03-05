#include "computer.h"

FILE* Loader::load_prog(char *fname, int base){
    
    char delim[] = " \n";

    Memory *mem = returnMemory();

    char line[100];
    FILE *fp = fopen(fname, "r");
    if (fp) {
      if (! fgets(line, sizeof(line), fp)) {
          cout << "Error: " << fname << " doesn't exist." << endl;
          return NULL;
      }
    }

    int Ncode, Ndata;
    char *word = strtok(line, delim);
    Ncode = atoi(word);
    word = strtok(NULL, delim);
    Ndata = atoi(word);

    int num;
    int prog_read_counter = 0;

    //loading instructions
    for ( int instruction_line_counter = 0; instruction_line_counter < Ncode; instruction_line_counter++ ){
        
        fgets(line, sizeof(line), fp);
        
        word = strtok(line, delim);
        num = atoi(word);
        mem->Mem[ base + prog_read_counter ] = num;
        prog_read_counter = prog_read_counter + 1;
        
        word = strtok(NULL, delim);
        num = atoi(word);
        mem->Mem[ base + prog_read_counter ] = num;
        prog_read_counter = prog_read_counter + 1;

        word = strtok(NULL, delim);
    }

    //loading data
    for ( int data_line_counter = 0; data_line_counter < Ndata; data_line_counter++ ){
            
            fgets(line, sizeof(line), fp);
            
            word = strtok(line, delim);
            num = atoi(word);
            mem->Mem[ base + prog_read_counter ] = num;
            prog_read_counter = prog_read_counter + 1;
    }

    // //load the data

    return fp;

}

void Loader::load_finish(FILE *f){
    fclose(f);
}
