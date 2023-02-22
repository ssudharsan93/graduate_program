/****************************************
*
* File and Formatting
* Sudharsan Sundaravenkataraman
* The University of Texas at Dallas
* Homework #3
* October 8, 2022
* Macbook
* g++ compiler
* Study Group:
* Study Group Members:
*
****************************************/

// Include Library Header Files
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <cmath>

// Use the STD Namespace
using namespace std;

//Prototypes
//List of functions in this file
//With the correct parameters
//And with the correct return types
void menu();
void output_name();
vector<int> load_from_a_file(vector<int> data_vector);
void calculate_the_statistics(vector<int> data_vector);
vector<int> perform_the_count(vector<int> data_vector, vector<int> counting_vector);
void show_the_count(vector<int> counting_vector);
void display_the_bar_graph(vector<int> counting_vector);
void display_the_bar_graph_vertically(vector<int> counting_vector);
//List of functions corresponding to performing
//calculations, with the correct parameters,
//and with the correct return types.
double find_total(vector<int> input_vector);
double find_average(vector<int> input_vector);
double find_variance(vector<int> input_vector);
double find_standard_deviation(vector<int> input_vector);
int Normalization(vector<int> input_data, int index);

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
*    This method just prints my name, the class, and the date.
*
*/

void output_name() {

  cout << "Sudharsan Sundaravenkataraman" << endl;
  cout << "CS5303-001" << endl;
  cout << "October 08, 2022" << endl;
  cout << "=========" << endl;

}

/*
*  Function Menu
*  Parameter List: empty
*  Return: void
*  Description:
*    The cin command will return nothing until the enter key is pressed.
*    The while statement will continue forever until the expression becomes false.
*    The options for the menu include:
*        1. Clearing the application / vectors.
*        2. Loading the values from Sealife.txt .
*        3. Calculating the total, average, variance and
*           standard deviation.
*        4. Performing the count of distinct elements.
*        5. Showing the count of each distinct element.
*        6. Displaying a bargraph which illustrates counts of
*           distinct elements.
*        7. Quit the program.
*        8. Display the bargraph vertically, with Xs now in the
*           Y-axis of the graph.
*
*    While "Nothing Happens" keep waiting.
*
* Once something happens, function pause ends.
*
*/
void menu() {

    bool user_not_terminated = true;
    vector<int> data_vector;
    vector<int> counting_vector(17);
    vector<int> zero_vector(17,0);

    while (user_not_terminated) {
        cout << "1. Clear the Application" << endl;
        cout << "2. Load From a File" << endl;
        cout << "3. Calculate The Statistics" << endl;
        cout << "4. Perform the Count" << endl;
        cout << "5. Show the Count" << endl;
        cout << "6. Display the Bargraph" << endl;
        cout << "7. Quit" << endl;
        cout << "8. Display the Bargraph Vertically" << endl;
        cout << "--------------" << endl;

        int user_decision;

        cin >> user_decision;

        switch (user_decision) {
            case 1 :
                data_vector.clear();
                counting_vector = zero_vector;
                cout << endl;
                break;
            case 2 :
                data_vector = load_from_a_file(data_vector);
                break;
            case 3 :
                calculate_the_statistics(data_vector);
                break;
            case 4 :
                counting_vector = perform_the_count(data_vector, counting_vector);
                break;
            case 5 :
                show_the_count(counting_vector);
                break;
            case 6 :
                display_the_bar_graph(counting_vector);
                break;
            case 7 :
                user_not_terminated = false;
                break;
            case 8 :
                display_the_bar_graph_vertically(counting_vector);
                break;
            default :
                cout << "Invalid Input. Try Again";
                break;
        }
    }
}


/*
* Function calculate_the_statistics
* Parameters:
*    vector<int> data_vector- a vector containing integer values
* Return: vector<int> - all of the comma separated values from Sealife.txt
*                       loaded into the vector, having ignored the comma
*                       characters.
* Description:
*    This method takes in data_vector, and reads integer values from
*    the Sealife.txt file into data_vector while ignoring comma characters.
*/
vector<int> load_from_a_file(vector<int> data_vector) {

    string filename = "Sealife.txt";
    int current_int;
    char comma;

    ifstream input_file;
    input_file.open(filename);

    //If the input file is not found, or the file is unable to be opened.
    //The method will return an empty vector<int>
    if (!input_file) {
      cout << "Unable to open file. Check project directory. Vector returned will be empty" << endl;
      return data_vector;
    }

    while ( !input_file.eof() ){
        input_file >> current_int;
        input_file >> comma;
        data_vector.push_back(current_int);
    }

    input_file.close();

    cout << endl;

    return data_vector;

}

