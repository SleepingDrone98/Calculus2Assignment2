/*******************************************************************************
Name:											Phillip Clarke
Student number:									040832994
Assignment number:								2
Course name and number:							Numerical Computing CST8233
Lab section number:								300
Professor's name:								Abdullah Kadri
Due date of assignment:							Friday, November 15th 2019
Submission date of assignment:					Saturday, November 16th 2019
List of source and header files in the project:	ass2.cpp
********************************************************************************/
#include <crtdbg.h>
#include <iostream>
#include <fstream>
#include <limits>
#include <string>
#include <iomanip>
using namespace std;
void extrapolation(double, double);
void exponentialFit();

/******************************************************************************************************************************************************************************
Function name:	Main
Purpose:		To run the logic of the program - runs a menu that allows the user to select a file to read from.
Function		In parameters: None
Function		Out parameters: Int (returns 0 upon success and closes the program)
Version:		1.0
Author:			Phillip Clarke
*******************************************************************************************************************************************************************************/

int main(void)
{
	char response;
	bool RUNNING = true;
		while (RUNNING)/*Menu that allows the user to run the exponentialFit function or quit*/
		{
			cout << "LEAST_SQUARES LINEAR REGRESSION\n\nMENU\n  1. Exponential Fit\n  2. Quit" << endl;
			cin >> response;
			switch (response)
			{
			case '1':exponentialFit();
				break;
			case '2':RUNNING = false;
				break;
			default:cout << "Please enter a valid option" << endl;
			}
		}
	return 0;
}

/******************************************************************************************************************************************************************************
Function name:	exponentialFit
Purpose:		allows the user to read from a file - builds arrays and variables based on the numbers in the passed in file, displays the linear regression fit and 
allows for the user to calculate the approximation based on the passed in year.
Function		In parameters: None
Function		Out parameters: void
Version:		1.0
Author:			Phillip Clarke
*******************************************************************************************************************************************************************************/
void exponentialFit()
{
	string file, word;
	/*Variables that house the calculations on the table based on the file that's read*/
	double tableX[100], tableY[100], tableWI[100], tableZI[100], tableWIZI[100], tableWI2[100], temp = 0.0, sumX = 0.0, sumY = 0.0, sumWI = 0.0,meanX=0.0,sumXY=0.0, meanY=0.0, sumZI = 0.0, sumWIZI = 0.0, sumWI2 = 0.0, a1=0.0, a0=0.0, a=0.0, b=0.0;
	/*Increments for every line read*/
	short counter=0;
	/*Prompts the user for the file name to be opened*/
	cout << "\nPlease enter the name of the file to open: ";
	cin >> file;
	ifstream inputFile;
	/*Opens file*/
	inputFile.open(file);
	/*Loop that checks if the filename passed in is correct*/
	if (inputFile.is_open())
	{
		getline(inputFile, word);/*Gets and prints the first line in the file showing the table headers*/
		cout << word << endl;

		/*Loop that reads the entirety of the file*/
		while ( inputFile >> temp)
		{

			cout << fixed;
			cout.precision(0);

			/*Builds the sum of the x column of the table and prints x*/
			sumX += temp;
			tableX[counter] = temp;
			cout << tableX[counter] << "\t\t";
			
			/*Builds the sum of the y column of the table and prints y*/
			inputFile >> temp;
			sumY += temp;
			tableY[counter] = temp;
			cout.precision(3);
			cout << scientific;
			cout << tableY[counter] << "\t\t";

			/*reads and prints the word from the file*/
			inputFile >> word;
			cout << word << "\n";
			
			/*Builds the sums and table values of the ZI, WI, WIZI and WI2 tables*/
			tableZI[counter] = log(tableY[counter]);
			tableWI[counter] = tableX[counter] - 1970;
			sumWI += tableWI[counter];
			sumZI += tableZI[counter];
			tableWIZI[counter] = tableWI[counter] * tableZI[counter];
			sumWIZI += tableWIZI[counter];
			tableWI2[counter] = pow(tableWI[counter], 2);
			sumWI2 += tableWI2[counter];

			/*Increments counter*/
			counter++;
		}
		/*Calculates the means of the x and y table values*/
		meanX = sumX / counter;
		meanY = sumY / counter;

		/*Displays the number of records*/
		cout << "\nThere are " << counter << " records." << endl;
		
		/*Calculates a1 for the equation*/
		a1 = ((counter * sumWIZI - sumWI * sumZI)) / (counter * sumWI2 - pow(sumWI, 2));
		/*calculates a0 for the equation*/
		a0 = (sumZI/counter) - a1 * (sumWI/counter);
		/*Calculates a and b based on a1 and a0*/
		a = exp(a0);
		b = a1;




		cout << scientific;
		cout.precision(3);
		/*Displays the linear regression fit based on the previous calculations*/
		cout << "\nLinear Regression Fit:  transistor count = "<<a<<"*exp("<<b<<"*(year-1970))\n" << endl;
		char response;
		bool RUNNING = true;
		/*Creates menu allowing for user to exit or extrapolate based on the calculations made from the file*/
		while (RUNNING)
		{
			cout << "\nMENU\n  1. Extrapolation\n  2. Main Menu" << endl;
			cin >> response;
			switch (response)
			{
			case '1':extrapolation(a, b);
				break;
			case '2':RUNNING = false;
				break;
			default:cout << "Please enter a valid option" << endl;
			}
		}
		inputFile.close();
	}

}

/******************************************************************************************************************************************************************************
Function name:	extrapolation
Purpose:		takes in the calculated variables from exponentialFit(), prompts the user for a year and calculates the transistor count and rate of count increase based on the year input
Function		In parameters: double a, double b
Function		Out parameters: void
Version:		1.0
Author:			Phillip Clarke
*******************************************************************************************************************************************************************************/
void extrapolation(double a, double b)
{
	/*Prompts user to input a custom year to plug into the calculation*/
	double year;
	cout << "\nPlease enter the year to extrapolate to: ";
	cin >> year;
	cout.precision(0);
	cout << fixed;

	/*Calculates the transistor count by plugging in a,b and the given year*/
	double transistorCount = a * exp(b*(year-1970));
	/*Calculates the rate increase yearly*/
	double rate = a * b * exp(b * (year - 1970));

	/*Prints the custom year, the transistor count and the rate increase based on the given year from the user */
	cout << "\nYear = " << year<<endl;
	cout.precision(3);
	cout << scientific;
	cout << "Transistor count = " << transistorCount << endl;
	cout << "Rate of count increase = " << rate << " transistors/year" <<endl;

}