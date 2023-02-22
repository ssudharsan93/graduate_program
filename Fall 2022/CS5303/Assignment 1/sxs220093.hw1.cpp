/****************************************
* 
* The Fate of Omnicron
* Sudharsan Sundaravenkataraman
* The University of Texas at Dallas
* Homework #1
* August 29, 2022
* Macbook
* g++ compiler
* Study Group: 
* Study Group Members: 
* 
****************************************/

// Include Library Header Files
//#include <conio.h>
#include <iostream>
#include <math.h>

// Use the STD Namespace
using namespace std;
 
// Set Global Constants (Not Variables)
const double gravity = 9.8;// meters/(second*second)
const double pi = atan(1) * 4.0; //I Like Pie

//Prototypes
//List of functions in this file 
//With the correct parameters
//And with the correct return types
void pause();
double findLength(double period);
double metres2feet(double meters);


// There is always a Main function to begin the program in C++.
int main()
{
	double length_metres;
	double length_feet;
	cout << "Oh, no! Curse you, Evil Captain Retcon!" << endl;
 	
	length_metres = findLength(5.0);
	length_feet = metres2feet(length_metres);

	cout << "Length for 5 seconds is " << length_metres <<" meters"<< endl;
	cout << "Length for 5 seconds is " << length_feet << " feet" << endl;

	cout << "Since Evil Captain Retcon has the heroic Omnicron tied" << endl;
	cout << "25 feet beneath the fulcrum of the swinging blade." << endl;

		if (length_feet > 25)
		{
			cout << "Poor Omnicron is cut in half!" << endl;
		}
		else
		{
			cout << "Omnicron is safe from the evil machinations of Evil Captain Retcon!" << endl;
		}


	pause();

	return 0;
}

/*
*  Function Pause
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
void pause()
{
	cout << "Press enter to continue" << endl;
	while (getchar() == NULL);
}

/*
* Function findLength
* Parameters:
*    double period-the period of a pendulum in seconds
*    return double-the length of the pendulum in metres.
* 
* The period of a pendulum is 2pi
*  mulitplied by the square root of length
*  divided by the acceleration due to gravity.
*
*  T=2pi*sqrt(L/g)
*
*  Need to reverse this equation to find length L in metres.
* 
*/

double findLength(double period)
{
	double result;
	double temp1;
	double temp2;
	double temp3;

	result = 0.0;
	temp1 = 0.0;
	temp2 = 0.0;
	temp3 = 0.0;

	temp1 = period/(2*pi); //Multiply the period by 2 pi
	temp2 = temp1 * temp1; //Square the quotient
	temp3 = temp2 * gravity; //Mulitply by gravity
	result = temp3; //What is left is the length in metres

	return result;
}

/*
* function doubles metres2feet
* parameter double metres- the number of metres
* return double - the number of feet
* Multiply by 100.00 centimetres per metre
* Divide   by   2.54 centimetres per inch
* Divide   by  12.00 inches per foot
*/

double metres2feet(double meters)
{
	double result = 0.0;

	result = meters * 100 / 2.54 / 12;
	return result;
}
