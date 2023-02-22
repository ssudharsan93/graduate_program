#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;

// prints the contents of the array, where each element
// is separated by a space and the entire array range
// is determined by the start and end values.
void print_arr_contents(int input[], int start, int end) {

    cout << "[";
    for ( int arr_counter = start; arr_counter <= end ; arr_counter++ ){
          cout << " " << input[arr_counter];
    }
    cout << " ]" << endl;

}

// Performs the ternary search
int ternary_search(int input[], int target, int start, int end) {

    cout << "\tSearching in: \t";
    print_arr_contents(input, start, end);

    // If there is only one element,
    // that element is checked against target.
    // If it is a match that element's index is
    // returned. Otherwise -1 is returned.
    if ( start == end ) {
        if ( input[start] == target ) { return start; }
        else { return -1; }
    }

    // If there are two elements,
    // both elements are checked against target.
    // If there is a match that element's index is
    // returned. Otherwise -1 is returned.
    if ( ( end - start ) == 1 ) {
        if ( input[start] == target ) { return start; }
        else if ( input[end] == target ){ return end; }
        else { return -1; }
    }

    // It calculates the partition size by
    // subtracting start from end, adding 1 and
    // dividing by 3. Then rounding to determine
    // as close to equal partition size amongst
    // all partitions.
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

    // If the target is less than the highest value
    // of the left partition then the left partition
    // is searched. If the target is more than the lowest
    // value of the right partition then the right partition
    // is searched. Otherwise the middle partition is searched.
    if ( target >= input[upper] ) {
        return ternary_search(input, target, upper, end); // check upper partition
    }
    else if ( target <= input[lower] ) {
        return ternary_search(input, target, start, lower); // check lower partition
    }
    else {
        return ternary_search(input, target, lower + 1, upper - 1); // check middle partition
    }

    return -1;
}

int main() {

    cout << endl;
    cout << "################################################" << endl;
    cout << "Ternary Search:" << endl;
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
    found_index = ternary_search(input_arr1, 17, 0, 10);
    cout << "\tIndex of element: " << found_index << endl;
    cout << endl;

    cout << endl;
    cout << "\tSearching for " << 83 << " in ";
    print_arr_contents(input_arr1, 0, 10);
    cout << "\tSize of array: " << 11 << endl;
    cout << endl;
    found_index = ternary_search(input_arr1, 83, 0, 10);
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
    found_index = ternary_search(input_arr2, 23, 0, 14);
    cout << "\tIndex of element: " << found_index << endl;
    cout << endl;

    cout << endl;
    cout << "\tSearching for " << 52 << " in ";
    print_arr_contents(input_arr2, 0, 14);
    cout << "\tSize of array: " << 15 << endl;
    cout << endl;
    found_index = ternary_search(input_arr2, 52, 0, 14);
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
    found_index = ternary_search(input_arr3, 23, 0, 11);
    cout << "\tIndex of element: " << found_index << endl;
    cout << endl;

    cout << endl;
    cout << "\tSearching for " << 59 << " in ";
    print_arr_contents(input_arr3, 0, 11);
    cout << "\tSize of array: " << 12 << endl;
    cout << endl;
    found_index = ternary_search(input_arr3, 59, 0, 11);
    cout << "\tIndex of element: " << found_index << endl;
    cout << endl;
    cout << "\t----------------------------------" << endl;
    cout << endl;

}