/*
* Function calculate_the_statistics
* Parameters:
*    vector<int> data_vector- a vector containing integer values
* Return: void
* Description:
*    This method calculates the total, average, variance,
*    and standard deviation of the elements in data_vector
*    by calling the corresponding methods find_total,
*    find_average, find_variance, find_standard_deviation.
*    This method also prints these values out.
*/
void calculate_the_statistics(vector<int> data_vector) {

    double total_of_input_vector;
    double average_of_input_vector;
    double variance_of_input_vector;
    double standard_deviation_of_input_vector;

    if ( data_vector.size() == 0 ) {
        cout << "Error: Vector is empty. "
             << "Please load the vector and try again." << endl;
        return;
    }

    cout << endl;

    total_of_input_vector = find_total(data_vector);

    cout << "The Total is "
         << fixed << setprecision(2) << total_of_input_vector << endl;

    average_of_input_vector = find_average(data_vector);

    cout << "The Average is "
         << fixed << setprecision(2) << average_of_input_vector << endl;

    variance_of_input_vector = find_variance(data_vector);

    cout << "The Variance is "
         << fixed << setprecision(2) << variance_of_input_vector << endl;

    standard_deviation_of_input_vector = find_standard_deviation(data_vector);

    cout << "The Standard Deviation is "
         << fixed << setprecision(2) << standard_deviation_of_input_vector << endl;

    cout << endl;

    return;
};

/*
* Function perform_the_count
* Parameters:
*    vector<int> data_vector- a vector containing integer values
*    vector<int> counting_vector- a vector containing integer values
* Return: vector<int> - After finding the frequency of each distinct
*                       element in data_vector, and storing those
*                       frequencies in counting_vector, the method
*                       returns counting_vector.
* Description:
*    This method counts the number of instances of distinct elements
*    in data_vector and places their frequencies in counting_vector.
*    The value in counting_vector is incremented for each instance of
*    a distinct element in data_vector.
*/
vector<int> perform_the_count(vector<int> data_vector, vector<int> counting_vector) {

    int length_of_data_vector = data_vector.size();

    if ( length_of_data_vector == 0 ) {
        cout << "Error: Vector is empty. "
             << "Please load the vector and try again." << endl;
        cout << endl;

        return counting_vector;
    }

    for ( int index = 0; index < length_of_data_vector; index++ ) {
        counting_vector[data_vector[index]] = counting_vector[data_vector[index]] + 1;
    }

    cout << endl;

    return counting_vector;
};

/*
* Function show_the_count
* Parameters:
*    vector<int> counting_vector- a vector containing integer values
* Return: void
* Description:
*    This method displays the value of the elements
*    contained in the vector that is passed in.
*    The index is printed followed by a bar ( | ) and then
*    the integer value stored in the vector.
*/
void show_the_count(vector<int> counting_vector) {

    int length_of_counting_vector = counting_vector.size();

    cout << endl;

    for ( int index = 0; index < length_of_counting_vector; index++ ) {
        int total_for_current_element = counting_vector[index];
        cout << setw(2) << right << index << "| "
             <<  total_for_current_element << endl;
    }

    cout << endl;

    return;
};

/*
* Function display_the_bar_graph
* Parameters:
*    vector<int> counting_vector- a vector containing integer values
* Return: void
* Description:
*    This method displays a Bargraph with the x-axis containing
*    X's corresponding to the normalized values of the elements contained
*    in the vector and the y-axis containing the individual elements
*    themselves.
*/
void display_the_bar_graph(vector<int> counting_vector) {

    int length_of_counting_vector = counting_vector.size();

    cout << endl;

    // Find the normalized value, then print the element, print a
    // Line separating the element and the Xs, and then have
    // another loop that prints out the number of Xs as specified
    // by the normalized value. a normalized value of 13
    // will print out 13 Xs.
    for ( int index = 0; index < length_of_counting_vector; index++ ){
        cout << setw(2) << right << index << "| ";
        int normalized_value = Normalization(counting_vector, index);

        for ( int total_number_of_x = 0; total_number_of_x < normalized_value; total_number_of_x++) {
            cout << 'X';
        }

        cout << endl;
    }

    cout << endl;

    return;
};

