/****************************************
*
* Math Manipulation
* Sudharsan Sundaravenkataraman
* The University of Texas at Dallas
* Homework #2
* September 12, 2022
* Macbook
* g++ compiler
* Study Group:
* Study Group Members:
*
****************************************/

// Include Library Header Files
#include <iostream>
#include <math.h>

// Use the STD Namespace
using namespace std;

//Prototypes
//List of functions in this file
//With the correct parameters
//And with the correct return types
void menu();
void output_name();
void clear_data(double input_array[], int length);
void input_data(double input_array[], int length);
void show_data(double input_array[], int length);
void find_min(double input_array[], int length);
void find_max(double input_array[], int length);
double find_total(double input_array[], int length);
double find_average(double input_array[], int length);
double find_variance(double input_array[], int length);
double find_standard_deviation(double input_array[], int length);


// There is always a Main function to begin the program in C++.
int main()
{
    output_name();
    menu();

    return 0;
}

/*
*  Function output_name
*  Parameter List: empty
*  Return: void
*  Description:
*    The getchar command will return nothing until the enter key is pressed.
*	 Nothing is called NULL in C++
*    The while statement will continue forever until the expression becomes false.
*
*  While "Nothing Happens" keep waiting.
*
* Once something happens, function pause ends.
*
*/

void output_name() {

  cout << "Sudharsan Sundaravenkataraman" << endl;
  cout << "CS5303-001" << endl;
  cout << "September 12, 2022" << endl;
  cout << "=========" << endl;

}

/*
*  Function Menu
*  Parameter List: empty
*  Return: void
*  Description:
*    The getchar command will return nothing until the enter key is pressed.
*	 Nothing is called NULL in C++
*    The while statement will continue forever until the expression becomes false.
*
*  While "Nothing Happens" keep waiting.
*
* Once something happens, function pause ends.
*
*/
void menu() {

    double user_array[5] = {0, 0, 0, 0, 0};
    int length = 5;
    bool user_not_terminated = true;

    while (user_not_terminated) {
        cout << "0. Clear Data" << endl;
        cout << "1. Input Data" << endl;
        cout << "2. Show Data" << endl;
        cout << "3. Find Min" << endl;
        cout << "4. Find Max" << endl;
        cout << "5. Total" << endl;
        cout << "6. Average" << endl;
        cout << "7. Variance" << endl;
        cout << "8. Standard Deviation" << endl;
        cout << "9. Quit" << endl;
        cout << "--------------" << endl;

        int user_decision;

        cin >> user_decision;

        switch (user_decision) {
            case 0 :
                clear_data(user_array, length);
                break;
            case 1 :
                input_data(user_array, length);
                break;
            case 2 :
                show_data(user_array, length);
                break;
            case 3 :
                find_min(user_array, length);
                break;
            case 4 :
                find_max(user_array, length);
                break;
            case 5 :
                find_total(user_array, length);
                break;
            case 6 :
                find_average(user_array, length);
                break;
            case 7 :
                find_variance(user_array, length);
                break;
            case 8 :
                find_standard_deviation(user_array, length);
                break;
            case 9 :
                user_not_terminated = false;
                break;
            default :
                cout << "Invalid Input. Try Again";
                break;
        }
    }
}

void clear_data(double input_array[], int length) {

    int index;
    for ( index = 0; index < length; index++ ) {
        input_array[index] = 0;
    }

    return;
}

void input_data(double input_array[], int length) {

    int index;
    double current_val;

    cout << "Please enter 5 floating point numbers, follow each number with an enter" << endl;
    for ( index = 0; index < length; index++ ) {
        cin >> current_val;
        input_array[index] = current_val;
    }

    return;
}

void show_data(double input_array[], int length) {

    int index;

    for ( index = 0; index < length; index++ ) {
        cout << input_array[index] << endl;
    }

    return;
};

void find_min(double input_array[], int length) {

    int index;
    double min_of_array = input_array[0];

    for ( index = 0; index < length; index++ ) {
        if ( min_of_array > input_array[index] ) {
            min_of_array = input_array[index];
        }
    }

    cout << "The minimum is " << min_of_array << endl;

    return;
};

void find_max(double input_array[], int length) {

    int index;
    double max_of_array = input_array[0];

    for ( index = 0; index < length; index++ ) {
        if ( max_of_array < input_array[index] ) {
            max_of_array = input_array[index];
        }
    }

    cout << "The maximum is " << max_of_array << endl;

    return;
};

double find_total(double input_array[], int length) {

    int index;
    double total_of_array = 0;

    for ( index = 0; index < length; index++ ) {
        total_of_array = total_of_array + input_array[index];
    }

    cout << "The Total is " << total_of_array << endl;

    return total_of_array;
};

double find_average(double input_array[], int length) {

    double total_of_array;
    double average_of_array;

    total_of_array = find_total(input_array, length);
    average_of_array = total_of_array / length;

    cout << "The Average is " << average_of_array << endl;

    return average_of_array;
};

double find_variance(double input_array[], int length) {

    int index;

    double average_of_array;
    double variance_of_array;

    double current_item;
    double squared_displacement;
    double sum_of_displacements_squared = 0;

    average_of_array = find_average(input_array, length);

    for ( index = 0; index < length; index++ ) {
        current_item = average_of_array - input_array[index];
        squared_displacement = current_item * current_item;
        sum_of_displacements_squared = sum_of_displacements_squared + squared_displacement;
    }

    variance_of_array = sum_of_displacements_squared / length;

    cout << "The variance is " << variance_of_array << endl;

    return variance_of_array;
};

double find_standard_deviation(double input_array[], int length) {

    double variance_of_array;
    double standard_deviation_of_array;

    variance_of_array = find_variance(input_array, length);

    standard_deviation_of_array = sqrt(variance_of_array);

    cout << "The standard deviation is " << standard_deviation_of_array << endl;

    return standard_deviation_of_array;
};
