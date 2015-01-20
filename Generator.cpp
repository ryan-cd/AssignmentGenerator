/***
Assignment 1 Generator Bonus
Ryan Davis
2S03

This generator will create a full assignment 1 setup for every student number found in "studentNumbers.txt" in the local directory. One number per line in the file
If no "studentNumbers.txt" is found in the local directory, the program will give an error and stop.
***/

#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include <direct.h>
#include <math.h>
#include <sstream>

using namespace std;

//function declarations
void readStudentNumbers(); //reads student numbers from "studentNumbers.txt" in local directory
void makeStudentDirectories(); //creates the student number directories with corresponding /se2s03 folders
void writeA2Test(); //makes A2Test java file
int A2RecursionSolve(int j, int a0, int a1, int x, int y); //this takes initialization values as input, applies recursion, and returns output. j is iteration value (0-30), rest are args of the function
void writeA2(); //makes A2 java file
void writeA1Test(); //makes A1Test java file
void writeA1(); //makes A1 java file

//global variables
vector <string> studentNumberList; //a list of every student number found in the "studentNumbers.txt" file
string currentDirectory; //variable for the current directories being used
bool studentNumbersDetected = false; //if student numbers file is detected this goes to true and the whole program runs. if not, the program will stop with an error message

vector <int> A2a0Array; //array of the a0 values. each student number directory has it's own randomized a0
vector <int> A2a1Array; //array of the a1 values. each student number directory has it's own randomized a1
vector <int> A2xArray; //array of the x values. each student number directory has it's own randomized x
vector <int> A2yArray; //array of the y values. each student number directory has it's own randomized y

vector <int> A1RandomOffset; //random offset for A1's x,y,z coordinates
vector <int> A1RandomAnswerOffset; //random offset for A1's return values
//the following arrays store all the x,y,z, and answer values from the original A1Test file provided. They will be offset by random values later on.
int A1xArray[] = {0,4,3,-1,2,2,4,6,3,12,12,-100,1,16,-7,-10,11,-8,4,1,9,3,-1,2,18,-7,7,4,6,13,0,5,2,1,3,0,10,20,2,4,3,4,2,3,4,2,3,4,2,3,4,2,3,4,2,3,4,2,3,3,4,2,2,3,4,2,3,4,3,4,4,2};
int A1yArray[] = {0,0,-5,-6,-4,-4,9,10,-3,-6,-5,-10,-1,2,6,-2,7,2,0,0,2,-5,-4,-4,-5,-15,-7,9,10,-7,10,-15,0,-4,-6,0,0,-18,-7,-5,-3,8,9,10,-7,-6,-5,-4,-3,8,9,10,-7,-6,-5,-4,-3,8,-5,9,10,-7,9,-6,-5,-4,-3,8,10,10,9,-6};
int A1zArray[] = {0,0,12,13,4,5,2,-7,1,3,3,11,0,-9,2,9,6,-5,1,-4,-9,17,-1,13,7,5,3,-10,-15,30,0,1,5,1,2,5,-5,10,1,3,5,1,2,3,4,5,1,2,3,4,5,1,2,3,4,5,1,2,13,3,4,5,1,1,2,3,4,5,2,2,1,13};
int A1answerArray[] = {10,6,7,9,10,1,6,3,10,5,2,7,10,6,10,1,2,10,6,10,6,9,10,1,2,7,5,6,3,5,10,6,1,10,7,1,6,5,7,2,1,6,10,10,5,7,7,6,10,10,2,10,7,5,7,1,6,10,9,10,2,7,10,7,6,10,10,2,10,3,6,9};


