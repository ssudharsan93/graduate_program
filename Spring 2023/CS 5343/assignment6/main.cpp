#include <iostream>
#include <fstream>
#include <algorithm>
#include "HashTable.h"

using namespace std;

string* read_words_from_input_file(){

    string *input = new string[20]();

    fstream input_fp;

    input_fp.open("input.txt", ios::in);

    if (input_fp.is_open()){ 
        string input_word;
        for ( int input_count = 0; input_count < 20; input_count++ ) {
            getline(input_fp, input_word);

            int carriage_return_index = input_word.find('\r');
            int newline_index = input_word.find('\r');

            if ( carriage_return_index < input_word.size() ){ 
                input_word.erase( carriage_return_index + input_word.begin()); 
            }
            
            if ( newline_index < input_word.size() ) {
                input_word.erase(newline_index + input_word.begin());
            }

            // cout << "Carriage Return Index : " << input_word.find('\r') << endl;
            // cout << "Newline Index : " << input_word.find('\n') << endl;
            
            input[input_count] = input_word;
        }
    }

    input_fp.close(); //close the file object.

    return input;
}

void insert_words_to_hash_table(HashTable *dataset){
    string *words = read_words_from_input_file();

    cout << "#########################################" << endl;
    cout << "       Initial State" << endl;
    cout << "#########################################" << endl;
    
    cout << endl;
    dataset->print_hash_table();
    cout << endl;

    cout << "#########################################" << endl;


    cout << endl;
    for ( int words_cntr = 0; words_cntr < 20; words_cntr++ ){
        dataset->insert_element(words[words_cntr]);
    }
    cout << endl;


    cout << "#########################################" << endl;
    cout << "       Solution Information" << endl;
    cout << "#########################################" << endl;
    
    cout << endl;
    dataset->print_hash_table();
    cout << endl;

    cout << endl;
    cout << "\t------------------------------------------" << endl;
    cout << "\tNum of Collisions that occurred: " << dataset->get_num_collisions() << endl;
    cout << "\t------------------------------------------" << endl;
    cout << endl;

    cout << endl;
    cout << "\t------------------------------------------" << endl;
    cout << "\tCurrent Load Factor: " << dataset->get_load_factor() << endl;
    cout << "\t------------------------------------------" << endl;
    cout << endl;

    cout << "#########################################" << endl;

}

int main() {

    HashTable *my_hash_table = new HashTable();
    insert_words_to_hash_table(my_hash_table);

}
