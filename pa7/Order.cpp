/**
 * * * * Amisha Prasad // First and Last Name
 * * * * aprasa14 // UCSC UserID
 * * * * 2024 Winter CSE101 PA7 // Assignment Number
 * * * * Order.cpp // FileName
 * * * * Client file for Dictionary ADT // Description
 * * * ***/


#include "Dictionary.h"
#include <fstream>

using namespace std;

int main(int argc, char* argv[]) {

    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <input file>" << endl;
        return EXIT_FAILURE;
    }

    // get input file
    ifstream input(argv[1]);

    if (!input.is_open()) {
        cerr << "Could not open the file " << argv[1] << endl;
        return EXIT_FAILURE;
    }

    // get output file
    ofstream output;

    // open output file
    output.open(argv[2], fstream::out);

    // create new dictionary, string, and int
    Dictionary newDict;
    string newString = "";
    int val = 1;

    // loop through and get each line of input
    while (getline(input, newString)) {
        newDict.setValue(newString, val);
        val++;
    }

    // printing to output
    output << newDict.to_string() << endl;
    output << newDict.pre_string() << endl;

    newDict.clear();

    input.close();
    output.close();

    return 0;
}