int main(){
    srand(time(NULL)); //randomize the random numbers. without this command the random numbers generated are the same every time
    //cout << sizeof(A1xArray)/sizeof(A1xArray[0]) << endl << sizeof(A1yArray)/sizeof(A1yArray[0]) << endl << sizeof(A1zArray)/sizeof(A1zArray[0]) << endl << sizeof(A1answerArray)/sizeof(A1answerArray[0]) << endl;
    cout << "Welcome to the Assignment 1 Generator! Made by Ryan Davis\n\n";
    readStudentNumbers();
    if(studentNumbersDetected == true){
        makeStudentDirectories();
        writeA2Test();
        writeA2();
        writeA1Test();
        writeA1();
    }

	system ("pause"); //this line is to prevent the console from exiting immediately

	return 0;
}

void readStudentNumbers(){
    //method of reading from files from cplusplus.com
    cout << "Now reading student numbers from local directory... ... ...\n";
    string studentNumber; //used to keep track of what line the system is reading from the file. (each student number is on its own line in the file)
    ifstream myfile ("studentNumbers.txt"); //load "studentNumber.txt". (assumed to be in local directory)

	if (myfile.is_open())
	{
	    studentNumbersDetected = true;
		while ( getline (myfile,studentNumber) ) //while system can retrieve information from a line in the file
	    {
	        cout << "Reading student number: " << studentNumber << endl;
			studentNumberList.push_back(studentNumber); //add the student number read to the vector
	    }
     myfile.close();
    } else {
		cout << "Error: Unable to open file. Make sure \"studentNumber.txt\" exists in the local directory";
	}
	cout << endl;
}

void makeStudentDirectories(){
    //for loop generates a directory for every student number that was found
    for (int i = 0; i < studentNumberList.size(); i++){
        //make student # directory
        cout << "creating directory for " << studentNumberList[i] << endl;
        _mkdir(studentNumberList[i].c_str());

        //make /%student number%/se2s03 directory
        currentDirectory = studentNumberList[i] + "/se2s03";
        _mkdir(currentDirectory.c_str());
    }
}

void writeA2Test(){
    //for loop generates a file for every student number that was found
    for (int i = 0; i < studentNumberList.size(); i++){
        currentDirectory = studentNumberList[i]+"/A2Test.java"; //set current directory to /%student number/A2Test.java

        //create a random number to use for each of the variable initializations in A2
        A2a0Array.push_back(ceil(rand()%4)+1);
        A2a1Array.push_back(ceil(rand()%4+1) * (-1));
        A2xArray.push_back(ceil(rand()%4)+1);
        A2yArray.push_back(ceil(rand()%4+1) * (-1));

        cout << "\nWriting A2Test to " << currentDirectory
                << " with a0 = " << A2a0Array[i] << ", "
                << " a1 = " << A2a1Array[i] << ", "
                << " x = " << A2xArray[i] << ", "
                << " y = " << A2yArray[i] << ". ";

        ofstream myFileOut (currentDirectory.c_str()); //prepare to write to the current directory location

        if (myFileOut.is_open()){
            //write A2Test.java
            myFileOut << "import static org.junit.Assert.*;\n";
            myFileOut << "import org.junit.BeforeClass;\n";
            myFileOut << "import org.junit.Test;\n\n";
            myFileOut << "import se2s03.A2;\n\n";
            myFileOut << "public class A2Test {\n";
            myFileOut << "    private static A2 tester;\n\n";
            myFileOut << "    @BeforeClass\n";
            myFileOut << "    public static void setUp(){\n";
            myFileOut << "        tester = new A2();\n";
            myFileOut << "    }\n\n";
            myFileOut << "    @Test\n";
            myFileOut << "    public void RecTest() {\n";

            for (int j = 0; j < 31; j++) {
                //this for loop will write out the test values from 0 to 30. the A2RecursionSolve function will figure out what the outputs should be, and will insert them too.
                myFileOut << "        assertEquals(\"Rec(" << j << ") must be "
                        << A2RecursionSolve(j, A2a0Array[i], A2a1Array[i], A2xArray[i], A2yArray[i]) << "\", "
                        << A2RecursionSolve(j, A2a0Array[i], A2a1Array[i], A2xArray[i], A2yArray[i]) << ", tester.Rec("
                        << j << "));\n";
            }

            myFileOut << "    }\n";
            myFileOut << "}\n";

        }
        myFileOut.close();
    }
    cout << endl;
}

