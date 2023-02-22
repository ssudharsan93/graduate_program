/****************************************
*
* Virtual Functions and Pointers
* Sudharsan Sundaravenkataraman
* The University of Texas at Dallas
* Homework #4
* October 25, 2022
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
#include "Barge.h"

// Use the STD Namespace
using namespace std;

//Prototypes
//List of functions in this file
//With the correct parameters
//And with the correct return types
void menu();
void output_name();
Barge create_new_barge();
void ignite_barge(vector<Barge> my_barge);

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
  cout << "October 25, 2022" << endl;
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
*        1. Clearing the barge vector.
*        2. Creating a new barge vector and loading it with random fireworks.
*        3. Setting off the fireworks by calling Barge.Ignite()
*        4. Exiting the program.
*
*    While "Nothing Happens" keep waiting.
*
* Once something happens, function pause ends.
*
*/

void menu() {

    bool user_not_terminated = true;
    vector<Barge> barge_vector;

    while (user_not_terminated) {
        cout << "1. Clear the Vector" << endl;
        cout << "2. Create Barge and Load Fireworks" << endl;
        cout << "3. Set off the Fireworks" << endl;
        cout << "4. Exit the Program" << endl;
        cout << "--------------" << endl;

        int user_decision;

        cin >> user_decision;

        switch (user_decision) {
            case 1 :
                barge_vector.clear();
                break;
            case 2 :
                barge_vector.push_back(create_new_barge());
                break;
            case 3 :
                ignite_barge(barge_vector);
                break;
            case 4 :
                user_not_terminated = false;
                break;
            default :
                cout << "Invalid Input. Try Again";
                break;
        }
    }
}

/*
* Function create_new_barge
* Parameter List: empty
* Return: Barge object
*         returns a barge object with the name property
*         set to the string you provide and filled with
*         random fireworks.
* Description:
*         This method prompts the user for the name of
*         the new barge to be created and filled with
*         random fireworks. Then finally returns the
*         barge back to the menu function.
*/

Barge create_new_barge() {

    string barge_name;

    cout << "Please enter a new for the new barge:" << endl;
    cin >> barge_name;

    Barge new_barge = Barge(barge_name);


    for (int i = 0; i < 10; i++){

        int firework_index = rand() % 7;

        Firework *current_firework;

        switch ( firework_index ) {
            case 0 :
                current_firework = new Firework();
                new_barge.LoadFirework(current_firework);
                break;
            case 1 :
                current_firework = new Rocket();
                new_barge.LoadFirework(current_firework);
                break;
            case 2 :
                current_firework = new Rocket("white");
                new_barge.LoadFirework(current_firework);
                break;
            case 3 :
                current_firework = new Rocket("blue");
                new_barge.LoadFirework(current_firework);
                break;
            case 4 :
                current_firework = new Flower();
                new_barge.LoadFirework(current_firework);
                break;
            case 5 :
                current_firework = new Flower("purple");
                new_barge.LoadFirework(current_firework);
                break;
            case 6 :
                current_firework = new Flower("pink");
                new_barge.LoadFirework(current_firework);
                break;
            default :
                current_firework = new Rocket("deep purple");
                new_barge.LoadFirework(current_firework);
                break;
        }

    }

    return new_barge;

}


/*
* Function ignite_barge
* Parameter List: vector<Barge> my_barge
* Return: void
* Description:
*         This method simply iterates through all the
*         Barges in the Barge vector and calls the
*         Barge.Ignite() method.
*/

void ignite_barge(vector<Barge> my_barge) {

    cout << endl;
    for ( int barge_index = 0; barge_index < my_barge.size(); barge_index++ ) {
        my_barge[barge_index].Ignite();
    }
    cout << endl;
}
