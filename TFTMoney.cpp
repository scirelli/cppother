//-------------------------------------------------------------
//
//Program Name: TFTMoney.cpp
//
//Purpose: This Program receives a file, finds the number of ints,
//doubles, strings, and bools. It determines how much memory each
//takes, plus how it is used.  It also displays how much
//memory the entire file uses.
//
//Coder: Chad Troisi
//
//Date: 3/1/02
//
//-------------------------------------------------------------


#include <iostream>
#include <fstream>
#include <ciso646>
#include <string>


using namespace std;


//Subprograms that will be used.
string getfilename(void);  //Get the filname from the user.

void outputLines(string message);  //Printed data

string inputLines(void);  // Inputs of the data

//Calculates the number of ints, doubles, bools, or strings
void testdata(ifstream & fin, string data, bool & foundint, int & 
numberOfInts,
	bool & founddouble, int & numberOfDoubles, bool & foundbool, int & 
numberOfBools,
	bool & foundstring, int & numberOfStrings, bool & foundequal);

void outputHeading(string fileName);  //Gives the out-put for the begining 
of the program..

void outputGreet(string greeting); // Prints the greeting at the beginning 
of the program.

//Prints the results of the ints, doubles, bools, and strings
// also, the size of the variable and the total amout of bytes is given.
void outputTypeResults( string type, int numberOfType, int sizeOfType, int 
totalbytes);

void outputTotal( int totalbytes);  //The total memory used gets printed to 
the screen.

bool anotherFile(void); //Prompts the user whether or not they want to 
process another file



//The Main Program.
int main(void)
{

	//User greeting and directions for use are given
	outputGreet("Hello!! Welcome To Thanks For The Memory!!\n\n");

	// The game description is given and the user is Prompted for the name of 
the
	// program file in which he/she wants to find the memory information about.
	outputGreet("This is a program that will read in other .cpp programs ");
	outputGreet("and try to determine how much space the computer will ");
	outputGreet("need to store the variables. \n\n");


	bool again = true;
	while (again)
	{

	// Declaring variables to be used in the program.
	string fileName;
	int numberOfInts = 0;
	int numberOfDoubles = 0;
	int numberOfStrings = 0;
	int numberOfBools = 0;
	int sizeOfInts = sizeof(int);
	int sizeOfDoubles = sizeof(double);
	int sizeOfBools = sizeof(bool);
	int sizeOfStrings = sizeof(string);
	bool foundint = false;
	bool founddouble = false;
	bool foundbool = false;
	bool foundstring = false;
	bool foundequal = false;

	//Retrieves the file name.
	fileName = getfilename();
	ifstream fin( fileName.c_str() ); //Opens the file that was given.

	string data;

	while( fin >> data )
	{

		//Calculates the amount of ints, doubles, strings, and bools
		testdata( fin, data, foundint, numberOfInts, founddouble, numberOfDoubles,
			foundbool, numberOfBools, foundstring, numberOfStrings, foundequal );

	}

	//Information is printed on the screen.
	outputHeading( fileName );

	//The results of each type of varible is calculated.
	outputTypeResults( "int(s)", numberOfInts, sizeOfInts, numberOfInts * 
sizeOfInts);
	outputTypeResults( "doubles(s)", numberOfDoubles, sizeOfDoubles, 
numberOfDoubles * sizeOfDoubles);
	outputTypeResults( "string(s)", numberOfStrings, sizeOfStrings, 
numberOfStrings * sizeOfStrings);
	outputTypeResults( "bool(s)", numberOfBools, sizeOfBools, numberOfBools * 
sizeOfBools);

	//The total amount of memory is printed to the screen.
	outputTotal(numberOfInts * sizeOfInts + numberOfDoubles * sizeOfDoubles + 
numberOfStrings * sizeOfStrings + numberOfBools * sizeOfBools);

	//Determines whether or not user wants to process another file
	again = anotherFile();
	}

	//The end of the main prgram.
	return 0;
}

//---------------------------------------------------------
//						Subprograms
//---------------------------------------------------------

//Retrieves the name of the file.
string getfilename()
{

	while (true)
	{
		//Promts user for the name of the file to get.
		outputLines("Please enter the name of the file: ");

		string fileName;
		fileName = inputLines();

		//Space created between input information and the output results.
		cout << endl;

		//Opens the file.
		ifstream fin(fileName.c_str() ) ;

		//Does the file name exist?
		if ( not fin.fail() )
			return fileName;
		else
			outputLines("File not found \n") ;

	}
}