int A2RecursionSolve(int j, int a0, int a1, int x, int y){
    //this function takes j (the test value from 0 to 30), and the initialization variables. It will perform recursion to work out what the output should be, and will return it

    int an = 0;

    if ( j == 0 ) return a0;
    if ( j == 1 ) return a1;

    for ( int i=2; i <= j; i++ ) {
       an= x * a0 + y * a1;
       a0 = a1;
       a1 = an;
    }
    return an;
}

void writeA2(){
    //for loop generates a file for every student number that was found
    for (int i = 0; i < studentNumberList.size(); i++){
        cout << "\ncreating \\se2s03\\A2.java file for " << studentNumberList[i];
        currentDirectory = studentNumberList[i] + "/se2s03/A2.java"; //set current directory variable to /%student number%/se2s03/A2.java

        ofstream myFileOut (currentDirectory.c_str()); //prepare to write to current directory location

        if (myFileOut.is_open()){
            //write A2.java using random a0, a1, x, y variables created earlier
            myFileOut << "package se2s03;\n\n";
            myFileOut << "public class A2 {\n";
            myFileOut << "    public int Rec(int n) {\n";
            myFileOut << "        int a0 = "; myFileOut << A2a0Array[i]; myFileOut << ", a1 = "; myFileOut << A2a1Array[i]; myFileOut << ", an = 0 ;\n";
            myFileOut << "        int x = "; myFileOut << A2xArray[i]; myFileOut << ", y = "; myFileOut << A2yArray[i]; myFileOut << " ;\n\n";
            myFileOut << "        if ( n == 0 ) return a0;\n";
            myFileOut << "        if ( n == 1 ) return a1;\n\n";
            myFileOut << "        for ( int i=2; i <= n; i++ ) {\n";
            myFileOut << "            an= x * a0 + y * a1;\n";
            myFileOut << "            a0 = a1;\n";
            myFileOut << "            a1 = an;\n";
            myFileOut << "        }\n";
            myFileOut << "        return an;\n";
            myFileOut << "    }\n";
            myFileOut << "}";
        }
        myFileOut.close();
    }
    cout << endl << endl;
}

void writeA1Test(){
    //for loop generates a file for every student number that was found
    for (int i = 0; i < studentNumberList.size(); i++){
        currentDirectory = studentNumberList[i]+"/A1Test.java"; //set current d
        A1RandomOffset.push_back(rand() % 6 - 3); // (x,y,z) points random offset
        A1RandomAnswerOffset.push_back(rand() % 6 - 3); // output random offset

        cout << "\nWriting A1Test to " << currentDirectory << " with (x,y,z) offset variable " << A1RandomOffset[i] << " and output offset variable " << A1RandomAnswerOffset[i];

        ofstream myFileOut (currentDirectory.c_str()); //prepare to write to current location
        if (myFileOut.is_open()){
            myFileOut << "import static org.junit.Assert.*;\n\n";
            myFileOut << "import org.junit.BeforeClass;\n";
            myFileOut << "import org.junit.Test;\n\n";
            myFileOut << "import se2s03.A1;\n\n";
            myFileOut << "public class A1Test {\n\n";
            myFileOut << "    private static A1 tester;\n\n";
            myFileOut << "    @BeforeClass\n";
            myFileOut << "    public static void setUp(){\n";
            myFileOut << "        tester = new A1();\n";
            myFileOut << "    }\n\n";
            myFileOut << "    @Test\n";
            myFileOut << "    public void casesTest() {\n";

            for (int j = 0; j < 72; j++) {
                //write all 72 test cases for the current A1Test file
                //for each variable, write the value of the original variable plus the random offset
                //for each output, write the value of the original output plus the random answer offset
                myFileOut << "        assertEquals(\"cases("
                        << A1xArray[j] + A1RandomOffset[i] << "," << A1yArray[j] + A1RandomOffset[i] << "," << A1zArray[j] + A1RandomOffset[i] << ") must be "
                        << A1answerArray[j] + A1RandomAnswerOffset[i] << "\", "
                        << A1answerArray[j] + A1RandomAnswerOffset[i] << ", tester.cases("
                        << A1xArray[j] + A1RandomOffset[i] << "," << A1yArray[j] + A1RandomOffset[i]<< "," << A1zArray[j] + A1RandomOffset[i] << "));\n";
            }

            myFileOut << "    }\n";
            myFileOut << "}\n";

        }
        myFileOut.close();
    }
    cout << endl;
}

