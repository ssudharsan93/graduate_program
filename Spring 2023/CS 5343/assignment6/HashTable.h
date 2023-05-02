#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <string>
#include <cmath>

using namespace std;

class HashTable {
private:
    string *table;
    int num_elements = 0;
    float rehash_load_factor = 0.5;
    int size = 31;
    int num_of_collisions = 0;
    
public:
    HashTable();
    void insert_element(string new_string);
    void delete_element(string string_to_delete);
    int find_element(string key);
    void rehash();
    int get_hash(string key);
    int get_num_elements();
    int get_size();
    void set_size(int new_size);
    void print_hash_table();
    float get_load_factor();
    int get_collision_resolution_index(int current_hash_val);
    int get_num_collisions();
    void increment_num_collisions();
    int get_next_table_size();
    bool is_prime(int potential_prime_num);
};

#endif HASHTABLE_H
