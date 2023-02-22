#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "ListNode.h"

using namespace std;

void print_arr_contents(int input[], int start, int end) {

    cout << "[";
    for ( int arr_counter = start; arr_counter <= end ; arr_counter++ ){
          cout << " " << input[arr_counter];
    }
    cout << " ]" << endl;

}

int tertiary_search(int input[], int target, int start, int end) {

    cout << "\tSearching in: \t";
    print_arr_contents(input, start, end);

    if ( start == end ) {
        if ( input[start] == target ) { return start; }
        else { return -1; }
    }

    if ( ( end - start ) == 1 ) {
        if ( input[start] == target ) { return start; }
        else if ( input[end] == target ){ return end; }
        else { return -1; }
    }

    int size = round( ( end - start + 1.0 ) / 3.0 );
    int upper, lower;

    lower = start + size - 1;
    upper = end - size + 1;

    cout << "\tLeft partition: \t";
    print_arr_contents(input, start, lower);
    cout << "\tMiddle partition: \t";
    print_arr_contents(input, lower + 1, upper - 1);
    cout << "\tRight partition: \t";
    print_arr_contents(input, upper, end);
    cout << endl;

    if ( target >= input[upper] ) {
        return tertiary_search(input, target, upper, end); // check upper partition
    }
    else if ( target <= input[lower] ) {
        return tertiary_search(input, target, start, lower); // check lower partition
    }
    else {
        return tertiary_search(input, target, lower + 1, upper - 1); // check middle partition
    }

    return -1;
}

void perf_tertiary_search() {

    cout << endl;
    cout << "################################################" << endl;
    cout << "Tertiary Search portion:" << endl;
    cout << "################################################" << endl;
    cout << endl;

    int found_index;

    int input_arr1[11] = {
        20, 29, 31, 40, 51,
        53, 55, 59, 63, 83,
        90
    };

    int input_arr2[15] = {
        1, 4, 15, 18, 19,
        20, 21, 23, 28, 43,
        56, 64, 66, 69, 80
    };


    int input_arr3[12] = {
        4, 10, 19, 25, 28,
        33, 39, 43, 49, 59,
        89, 100
    };

    cout << "\tDataset 1" << endl;
    cout << "\t----------------------------------" << endl;
    cout << "\tSearching for " << 17 << " in ";
    print_arr_contents(input_arr1, 0, 10);
    cout << "\tSize of array: " << 11 << endl;
    cout << endl;
    found_index = tertiary_search(input_arr1, 17, 0, 10);
    cout << "\tIndex of element: " << found_index << endl;
    cout << endl;

    cout << endl;
    cout << "\tSearching for " << 83 << " in ";
    print_arr_contents(input_arr1, 0, 10);
    cout << "\tSize of array: " << 11 << endl;
    cout << endl;
    found_index = tertiary_search(input_arr1, 83, 0, 10);
    cout << "\tIndex of element: " << found_index << endl;
    cout << endl;
    cout << "\t----------------------------------" << endl;
    cout << endl;

    cout << "\tDataset 2" << endl;
    cout << "\t----------------------------------" << endl;
    cout << "\tSearching for " << 23 << " in ";
    print_arr_contents(input_arr2, 0, 14);
    cout << "\tSize of array: " << 15 << endl;
    cout << endl;
    found_index = tertiary_search(input_arr2, 23, 0, 14);
    cout << "\tIndex of element: " << found_index << endl;
    cout << endl;

    cout << endl;
    cout << "\tSearching for " << 52 << " in ";
    print_arr_contents(input_arr2, 0, 14);
    cout << "\tSize of array: " << 15 << endl;
    cout << endl;
    found_index = tertiary_search(input_arr2, 52, 0, 14);
    cout << "\tIndex of element: " << found_index << endl;
    cout << endl;
    cout << "\t----------------------------------" << endl;
    cout << endl;

    cout << "\tDataset 3" << endl;
    cout << "\t----------------------------------" << endl;
    cout << "\tSearching for " << 23 << " in ";
    print_arr_contents(input_arr3, 0, 11);
    cout << "\tSize of array: " << 12 << endl;
    cout << endl;
    found_index = tertiary_search(input_arr3, 23, 0, 11);
    cout << "\tIndex of element: " << found_index << endl;
    cout << endl;

    cout << endl;
    cout << "\tSearching for " << 59 << " in ";
    print_arr_contents(input_arr3, 0, 11);
    cout << "\tSize of array: " << 12 << endl;
    cout << endl;
    found_index = tertiary_search(input_arr3, 59, 0, 11);
    cout << "\tIndex of element: " << found_index << endl;
    cout << endl;
    cout << "\t----------------------------------" << endl;
    cout << endl;

}

int main() {

    int LIST_SIZE = 15;

    ListNode *head = NULL;

    int new_elem;
    ListNode* curr_elem;

    srand(time(NULL));

    for (int populate_ctr = 0; populate_ctr < LIST_SIZE; populate_ctr++ ) {
        new_elem = rand() % 100 + 1;

        if (head == NULL) {
            head = new ListNode( new_elem );
            curr_elem = head;
        }

        else {
            ListNode* new_node = new ListNode( new_elem );
            curr_elem->set_next(new_node);
            curr_elem = new_node;

        }
    }

    cout << endl;
    cout << "################################################" << endl;
    cout << "List Node Bubble Sort portion:" << endl;
    cout << "################################################" << endl;
    cout << endl;

    cout << "\tOriginal: " << endl;
    cout << "\t\t";
    head->print_values();
    cout << endl;

    head = bubble_sort(head, LIST_SIZE);

    cout << "\tSorted: " << endl;
    cout << "\t\t";
    head->print_values();

    cout << endl;
    cout << endl;

    perf_tertiary_search();

}