void writeA1(){
    //for loop generates a file for every student number that was found
    for (int i = 0; i < studentNumberList.size(); i++){
        cout << "\ncreating \\se2s03\\A1.java file for " << studentNumberList[i];
        currentDirectory = studentNumberList[i] + "/se2s03/A1.java"; //set current directory variable to /%student number%/se2s03/A1.java

        ofstream myFileOut (currentDirectory.c_str()); //prepare to write to current directory

        if (myFileOut.is_open()){
            //write the A1 file. add the random offset to each of the original values in the if statement. add the random answer offset to each of the original return values
            myFileOut << "package se2s03;\n\n";
            myFileOut << "public class A1 {\n";
            myFileOut << "    public int cases(int v, int u, int w) {\n";
            myFileOut << "    	if (v <= "; myFileOut << 3+A1RandomOffset[i]; myFileOut << "){\n";
            myFileOut << "    		if (u <= "; myFileOut << (-5 + A1RandomOffset[i]); myFileOut << "){\n";
            myFileOut << "    			if (w <= "; myFileOut << (12 + A1RandomOffset[i]); myFileOut << "){\n";
            myFileOut << "    				return "; myFileOut << (7 + A1RandomAnswerOffset[i]) << ";\n";
            myFileOut << "    			} else {\n";
            myFileOut << "    				return "; myFileOut << (9 + A1RandomAnswerOffset[i]); myFileOut << ";\n";
            myFileOut << "    			}\n";
            myFileOut << "    		} else {\n";
            myFileOut << "    			if (w <= "; myFileOut << (4+ A1RandomOffset[i]); myFileOut << "){\n";
            myFileOut << "    				return "; myFileOut << (10 + A1RandomAnswerOffset[i]); myFileOut << ";\n";
            myFileOut << "    			} else {\n";
            myFileOut << "    				return "; myFileOut << (1+ A1RandomAnswerOffset[i]); myFileOut << ";\n";
            myFileOut << "    			}\n";
            myFileOut << "    		}\n";
            myFileOut << "    	} else {\n";
            myFileOut << "    		if (w <= "; myFileOut << (2 + A1RandomOffset[i]); myFileOut << "){\n";
            myFileOut << "    			if (u <= "; myFileOut << (9 + A1RandomOffset[i]); myFileOut << "){\n";
            myFileOut << "    				return "; myFileOut << (6 + A1RandomAnswerOffset[i]); myFileOut << ";\n";
            myFileOut << "    			} else {\n";
            myFileOut << "    				return "; myFileOut << (3 + A1RandomAnswerOffset[i]); myFileOut << ";\n";
            myFileOut << "    			}\n";
            myFileOut << "    		} else {\n";
            myFileOut << "    			if (u <= "; myFileOut << (-6 + A1RandomOffset[i]); myFileOut << "){\n";
            myFileOut << "    				return "; myFileOut << (5 + A1RandomAnswerOffset[i]); myFileOut << ";\n";
            myFileOut << "    			} else {\n";
            myFileOut << "    				return "; myFileOut << (2 + A1RandomAnswerOffset[i]); myFileOut << ";\n";
            myFileOut << "    			}\n";
            myFileOut << "    		}\n";
            myFileOut << "    	}\n";
            myFileOut << "    }\n";
            myFileOut << "}\n\n";
        }
        myFileOut.close();
    }
    cout << endl << endl;
}
