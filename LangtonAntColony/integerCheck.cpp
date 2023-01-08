#include "integerCheck.h"
#include <iostream>
#include <algorithm>
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::getline;
using std::remove;
using std::atoi;

int getUnsignedInt()
{
	//string variable to store input in which will be used to check for unsigned int
	//int variable to hold converted string to integer
	string input;
	int uint;

	//loop until is given Int
	do
	{
		//gets full input
		getline(cin, input);

		
		//https://stackoverflow.com/questions/16329358/remove-spaces-from-a-string-in-c
		input.erase(remove(input.begin(), input.end(), ' '), input.end());
		
		if (!(isUnsignedInt(input)))
			cout << "Error. Please enter a positive integer." << endl;

	} while (!(isUnsignedInt(input)));

	uint = atoi(input.c_str());

	return uint;
}

//checks input string to make sure all chars are digits
bool isUnsignedInt(string input)
{
	bool message;

	for (int index = 0; index < input.size(); index++)
	{
		if (isdigit(input[index]))
			message = true;
		//immediately return false if anything other than a number
		//is found
		else
			return false;
	}

	return message;
}

//check if is input in our range
bool isRange(int input, int max, int min)
{
	if (input > max)
		return false;
	if (input < min)
		return false;

	return true;
}