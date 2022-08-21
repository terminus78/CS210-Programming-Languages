//===================================================
// Author: Shawn Way
// Date : 08/13/2022
//
// Purpose: Analyze purchase data and display
//          values using Python modules called and
//          handled with C++
//===================================================

#include <Python.h>
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <cmath>
#include <string>

using namespace std;

/*
Description:
	To call this function, simply pass the function name in Python that you wish to call.
Example:
	callProcedure("printsomething");
Output:
	Python will print on the screen: Hello from python!
Return:
	None
*/
void CallProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("ProcessData");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

/*
Description:
	To call this function, pass the name of the Python function you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("PrintMe","Test");
Output:
	Python will print on the screen:
		You sent me: Test
Return:
	100 is returned to the C++
*/
int callIntFunc(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"ProcessData");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;


	return _PyLong_AsInt(presult);
}

/*
Description:
	To call this function, pass the name of the Python function you wish to call and the int parameter you want to send
Example:
	int x = callIntFunc("doublevalue",5);
Return:
	25 is returned to the C++
*/
int callIntFunc(string proc, int param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"ProcessData");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;

	return _PyLong_AsInt(presult);
}

/*
Description:
	To call this function, pass the name of the Python function you wish to call and the int parameter you want to send
Example:
	callVoidFunc("MultiplicationTable",6);
Output:
	Python will print on the screen:
		6 X 1 = 6
        6 X 2 = 12
        6 X 3 = 18
        6 X 4 = 24
        6 X 5 = 30
        6 X 6 = 36
        6 X 7 = 42
        6 X 8 = 48
        6 X 9 = 54
        6 X 10 = 60
Return:
	None
*/
void callVoidFunc(string pName, int param)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("ProcessData");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* pValue = nullptr;
	pValue = Py_BuildValue("(i)", param);
	PyObject* my_result = PyObject_CallObject(my_function, pValue);
	Py_Finalize();

	delete[] procname;
}

// Print greeting to user at program start
void greeting()
{
	cout << string(50, '*') << endl;
	cout << "Welcome to the Purchase Data Analyzer." << endl;
	cout << string(50, '*') << endl;
	cout << endl;
}

// Print thank you message to user at program exit
void goodbye()
{
	cout << string(50, '*') << endl;
	cout << "Thank you for using the Purchase Data Analyzer!" << endl;
	cout << string(50, '*') << endl;
	cout << endl;
}

// Build and return menu choices string
string menuString()
{
	string buildString = "";
	buildString += "\nPlease enter a number for one of the following choices and press enter.\n\n";
	buildString += "1: Display today's purchase list\n";
	buildString += "2: Check item quantity purchased\n";
	buildString += "3: Display histogram\n";
	buildString += "4: Exit program\n\n";

	return buildString;
}

// Get verified string
template <typename T> void getVerifiedInput(T& inputToGet, string askForInput)
{
	// The following was inspired by the stack overflow post asked by Zik (https://stackoverflow.com/users/1276897/zik)
	// and answered by chris (https://stackoverflow.com/users/962089/chris)
	// Post: https://stackoverflow.com/questions/10349857/how-to-handle-wrong-data-type-input
	bool badInput = true;

	while (badInput)
	{
		badInput = false;

		// Loops if input could not be obtained
		while (cout << askForInput && !(cin >> inputToGet))
		{
			cin.clear();  // Reset fail flag
			cin.ignore(1000, '\n');  // Discard input

			cout << "Invalid input. Please ensure input is one word string." << endl;
		}

		// Continue looking for input if it contains spaces
		for (int i = 0; i < inputToGet.size(); i++)
		{
			if (isspace(inputToGet[i]))
			{
				cout << "Invalid input. Please input only one word.";
				badInput = true;
			}
		}
	}
}

// Get verified number
template <typename T> void getVerifiedInput(T& inputToGet, string askForInput, T lowLimit, T highLimit)
{
	// The following was inspired by the stack overflow post asked by Zik (https://stackoverflow.com/users/1276897/zik)
	// and answered by chris (https://stackoverflow.com/users/962089/chris)
	// Post: https://stackoverflow.com/questions/10349857/how-to-handle-wrong-data-type-input
	bool endWhile = false;

	// Loop until input does not fail checks
	while (!endWhile)
	{
		// Loops if input could not be obtained
		while (cout << askForInput && !(cin >> inputToGet))
		{
			cin.clear();  // Reset fail flag
			cin.ignore(1000, '\n');  // Discard input

			cout << "Invalid input. Please ensure input is numeric." << endl;
		}

		if (inputToGet < lowLimit)
		{
			cin.ignore(1000, '\n');  // Discard input

			cout << "Invalid input. Please enter a number greater than or equal to ";
			cout << lowLimit << "." << endl;

			continue;
		}
		else if (inputToGet > highLimit)
		{
			cin.ignore(1000, '\n');  // Discard input

			cout << "Invalid input. Please enter a number less than or equal to ";
			cout << highLimit << "." << endl;

			continue;
		}

		endWhile = true;
	}
}

// I love the smell of *main* in the morning...
int main()
{
	int menuChoice = 0;
	int userValue;
	string itemName;
	const string ASK_MENU_CHOICE = menuString();  // Full menu build in menuString function

	greeting();  // Display greeting to user at start

	// Loop until user chooses to exit program
	while (menuChoice != 4)
	{
		// Get menu choice
		getVerifiedInput<int>(menuChoice, ASK_MENU_CHOICE, 1, 4);

		switch (menuChoice)
		{
		// Display today's purchase list
		case 1:
			CallProcedure("todayPurchaseList");
			break;

		// Check item quantity purchased
		case 2:
			getVerifiedInput<string>(itemName, "Enter item name as a one word string: ");

			cout << endl;
			cout << itemName << " quantity purchased: " << callIntFunc("findItemPurchaseAmount", itemName);
			cout << endl;
			break;

		// Display histogram
		case 3:
			CallProcedure("displayHistogram");
			break;

		// Thank user and end program
		case 4:
			goodbye();
			break;

		// This case should never be needed
		default:
			cout << "Damn...(furiously erases notes from drawing board)" << endl;
			cout << endl;
			break;
		}
	}

	return 0;
}