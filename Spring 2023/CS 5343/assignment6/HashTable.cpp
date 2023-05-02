#include "HashTable.h"

HashTable::HashTable(){
    this->table = new string[31]();
}

void HashTable::insert_element(string new_elem){
    this->num_elements = this->num_elements + 1;
    int hash_val = this->get_hash(new_elem);

    if ( this->get_load_factor() > this->rehash_load_factor ){
        cout << endl;
        cout << endl;
        cout << "Need to Rehash." << endl;
        this->rehash();
        cout << endl;
        cout << endl;
    }

    if ( this->table[hash_val] == "" ) { 
        cout << "Inserting: '" << new_elem << "' at -> " << hash_val << endl;
        this->table[hash_val] = new_elem;
    
    } else {

        cout << endl;
        cout << "Collision occurred. Need to Resolve." << endl;
        this->increment_num_collisions();
        hash_val = this->get_collision_resolution_index(hash_val);
        cout<< endl;

        cout << "Inserting: '" << new_elem << "' at Resolved val -> " << hash_val << endl;
        this->table[hash_val] = new_elem;
    }
}

void HashTable::delete_element(string string_to_delete){
    this->num_elements = this->num_elements - 1;
}

int HashTable::find_element(string key){
}

void HashTable::rehash(){

    int old_table_size = this->get_size();
    int new_table_size = this->get_next_table_size();
    cout << "New Hash Size Will Be: " << new_table_size << endl;

    string* old_table = this->table;
    string* new_table = new string[new_table_size]();
    
    this->table = new_table;
    this->set_size(new_table_size);
    this->num_elements = 0;

    for ( int table_cntr = 0; table_cntr < old_table_size; table_cntr++ ){
        string elem_to_relocate = old_table[table_cntr];
        if ( elem_to_relocate == "" ){ continue; }
        else { this->insert_element(elem_to_relocate); }
    }

    //delete old_table;
}

int HashTable::get_hash(string key){
    int table_size = this->get_size();
    int key_size = key.size();

    int calculated_hash_for_key = 0;

    for ( int key_cntr = 0; key_cntr < key_size; key_cntr++ ){
        calculated_hash_for_key = calculated_hash_for_key + (int) key[key_cntr];
        calculated_hash_for_key = 37^(key_cntr) * calculated_hash_for_key; 
    }

    calculated_hash_for_key = calculated_hash_for_key % table_size;

    if ( calculated_hash_for_key < 0 ) {
        calculated_hash_for_key = calculated_hash_for_key + table_size;
    }

    return calculated_hash_for_key; 
}

int HashTable::get_num_elements(){
    return this->num_elements;
}

int HashTable::get_size(){
    return this->size;
}

void HashTable::set_size(int new_size){
    this->size = new_size;
}

void HashTable::print_hash_table() {

    cout << "\t==========================================" << endl;
    cout << "\t         Current Hash Table: " << endl;
    cout << "\t==========================================" << endl;

    int table_size = this->get_size();

    for ( int table_cntr = 0; table_cntr < table_size; table_cntr++ ){
        cout << "\t" << table_cntr << " -> " << this->table[table_cntr] << endl;
    }

    cout << "\t==========================================" << endl;

}

float HashTable::get_load_factor() {
    return ( 1.0 * this->get_num_elements() ) / ( 1.0 * this->get_size() );
}

int HashTable::get_collision_resolution_index(int current_hash_val) {
    int resolved_hash_val = current_hash_val;
    int offset = 1;

    while ( this->table[resolved_hash_val] != "" ){
        resolved_hash_val = ( current_hash_val + ( offset^2 ) ) % this->get_size();
        
        if ( this->table[resolved_hash_val] != "" ){
            cout << "Collision reoccurred. Need to Resolve." << endl;
            this->increment_num_collisions();
        }

        offset = offset + 1;
    }

    return resolved_hash_val;
}

int HashTable::get_num_collisions() {
    return this->num_of_collisions;
}

void HashTable::increment_num_collisions() {
    this->num_of_collisions++;
}

int HashTable::get_next_table_size() {
    int curr_table_size = this->get_size();
    int potential_new_table_size = curr_table_size * 2;

    while ( ! is_prime(potential_new_table_size) ) {
        potential_new_table_size = potential_new_table_size + 1;
    }

    return potential_new_table_size;
}

bool HashTable::is_prime(int potential_prime_num){
    int prime_cntr_limit = ceil( ( potential_prime_num * 1.0 ) / 2.0);
    
    for ( int prime_check_cntr = 2; prime_check_cntr < prime_cntr_limit; prime_check_cntr++ ){
        if ( potential_prime_num % prime_check_cntr == 0 ) { 
            return false; 
        }
    }

    return true;
}