/*
* Function display_the_bar_graph_vertically
* Parameters:
*    vector<int> counting_vector- a vector containing integer values
* Return: void
* Description:
*    This method displays the Bargraph that we obtain in the other
*    display bar graph method only with the x-axis now containing
*    the individual elements and the y-axis containing X's corresponding
*    to the normalized values of the frequencies of the individual elements.
*
*/
void display_the_bar_graph_vertically(vector<int> counting_vector) {

    int length_of_counting_vector = counting_vector.size();
    //We need an array of the normalized values so we know
    // how many X's we need to display in the bar for the
    // corresponding element.
    int normalized_values[length_of_counting_vector];
    int max_normalized_value = 0;

    cout << endl;

    // We populate the normalized_values array with the normalized
    // values for each individual element in the vector by
    // calling the Normalization() method. We also save the
    // max_normalized_value since this value represents the
    // maximum number of X's and the highest row of the bar graph.
    for (int index = 0; index < length_of_counting_vector; index++) {
        int current_normalized_value = Normalization(counting_vector, index);
        normalized_values[index] = current_normalized_value;

        if ( max_normalized_value < current_normalized_value ) {
            max_normalized_value = current_normalized_value;
        }
    }

    // If the normalized value for the individual element is
    // larger or equal to the row index, then this corresponds to an
    // X in that position. For example if the normalized value
    // for a given element is 15, then rows 20-16 will not have
    // an X however rows 1-15 will have an X.
    for ( int row = max_normalized_value; row > 0; row--) {
        for ( int index = 0; index < length_of_counting_vector; index++ ) {
            if (  normalized_values[index] >= row ) {
                cout << setw(4) << right << "X";
            } else {
                cout << setw(4) << " ";
            }
        }
        cout << endl;
    }

    // Prints out a line separating the bar graph and the
    // individual elements in the X axis.
    for (int index = 0; index < length_of_counting_vector; index++) {
      cout << "____";
    }

    cout << endl;

    // Prints out each individual element corresponding to a bar
    // in the Bargraph.
    for (int index = 0; index < length_of_counting_vector; index++) {
      cout << setw(4) << right << index;
    }

    cout << endl;

    cout << endl;

    return;
};

/*
* Function find_total
* Parameters:
*    vector<int> input_vector-a vector containing integer values
*    return double- The total of the integers contained
*                   within the vector.
*
*    The intent is to calculate the total of all the
*    values stored in the Sealife.txt file.
*
*/
double find_total(vector<int> input_vector) {

    double total_of_input_vector = 0;
    int length_of_input_vector = input_vector.size();

    for ( int index = 0; index < length_of_input_vector; index++ ) {
        total_of_input_vector = total_of_input_vector + input_vector[index];
    }

    return total_of_input_vector;
};

/*
* Function find_average
* Parameters:
*    vector<int> input_vector-a vector containing integer values
*    return double- The average of the integers contained
*                   within the vector.
*
*    The intent is to calculate the average of all the
*    values stored in the Sealife.txt file.
*    The average is found by finding the sum of all
*    the elements divided by the total number
*    of elements.
*/
double find_average(vector<int> input_vector) {

    double total_of_input_vector;
    double average_of_vector;
    int length_of_input_vector = input_vector.size();

    // we call the find_total method since we need the
    // the total sum of all elements in order to find
    // the average.
    total_of_input_vector = find_total(input_vector);
    average_of_vector = total_of_input_vector / length_of_input_vector;

    return average_of_vector;
};

/*
* Function find_variance
* Parameters:
*    vector<int> input_vector-a vector containing integer values
*    return double- The variance of the integers contained
*                   within the vector.
*
*    The intent is to calculate the variance of all the
*    values stored in the Sealife.txt file.
*    The formula for variance is the sum of the difference
*    between the average and each element squared divided by
*    the total number of elements.
*/
double find_variance(vector<int> input_vector) {

    int index;
    int length_of_input_vector = input_vector.size();

    double average_of_input_vector;
    double variance_of_input_vector;

    double current_item;
    double squared_displacement;
    double sum_of_displacements_squared = 0;

    // we call the find_average method since we need the
    // the average in order to find the variance.
    average_of_input_vector = find_average(input_vector);

    for ( index = 0; index < length_of_input_vector; index++ ) {
        current_item = average_of_input_vector - input_vector[index];
        squared_displacement = current_item * current_item;
        sum_of_displacements_squared = sum_of_displacements_squared + squared_displacement;
    }

    variance_of_input_vector = sum_of_displacements_squared / length_of_input_vector;

    return variance_of_input_vector;
};

/*
* Function find_standard_deviation
* Parameters:
*    vector<int> input_vector-a vector containing integer values
*    return double- The standard deviation of the integers contained
*                   within the vector.
*
*    The intent is to calculate the standard deviation of all the
*    values stored in the Sealife.txt file.
*/
double find_standard_deviation(vector<int> input_vector) {

    double variance_of_input_vector;
    double standard_deviation_of_input_vector;

    // we call the find_variance method since we can find
    // the standard deviation from the variance.
    variance_of_input_vector = find_variance(input_vector);

    standard_deviation_of_input_vector = sqrt(variance_of_input_vector);

    return standard_deviation_of_input_vector;
};

/*
* Function Normalization
* Parameters:
*    vector<int> input_data-the vector containing the values not normalized
*    int         index- the index of the element containing the value to be
*                       normalized.
*    return int- the normalized value of the element at the given index.
*
*    The intent is to normalize the values in the counting vector by
*    dividing by 1000.
*/
int Normalization(vector<int> input_data, int index){
    return (int) input_data[index] / 1000;
}
