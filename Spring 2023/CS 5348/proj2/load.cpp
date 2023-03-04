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

    //load the instructions

    for ( int line_counter = 0; line_counter < Ncode + Ndata; line_counter++ ){
        fgets(line, sizeof(line), fp);
        //cout << endl;
        //cout << "Need to write: " << line << endl;
        word = strtok(line, delim);

        while(word != NULL){
            num = atoi(word);

            //cout << "Writing: " << num << " to " << ( base + prog_read_counter ) << endl;

            mem->Mem[ base + prog_read_counter ] = num;

            //cout << "Actual Contents - " << base + prog_read_counter << " : " << mem->Mem[ base + prog_read_counter ] << endl;

            prog_read_counter++;
            word = strtok(NULL, delim);
	      }
    }

    //load the data

    return fp;

}

void Loader::load_finish(FILE *f){
    fclose(f);
}
