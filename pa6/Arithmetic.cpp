/**
 * * * * Amisha Prasad // First and Last Name
 * * * * aprasa14 // UCSC UserID
 * * * * 2024 Winter CSE101 PA6 // Assignment Number
 * * * * Arithmetic.cpp // FileName
 * * * * Client program for BigInteger ADT // Description
 * * * ***/

#include<iostream>
#include<fstream>
#include<string>
#include "BigInteger.h"
 
using namespace std;

#define MAX_LEN 300

int main(int argc, char * argv[]){

	int line_count;
	string line;
	ifstream in;
   	ofstream out;
	string A;
	string B;

	if( argc != 3 ){
      		cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
      		return(EXIT_FAILURE);
   	}

	in.open(argv[1]);
   	if( !in.is_open() ){
      		cerr << "Unable to open file " << argv[1] << " for reading" << endl;
      		return(EXIT_FAILURE);
   	}

   	out.open(argv[2]);
   	if( !out.is_open() ){
      		cerr << "Unable to open file " << argv[2] << " for writing" << endl;
      		return(EXIT_FAILURE);
   	}

	line_count = 0;
   	while( getline(in, line) )  {
      		line_count++;
		if(line_count == 1){
			A = line;
			continue;
		}
		else if(line_count == 3){ 
                	B = line;
                	break; 
            	}
	}

	cout << A << endl;
	cout << B  << endl;

	return 0;

}