// Determines how many ints, doubles, bools, and strings are in a file.
void testdata ( ifstream & fin, string data, bool & foundint, int & 
numberOfInts, bool & founddouble, int & numberOfDoubles,
	bool & foundbool, int & numberOfBools, bool & foundstring, int & 
numberOfStrings, bool & foundequal)
{

	int datafind = 0;
	string lineOfData;

	//When a comment is found the rest of the line is skipped.
	if (data == "//")
	{
		getline( fin, lineOfData, '\n');
	}

	//The amount of ints is determined.
	if (foundint)
	{
		if ( data == "main()" or data == "main(void)" or data == "=")
		{
			foundint = false;
			foundequal = false;
		}
		else {
			if (not foundequal)
			{
				numberOfInts++;
				datafind = data.find(";") + 1;
				if ( datafind > 0 )
				{
					foundint = false;
					foundequal = false;
				}
				datafind = data.find(",") + 1;
				if ( datafind > 0 )
					foundequal = false;
			}
		}

	}

	//The amount of doubles is determined.
	if (founddouble)
	{
		if (data == "=")
			foundequal = true;
		if (not foundequal)
		{
			numberOfDoubles++;
			datafind = data.find(";") + 1;
			if ( datafind>0 )
			{
				founddouble = false;
				foundequal = false;
			}
		}
		datafind = data.find(";") + 1;
		if ( datafind>0 )
		{
			founddouble = false;
			foundequal = false;
		}
	}

	//The amount of strings is determined.
	if (foundstring)
	{
		if ( data == "=")
			foundstring = false;
		else
		{
			numberOfStrings++;
			datafind = data.find(";") + 1;
			if ( datafind>0 )
				foundstring = false;
		}
		datafind = data.find("(") + 1;
		if ( datafind > 0 )
			foundstring = false;
	}

	//The amount of bools is determined.
	if (foundbool)
	{
		if ( data == "=" )
			foundbool = false;
		else
		{
			numberOfBools++;
			datafind = data.find(";") + 1;
			if ( datafind>0 )
				foundbool = false;
		}
	}


	//Determines whether or not to continue the search for ints, doubles, 
bools, or strings
	datafind = data.find(",") + 1;
	if ( datafind > 0 )
		foundequal = false;
	if (data == "int")
		foundint = true;
	if (data == "double")
		founddouble = true;
	if (data == "string")
		foundstring = true;
	if (data == "bool")
		foundbool = true;
}


//Input information is processed.
string inputLines()
{
	//Gets input
	string input;
	cin >> input;
		return input;
}


//Prints output to screen.
void outputLines(string message)
{
	cout << message;
}

//Prints output to screen.
void outputGreet(string greeting)
{
	cout << greeting;
}


//Outputs basic information at top of output screen
void outputHeading( string fileName )
{
	outputLines( fileName + " requires:\n");
}



//The output results for ints, doubles, bools, and strings
void outputTypeResults( string type, int numberOfType, int sizeOfType, int 
totalbytes)
{
	outputLines("     ");
	cout << numberOfType ;
	outputLines( " " + type + " requiring ");
	cout << totalbytes;
	outputLines( " bytes (" );
	cout << sizeOfType;
	outputLines( " bytes each).\n");
}


//Outputs total amount of memory used
void outputTotal( int totalbytes )
{
	outputLines("     Total: ");
	cout << totalbytes;
	outputLines(" bytes of memory used:\n");
}


//Asks the user whether the user wants to process another file
bool anotherFile(void)
{

	bool gettingInput = true;
	bool yesAnswer;
	bool noAnswer;

	while(gettingInput)
	{
		outputLines("Would you like to process a different file(Y/N)?  ");
		string answer;
		answer = inputLines();
		outputLines("\n");

		//what is a correct answer for each variable
		yesAnswer = (answer == "Y") or (answer == "y");
		noAnswer = (answer == "N") or (answer == "n");

		gettingInput = not (yesAnswer or noAnswer); //tries again is input was 
wrong

	}
	return yesAnswer;
}


/*
Please enter the name of the file: EnglishLength.cpp

EnglishLength.cpp requires:
     6 int(s) requiring 24 bytes (4 bytes each).
     0 doubles(s) requiring 0 bytes (8 bytes each).
     0 string(s) requiring 0 bytes (16 bytes each).
     0 bool(s) requiring 0 bytes (1 bytes each).
     Total: 24 bytes of memory used:
Would you like to process another file(Y/N)?  y

Please enter the name of the file: NameChange.cpp

NameChange.cpp requires:
     2 int(s) requiring 8 bytes (4 bytes each).
     0 doubles(s) requiring 0 bytes (8 bytes each).
     3 string(s) requiring 48 bytes (16 bytes each).
     0 bool(s) requiring 0 bytes (1 bytes each).
     Total: 56 bytes of memory used:
Would you like to process another file(Y/N)?  y

Please enter the name of the file: MPoD.cpp

MPoD.cpp requires:
     3 int(s) requiring 12 bytes (4 bytes each).
     0 doubles(s) requiring 0 bytes (8 bytes each).
     1 string(s) requiring 16 bytes (16 bytes each).
     5 bool(s) requiring 5 bytes (1 bytes each).
     Total: 33 bytes of memory used:
Would you like to process another file(Y/N)?  y

Please enter the name of the file: Pain.cpp

Pain.cpp requires:
     4 int(s) requiring 16 bytes (4 bytes each).
     3 doubles(s) requiring 24 bytes (8 bytes each).
     1 string(s) requiring 16 bytes (16 bytes each).
     0 bool(s) requiring 0 bytes (1 bytes each).
     Total: 56 bytes of memory used:
Would you like to process another file(Y/N)?  n

Press any key to continue

*/


